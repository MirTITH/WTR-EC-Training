/**
 * @file uart_printf.c
 * @author X. Y.
 * @brief printf() 串口重定向
 * @version 2.1
 * @date 2022-9-11
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "usart.h"

// 串口号配置
static UART_HandleTypeDef *debug_huart = &huart1;

// 对于 GCC
#ifdef __GNUC__
#include <errno.h>
#include <sys/unistd.h>

/**
 * @brief Writes data to a file.
 *
 * @param fd File descriptor of file into which data is written.
 * @param pBuffer Data to be written.
 * @param size Number of bytes.
 * @return 成功则返回写入的字节数，否则返回 -1
 */
int _write(int fd, char *pBuffer, int size)
{
    HAL_StatusTypeDef status = HAL_ERROR;

    switch (fd)
    {
    case STDOUT_FILENO: // 标准输出流
        status = HAL_UART_Transmit(debug_huart, (uint8_t *)pBuffer, size, HAL_MAX_DELAY);
        break;
    case STDERR_FILENO: // 标准错误流
        status = HAL_UART_Transmit(debug_huart, (uint8_t *)pBuffer, size, HAL_MAX_DELAY);
        break;
    default:
        // EBADF, which means the file descriptor is invalid or the file isn't opened for writing;
        errno = EBADF;
        return -1;
        break;
    }

    return (status == HAL_OK ? size : 0);
}
#endif

// 对于 ARMCC (MDK)
#ifdef __arm__
#include <stdio.h>

/**
 *
 * @brief 将字符写入流
 *
 * @param ch 要写入的字符
 * @param stream 流
 * @return 返回写入的字符，但如果出现错误，返回 EOF
 */
int fputc(int ch, FILE *stream)
{
    HAL_StatusTypeDef status = HAL_UART_Transmit(debug_huart, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return (status == HAL_OK ? ch : EOF);
}

// 以下为关闭半主机模式的代码（防止卡死）

#pragma import(__use_no_semihosting)

//标准库需要的支持函数
struct __FILE
{
    int handle;
};

FILE __stdout;

//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x)
{
    (void)x;
}

#endif
