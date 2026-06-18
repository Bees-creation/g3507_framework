#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "ti_msp_dl_config.h"


/* 调度器行为 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0   // 使用通用任务选择方法
#define configTICK_RATE_HZ ((TickType_t) 1000)      // 1kHz时钟节拍
#define configUSE_PREEMPTION 1                      // 启用抢占式调度
/*
 * 调度器会运行最高优先级任务
 * 但不会因为tick更新而切换同优先级任务
 */
#define configUSE_TIME_SLICING 0            // 同优先级时间片轮转（禁用）
/*
 * 任务优先级数量
 * 一个优先级可以添加任意数量的任务
 * 数字越小，任务优先级越低
 * 由于每个优先级都要消耗RAM，原则是非必要不分配新的优先级
 */
#define configMAX_PRIORITIES (10UL)         // 任务优先级数量（0~9）
/*
 * 空闲优先级任务就绪时，空闲任务不会让出CPU
 * 根据应用程序的需要，空闲任务让出CPU的行为可能产生不良影响（参照FreeRTOS配置文档）
 */
#define configIDLE_SHOULD_YIELD 0           // 空闲任务主动让出CPU（禁用）
#define configUSE_16_BIT_TICKS 0            // 仅适用于8位和16位硬件


/* 硬件和内存使用情况 */
#define configCPU_CLOCK_HZ ((unsigned long) CPUCLK_FREQ)    // 系统时钟
/* 允许的最小堆栈大小 */
#define configMINIMAL_STACK_SIZE ((unsigned short) 128)     // 最小任务栈（128字*4字节/字=512字节）
#define configMAX_TASK_NAME_LEN (12)                        // 任务名最大长度
#define configTOTAL_HEAP_SIZE ((size_t)(8 * 1024))          // 堆总大小（8KB*1024字节/KB）

/*
 * 如果使用静态任务分配（以及计时器，configUSE_TIMERS = 1）
 * 必须提供两个回调函数:
 * - vApplicationGetIdleTaskMemory() 为空闲任务提供内存
 * - vApplicationGetTimerTaskMemory() 为定时器任务提供内存
 * 这些函数的实现在 StaticAllocs_freertos.c 中提供
 * 他们是取自FreeRTOS配置文档的示例实现
 */
#define configSUPPORT_STATIC_ALLOCATION 1   // 静态任务分配

/* 空闲任务堆栈大小（以字为单位） */
#define configIDLE_TASK_STACK_DEPTH (configMINIMAL_STACK_SIZE)

/* TI-POSIX线程的默认堆栈大小（以字为单位） */
#define configPOSIX_STACK_SIZE ((unsigned short) 256)


/* 功能裁剪 */
#define configUSE_MUTEXES 1                 // 互斥信号量
#define configUSE_TICKLESS_IDLE 1           // 空闲停用SysTick的低功耗模式
#define configUSE_APPLICATION_TASK_TAG 1 /* Need by POSIX/pthread */
/*
 * 协程是为小进程设计的，这类进程通常有RAM限制，通常不会在32位MCU上使用
 */
#define configUSE_CO_ROUTINES 0             // 协程（禁用）
#define configUSE_COUNTING_SEMAPHORES 1     // 计数信号量
#define configUSE_RECURSIVE_MUTEXES 1       // 递归互斥量
/*
 * 如果启用队列集功能，任务可以把多个队列视为一个集合，并按集合阻塞/挂起
 */
#define configUSE_QUEUE_SETS 0              // 队列集（禁用）
#define configUSE_TASK_NOTIFICATIONS 1      // 任务通知

/* 钩子(回调)函数裁剪 */
#define configUSE_IDLE_HOOK 0               // 空闲钩子（禁用）
#define configUSE_TICK_HOOK 0
#define configUSE_MALLOC_FAILED_HOOK 0

/* 调试辅助 */
/*
 * 栈溢出检测方法: 创建任务时将栈填充为已知值，切出任务时RTOS检测最后16字节，确保
 * 这16字节没有被覆盖，如果覆盖了，则调用栈溢出回调函数，但不保证捕获所有栈溢出
 * 必须提供栈溢出钩子函数，函数的示例实现在 AppHooks_freertos.c 中提供
 */
#define configCHECK_FOR_STACK_OVERFLOW 2    // 栈溢出检测
/* 调试断言: 当表达式为假时，关闭中断并进入死循环 */
#define configASSERT(x)           \
    if ((x) == 0) {               \
        taskDISABLE_INTERRUPTS(); \
        for (;;)                  \
            ;                     \
    }
/*
 * 队列注册表允许文本名称与队列相关联，以便在RTOS内核感知调试器中轻松识别队列
 */
#define configQUEUE_REGISTRY_SIZE 0     // 队列注册表（禁用）

/* Minimum FreeRTOS tick periods of idle before invoking Power policy */
/* TODO: find way to reduce this; FreeRTOS requires it to be 2 or more */
#define configEXPECTED_IDLE_TIME_BEFORE_SLEEP 2

