# FreeRTOS 的线程安全

线程安全的问题只会在多个线程同时访问相同的变量（比如全局变量、函数中的静态变量）才会出现。

线程安全问题必须重视，否则最后工程写得越大越容易出现玄学问题。

## 线程安全问题的原因

比如，有两个线程A和B，A 不断写入一个全局数组，B 读取这个数组并进行计算。

如果 A 写入进行到一半时发生了线程切换，B开始读取。这时 B 读到的数据就有一半是当前的数据，另一半是之前的数据，这样 B 读到的数据就错位了，B用错误的数据进行计算就会算出怪东西。

## 如何避免遇到线程安全问题
### 库函数的使用
- 不使用C语言自带的 malloc() 及相关函数，而应使用 FreeRTOS 提供的函数 `pvPortMalloc()` 和 `vPortFree()`
- 只在一个线程中使用 printf()。如果一定要在多个线程中使用，至少要保证它们不会同时调用printf()（可以用互斥量保护）

> 因为 malloc() 会修改C库内部的一个全局变量，它不是线程安全的。而 printf() 会调用 malloc()，因此也不是线程安全的。

### 尽量不要使用全局变量和函数内静态变量
全局变量是导致线程安全问题的根本，因此应尽量避免使用全局变量。

-   尽量不要使用全局变量，而是使用局部变量
-   不到万不得已，不要使用函数内静态变量，即不要使用这样的变量：
    ```c
    void Function() {
        static int var;
    }
    ```

## 如何解决线程安全问题

FreeRTOS 提供了队列和各种信号量机制来解决线程安全问题。

请学习：

信号量概念: <https://freertos.blog.csdn.net/article/details/50835613>

相关代码: <https://www.cnblogs.com/doitjust/p/11024718.html>

官方文档: <https://www.freertos.org/Inter-Task-Communication.html>

官方API 介绍及例子: <https://www.freertos.org/a00113.html>

### 如何安全地在线程之间共享数据

如果数据只会在线程中被读写，而不会在中断中读写时，有以下几种方法。

1. 临时关闭线程调度
    ```c
    // 关闭线程调度
    vTaskSuspendAll();

    // 读写数据的代码
    // 这里的代码执行时间要尽可能地短，否则其他线程无法及时执行，会影响系统实时性。通常建议在 1 ms 以内。

    // 启动线程调度
    xTaskResumeAll();
    ```
    原理：vTaskSuspendAll() 会关闭线程调度。关闭线程调度后，当前线程就永远不会被其他线程打断，因此读写全局变量的代码能完整执行。  
    在读写完毕后再次打开线程调度，使系统恢复正常运行。

    注：
    - vTaskSuspendAll() 不会关闭中断，所以不会影响中断的实时响应，但这也意味着读写数据的代码会被中断打断，所以需要保证中断里的代码不会读写这里的数据。
    - 关闭线程调度后不能使用`osDelay()` 或 `vTaskDelay()` 等延时函数。（可以使用 `HAL_Delay()`延时，但非常不建议这样做）

