/**
 * @brief 计时器
 * @date 2026/7/29
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef DVC_TIMER_H
#define DVC_TIMER_H

#include "Drivers/TIM/drv_tim.h"

class Class_Timer {
public:
    static void Init(void);

    static void Update(void);

    static void Clear(void);

    static uint32_t Get(void);

private:
    inline static uint32_t time = 0;
};

#endif /* DVC_TIMER_H */
