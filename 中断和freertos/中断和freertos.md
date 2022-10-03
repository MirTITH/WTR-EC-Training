# 中断和freertos

## 什么是中断

- 普通线程（裸机只有 1 个线程，使用 rtos 后就能创建多个线程）
- 中断服务处理 (Interrupt Service Routines, ISR)（比如各种中断回调函数）

## 中断优先级

抢占优先级和子优先级

stm32 的中断向量表里，数字越低，优先级越高，一般不使用子优先级，并且使用 FreeRTOS 时不能使用子优先级

高优先级的抢占优先级是可以打断正在进行的低抢占优先级中断的。

抢占优先级相同的中断，高响应优先级不可以打断低响应优先级的中断。

抢占优先级相同的中断，当两个中断同时发生的情况下，哪个响应优先级高，哪个先执行。

如果两个中断的抢占优先级和响应优先级都是一样的话，则看哪个中断先发生就先执行。

## 线程优先级

- 数字越高，优先级越高
- 线程一定比中断的优先级低，即中断一定会抢占线程（除非关闭了中断）

## 在中断中用 freeRTOS 相关的函数

在中断中只能调用以 `FromISR` 结尾的 FreeRTOS 函数

只有在优先级低于 `LIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY` 的中断中才能调用 FreeRTOS 的函数

在 FreeRTOS 中调用 `taskENTER_CRITICAL()` 只会关闭优先级低于或等于 `LIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY` 的中断