/* 软件定时器 */
#define configUSE_TIMERS 1              // 使用软件定时器
#define configTIMER_TASK_PRIORITY (5)   // 定时器任务优先级
#define configTIMER_QUEUE_LENGTH (20)   // 定时器队列长度
/* 定时器任务堆栈大小 (以字为单位) */
#define configTIMER_TASK_STACK_DEPTH (configMINIMAL_STACK_SIZE)
/* 关闭旧版本FreeRTOS中被废弃的功能 */
#define configENABLE_BACKWARD_COMPATIBILITY 0

#if defined(__TI_COMPILER_VERSION__) || defined(__ti_version__)
#include <ti/posix/freertos/PTLS.h>
#define traceTASK_DELETE(pxTCB) PTLS_taskDeleteHook(pxTCB)
#elif defined(__IAR_SYSTEMS_ICC__)
#ifndef __IAR_SYSTEMS_ASM__
#include <ti/posix/freertos/Mtx.h>
#define traceTASK_DELETE(pxTCB) Mtx_taskDeleteHook(pxTCB)
#endif
#endif

/*
 *  Enable thread local storage
 *
 *  Assign TLS array index ownership here to avoid collisions.
 *  TLS storage is needed to implement thread-safe errno with
 *  TI and IAR compilers. With GNU compiler, we enable newlib.
 */
#if defined(__TI_COMPILER_VERSION__) || defined(__ti_version__) || \
    defined(__IAR_SYSTEMS_ICC__) || defined(__ARMCC_VERSION)

#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 2

#if defined(__TI_COMPILER_VERSION__) || defined(__ti_version__)
#define PTLS_TLS_INDEX 0 /* ti.posix.freertos.PTLS */
#elif defined(__IAR_SYSTEMS_ICC__)
#define MTX_TLS_INDEX 0 /* ti.posix.freertos.Mtx */
#endif

#define NDK_TLS_INDEX 1 /* Reserve an index for NDK TLS */

#elif defined(__GNUC__)

#define configNUM_THREAD_LOCAL_STORAGE_POINTERS 1

#define NDK_TLS_INDEX 0 /* Reserve an index for NDK TLS */

/* note: system locks required by newlib are not implemented */
#define configUSE_NEWLIB_REENTRANT 1
#endif

/*
 * 函数API裁剪: 1表示启用/0表示禁用
 * 注意:  只有链接器不自动删除未被引用的函数时，设置INCLUDE_ 宏为0才是必要的
 */
#define INCLUDE_vTaskPrioritySet 1
#define INCLUDE_uxTaskPriorityGet 1
#define INCLUDE_vTaskDelete 1
#define INCLUDE_vTaskCleanUpResources 0
#define INCLUDE_vTaskSuspend 1
#define INCLUDE_vTaskDelayUntil 1
#define INCLUDE_vTaskDelay 1
#define INCLUDE_uxTaskGetStackHighWaterMark 0
#define INCLUDE_xTaskGetIdleTaskHandle 0
#define INCLUDE_eTaskGetState 1
#define INCLUDE_xTaskResumeFromISR 0
#define INCLUDE_xTaskGetCurrentTaskHandle 1
#define INCLUDE_xTaskGetSchedulerState 1
#define INCLUDE_xSemaphoreGetMutexHolder 0
#define INCLUDE_xTimerPendFunctionCall 0

/* Cortex-M0中断优先级配置如下...................... */

/* 使用系统配置 */
#ifdef __NVIC_PRIO_BITS
#define configPRIO_BITS __NVIC_PRIO_BITS
#else
#define configPRIO_BITS 2 /* 4 priority levels */
#endif

/*
 * “设置优先级”函数可以使用的最低优先级
 */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY 0x03

/*
 * 可以被中断服务函数调用中断安全FreeRTOS API的最高的中断优先级
 * 不要从高于该优先级的中断函数中，调用中断安全FREERTOS API（高优先级是小数字）
 */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY 1

/*
 * 中断优先级由内核端口层本身使用，这些对所有的Cortex-M端口都是通用的
 * 并且不依赖于任何特定的库函数
 */
#define configKERNEL_INTERRUPT_PRIORITY \
    (configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

/*
 * !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
 * See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html.
 *
 * Priority 1 (shifted 6 since only the top 2 bits are implemented).
 * Priority 1 is the second highest priority.
 * Priority 0 is the highest priority.
 */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY \
    (configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS))

/*
 * The trace facility is turned on to make some functions available for use in
 * CLI commands.
 */
#define configUSE_TRACE_FACILITY 1

/*
 * Runtime Object View is a Texas Instrument host tool that helps visualize
 * the application. When enabled, the ISR stack will be initialized in the
 * startup_<device>_<compiler>.c file to 0xa5a5a5a5. The stack peak can then
 * be displayed in Runtime Object View.
 */
#define configENABLE_ISR_STACK_INIT 0

/*
 * Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
 * standard names - can't be used with CCS due to limitations in the assemblers
 * pre-processing.
 */
/* Simplelink places the definitions in the startup files */
#ifndef __TI_COMPILER_VERSION__
#define xPortPendSVHandler PendSV_Handler
#define vPortSVCHandler SVC_Handler
#define xPortSysTickHandler SysTick_Handler
#endif

#endif /* FREERTOS_CONFIG_H */