2. 使用互斥信号量


    建议先学习FreeRTOS的各种信号量  
    省流：  
    互斥量（简称互斥量）同时只能由一个线程获取，并由这个线程释放。**（所以中断中不能操作互斥量）**
    
    当一个线程获取了互斥量后，其他线程就不能再次获取这个互斥量，除非那个获取了互斥量的线程释放了互斥量。

    > 互斥信号量使用 `xSemaphoreCreateMutex()` 创建，使用 `xSemaphoreTake()` 获取，使用 `xSemaphoreGive()` 释放。

    假设有 A、B 两个线程，如果 A 线程获取了互斥量之后（还没有释放），B 线程也尝试获取这个互斥量，B 线程就会被阻塞，直到 A 释放了互斥量（这时互斥量会被 B 立即获取）或到达超时时间（这时`xSemaphoreTake()`会返回 pdFALSE)。

    只要在读写数据前获取互斥量，读写完成后释放互斥量，就可以保证数据同时只由一个线程访问。


    代码示例：
    ```c
    typedef struct
    {
        int data[10]; // 被保护的数据
        SemaphoreHandle_t semaphore; // 互斥信号量的句柄
    } DataStruct_t;

    DataStruct_t DataStruct;

    // 先调用这个函数创建信号量，然后再创建 Task1 和 Task2 两个线程
    void DataStructInit(DataStruct_t *data_struct)
    {
        // 创建互斥信号量（使用互斥量前要创建互斥量（创建一次就行了），之后就可以对它进行获取和释放操作）
        data_struct->semaphore = xSemaphoreCreateMutex();

        // 判断是否创建成功
        if (data_struct->semaphore == NULL) {
            // FreeRTOS heap 空间不够，创建失败
        } else {
            // 创建成功
        }
    }

    void Task1(void const *argument)
    {
        (void)argument;

        TickType_t timeout = portMAX_DELAY; // 等待时间（单位 tick）。如果是 portMAX_DELAY 则一直等

        for (;;) {
            /* See if we can obtain the semaphore.  If the semaphore is not
            available wait 'timeout' ticks to see if it becomes free. */
            if (xSemaphoreTake(DataStruct.semaphore, timeout) == pdTRUE) {
                /* We were able to obtain the semaphore and can now access the
                shared resource. */

                // 读写代码
                // DataStruct.data = ...

                /* We have finished accessing the shared resource.  Release the
                semaphore. */
                xSemaphoreGive(DataStruct.semaphore);
            } else {
                /* We could not obtain the semaphore and can therefore not access
                the shared resource safely. */
            }
        }
    }

    // 和 Task1 完全相同
    void Task2(void const *argument)
    {
        (void)argument;

        TickType_t timeout = portMAX_DELAY; // 等待时间（单位 tick）。如果是 portMAX_DELAY 则一直等

        for (;;) {
            /* See if we can obtain the semaphore.  If the semaphore is not
            available wait 'timeout' ticks to see if it becomes free. */
            if (xSemaphoreTake(DataStruct.semaphore, timeout) == pdTRUE) {
                /* We were able to obtain the semaphore and can now access the
                shared resource. */

                // 读写代码
                // DataStruct.data = ...

                /* We have finished accessing the shared resource.  Release the
                semaphore. */
                xSemaphoreGive(DataStruct.semaphore);
            } else {
                /* We could not obtain the semaphore and can therefore not access
                the shared resource safely. */
            }
        }
    }
    ```

### 如何安全地在线程和中断之间共享数据

如果数据既会在线程中被读写，又会在中断中被读写时，有以下几种方法。

1. 临时关闭中断和调度
    ```c
    // 进入关键区（关闭线程调度和中断）
    taskENTER_CRITICAL();

    // 读写数据的代码
    // 这里的代码执行时间要尽可能地短，否则其他线程和中断无法及时执行，会影响系统实时性。通常建议在 1 us 以内。

    // 退出关键区（启动线程调度和中断）
    taskEXIT_CRITICAL();
    ```
    原理：taskENTER_CRITICAL() 会关闭线程调度和中断。关闭线程调度和中断后，当前线程就永远不会被其他线程和中断打断(见注)，因此读写全局变量的代码能完整执行。  
    在读写完毕后再次打开线程调度和中断，使系统恢复正常运行。

    注：
    - taskENTER_CRITICAL() 只会关闭优先级低于或等于 `LIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY`（默认为5）的中断，因此比这个优先级高的中断仍然会打断线程。所以不要在这样的中断中改变线程需要读写的全局变量。
    - 由于 taskENTER_CRITICAL() 会关中断，因此一定要保证关键区的代码执行时间足够短。
    - 关闭线程调度后不能使用`osDelay()` 或 `vTaskDelay()` 或 `HAL_Delay()` 等延时函数（否则会卡在延时里）。

2. 使用二值信号量

    但如果在中断写入数据，线程读取数据，可以使用二值信号量保证数据安全。  
    思路：  
    中断中写入数据后释放二值信号量。  
    线程获取这个信号量。如果获取到了，就读取，否则就一直阻塞。只要读取的时间小于进入中断的周期，就能保证数据安全。

    （也可以使用计数信号量，此时可以检测出读取速度是否够快。如果发现计数信号量的值大于1，则说明读取得不够快）

    相关代码请自行尝试编写。

