/**
 * @brief 数学库
 * @date 2026/5/26
 * @ref 参考代码 https://github.com/yssickjgd/robowalker_train
 * @copyright USTC-RoboWalker (c) 2023
 */

#ifndef ALG_MATH_H
#define ALG_MATH_H

#include <stdint.h>

#ifndef PI
#define PI 3.14159265358979f
#endif

/* 单位换算 */
// rpm换算到rad/s
constexpr float MATH_RADPS_DIVIDE_RPM = 2.0f * PI / 60.0f;
#define MATH_RPM_TO_RADPS(rpm) (rpm * MATH_RADPS_DIVIDE_RPM)
// deg换算到rad
constexpr float MATH_RAD_DIVIDE_DEG = PI / 180.0f;
#define MATH_DEG_TO_RAD(deg) (deg * MATH_RAD_DIVIDE_DEG)
// 摄氏度换算到开氏度
constexpr float MATH_CELSIUS_MINUS_KELVIN = 273.15f;
#define MATH_CELSIUS_TO_KELVIN(celsius) (celsius + MATH_CELSIUS_MINUS_KELVIN)

/**
 * @brief 限幅函数
 *
 * @tparam Type 类型
 * @param x 传入数据
 * @param Min 最小值
 * @param Max 最大值
 * @retval Type x输出值
 */
template<typename Type>
Type Math_Constrain(Type x, Type Min, Type Max) {
    if (x < Min) {
        x = Min;
    }
    else if (x > Max) {
        x = Max;
    }
    return (x);
}
template<typename Type>
Type Math_Constrain(Type *x, Type Min, Type Max) {
    if (*x < Min) {
        *x = Min;
    }
    else if (*x > Max) {
        *x = Max;
    }
    return (*x);
}

/**
 * @brief 求绝对值
 *
 * @tparam Type 类型
 * @param x 传入数据
 * @retval Type x输出值
 */
template<typename Type>
Type Math_Abs(Type x) {
    return ((x > 0) ? x : -x);
}
template<typename Type>
Type Math_Abs(Type *x) {
    return ((*x > 0) ? *x : -*x);
}

#endif /* ALG_MATH_H */

/************************ COPYRIGHT(C) USTC-ROBOWALKER **************************/