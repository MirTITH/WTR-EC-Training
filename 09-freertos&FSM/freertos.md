# FreeRTOS

## 注意事项
arm-none-eabi-gcc 和 MDK 工程的 FreeRTOS 文件有区别，不能混用

有FPU的MCU要开启 ENABLE_FPU

不能使用 malloc() 和 free() 函数，而要改为 `pvPortMalloc()` 和 `vPortFree()`

TOTAL_HEAP_SIZE 是 freertos 的堆内存，动态创建的线程、邮箱等和`pvPortMalloc()`分配的内存都从这里分配

CubeMX 里的默认线程建议选择`As Weak`

gcc编译器要开启 USE_NEWLIB_REENTRANT
> NEWLIB 是 arm-none-eabi-gcc 的C语言库，开启后才能安全地在多线程中使用一些C函数（如printf）。不开启使用这些函数会造成内存泄漏，甚至进 HardFault  
> MDK 用的不是 NEWLIB 库，所以不能开启 USE_NEWLIB_REENTRANT（至于MDK在freertos下能不能用printf，我没试过）

## 官方文档

<https://www.freertos.org/RTOS.html>

## 其他文档

比较完备的教程：[FreeRTOS基础篇](https://blog.csdn.net/zhzht19861011/category_9265276.html)

在 CubeMX 中怎么配置：[FreeRTOS+CubeMX系列第一篇——初识FreeRTOS](https://blog.csdn.net/weixin_44793491/article/details/107577711)

让你看得懂FreeRTOS奇怪的命名：[FreeRTOS 数据类型和编程规范](https://deepinout.com/freertos-tutorials/freertos-intro/freertos-tutorials-data-types-and-programming-specifications.html)

有关 NewLib 线程安全的问题：

- [关于 FreeRTOS和 newlib库共存问题](https://blog.csdn.net/qq_42992084/article/details/120927845)
- <https://nadler.com/embedded/newlibAndFreeRTOS.html>
  > nadler 的代码有一个地方编译报错，我进行了一些修改，并添加了一点功能：<https://github.com/MirTITH/FreeRTOS_helpers>