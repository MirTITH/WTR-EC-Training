/**
 * @file uart_printf.c
 * @author X. Y.
 * @brief printf() 串口重定向
 * @version 3.2
 * @date 2022-9-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "usart.h"

// 串口号配置
static UART_HandleTypeDef *debug_huart = &huart1;
// #define config_USE_RTOS 1 // 是否使用 RTOS，如果使用，建议打开

#if (config_USE_RTOS == 1)
#include "cmsis_os.h"
#endif

// 判断是哪个编译器。GCC 会定义 __GNUC__，ARMCCv5 会定义 __ARMCC_VERSION，ARMCCv6 会定义 __GNUC__ 和 __ARMCC_VERSION
#if (defined __GNUC__) && (!defined __ARMCC_VERSION)

// GCC 编译器

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
__attribute__((used)) int _write(int fd, char *pBuffer, int size)
{
    switch (fd) {
        case STDOUT_FILENO: // 标准输出流
            while (HAL_UART_Transmit(debug_huart, (uint8_t *)pBuffer, size, HAL_MAX_DELAY) == HAL_BUSY) {
#if (config_USE_RTOS == 1)
                osThreadYield();
#endif
            }
            break;
        case STDERR_FILENO: // 标准错误流
            while (HAL_UART_Transmit(debug_huart, (uint8_t *)pBuffer, size, HAL_MAX_DELAY) == HAL_BUSY) {
#if (config_USE_RTOS == 1)
                osThreadYield();
#endif
            }
            break;
        default:
            // EBADF, which means the file descriptor is invalid or the file isn't opened for writing;
            errno = EBADF;
            return -1;
            break;
    }
    return size;
}

#else

// MDK 的 ARMCC 编译器

#include <stdio.h>
#include <rt_sys.h>
#include <rt_misc.h>
#include <time.h>

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
    while (HAL_UART_Transmit(debug_huart, (uint8_t *)&ch, 1, HAL_MAX_DELAY) == HAL_BUSY) {
#if (config_USE_RTOS == 1)
        osThreadYield();
#endif
    }
    return ch;
}

// ARMCC 默认启用半主机模式，重定向 printf 后需要关闭，防止卡死
// ARMCCv6 和 ARMCCv5 关闭半主机模式的代码不一样，需要判断
#if __ARMCC_VERSION >= 6000000
// ARMCCv6
__asm(".global __use_no_semihosting");
#elif __ARMCC_VERSION >= 5000000
// ARMCCv5
#pragma import(__use_no_semihosting)
#else
#error Unsupported compiler
#endif

// 关闭半主机模式后，需要自己实现一些相关系统函数

const char __stdin_name[]  = ":tt";
const char __stdout_name[] = ":tt";
const char __stderr_name[] = ":tt";

FILEHANDLE _sys_open(const char *name, int openmode)
{
    return 1;
}

int _sys_close(FILEHANDLE fh)
{
    return 0;
}

char *_sys_command_string(char *cmd, int len)
{
    return NULL;
}

int _sys_write(FILEHANDLE fh, const unsigned char *buf, unsigned len, int mode)
{
    return 0;
}

int _sys_read(FILEHANDLE fh, unsigned char *buf, unsigned len, int mode)
{
    return -1;
}

void _ttywrch(int ch)
{
}

int _sys_istty(FILEHANDLE fh)
{
    return 0;
}

int _sys_seek(FILEHANDLE fh, long pos)
{
    return -1;
}

long _sys_flen(FILEHANDLE fh)
{
    return -1;
}

void _sys_exit(int return_code)
{
    while (1)
        ;
}

clock_t clock(void)
{
    clock_t tmp;
    return tmp;
}

void _clock_init(void)
{
}

time_t time(time_t *timer)
{
    time_t tmp;
    return tmp;
}

int system(const char *string)
{
    return 0;
}

char *getenv(const char *name)
{
    return NULL;
}

void _getenv_init(void)
{
}
#endif
