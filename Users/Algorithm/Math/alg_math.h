/**
 * @brief 数学库
 * @date 2026/5/26
 * @ref 参考代码 https://github.com/yssickjgd/robowalker_train
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef ALG_MATH_H
#define ALG_MATH_H

#include <math.h>

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

/**
 * @brief 归一化线性映射
 *
 * @tparam Type 类型
 * @param x 传入数据，范围[Min,Max]
 * @param Min 最小值
 * @param Max 最大值
 * @retval [Min,Max]映射到[0,1]，超出范围的x会被限幅
 */
template<typename Type>
Type Math_Normalization(Type x, Type Min, Type Max) {
    return (Math_Constrain(x, Min, Max) - Min) / (Max - Min);
}

/**
 * @brief 逆归一化线性映射
 *
 * @tparam Type 类型
 * @param x 归一化数据，范围[0,1]
 * @param Min 最小值
 * @param Max 最大值
 * @retval [0,1]映射到[Min,Max]，超出范围的x会被限幅
 */
template<typename Type>
Type Math_Denormalization(Type x, Type Min, Type Max) {
    return Math_Constrain(x * (Max - Min) + Min, Min, Max);
}

/**
 * @brief 归一化线性插值
 *
 * @tparam Type 类型
 * @param x1 起始值
 * @param x2 终点值
 * @param t 时间
 * @param T 周期
 * @retval Type xt输出值
 */
template<typename Type>
Type Math_Linear_Interpolation(Type x1, Type x2, Type t, Type T) {
    t = Math_Normalization(t, (Type)0, T);
    return Math_Denormalization(t, x1, x2);
}

/**
 * @brief 归一化五次多项式插值
 *
 * @tparam Type 类型
 * @param x1 起始值
 * @param x2 终点值
 * @param t 时间
 * @param T 周期
 * @retval Type xt输出值
 */
template<typename Type>
Type Math_Quintic_Polynomial_Interpolation(Type x1, Type x2, Type t, Type T) {
    t = Math_Normalization(t, (Type)0, T);
    float y = 6 * pow(t, 5) - 15 * pow(t, 4) + 10 * pow(t, 3);
    return Math_Denormalization(y, x1, x2);
}

/**
 * @brief 绝对角度类型
 * 
 * @param _value 绝对角度，范围 [-180°, 180°)
 */
class Angle_t {
private:
    float _value;

    /**
     * @brief 角度标准化
     * 
     * @param angle 任意角度，范围 (-Inf, Inf)
     */
    static float Normalize(float angle) {
        angle = fmodf(angle, 360.0f);
        if (angle >= 180.0f) { angle -= 360.0f; }
        else if (angle < -180.0f) { angle += 360.0f; }
        return angle;
    }

public:
    /**
     * @brief 默认初始化
     */
    Angle_t() : _value(0.0f) {}

    /**
     * @brief 传入角度初始化
     * 
     * @param angle 任意角度，范围 (-Inf, Inf)
     */
    Angle_t(float angle) : _value(Normalize(angle)) {}

    /**
     * @brief 显式类型转换，可以将类当作 float 变量传参
     * 
     * @retval 绝对角度，范围 [-180°, 180°)
     */
    explicit operator float() const { return _value; }

    /**
     * @brief 赋值运算符，用于从 float 变量赋值
     * 
     * @param angle 任意角度，范围 (-Inf, Inf)
     * @retval 绝对角度类型
     */
    Angle_t& operator=(float angle) {
        _value = Normalize(angle);
        return *this;
    }

    /**
     * @brief 减号运算符，用于计算 Angle_t 最小角度差值
     * 
     * @param other 绝对角度类型
     * @retval 绝对角度类型
     */
    Angle_t operator-(const Angle_t& other) const {
        return Angle_t(_value - other._value);
    }
};

/**
 * @brief 相对角度类型
 * 
 * @param _value 相对角度，范围 (-Inf, Inf)
 */
class Rotation_t {
private:
    float _value;

public:
    /**
     * @brief 默认初始化
     */
    Rotation_t() : _value(0.0f) {}

    /**
     * @brief 传入角度初始化
     * 
     * @param angle 任意角度，范围 (-Inf, Inf)
     */
    Rotation_t(float val) : _value(val) {}

    /**
     * @brief 显式类型转换，可以将类当作 float 变量传参
     * 
     * @retval 相对角度，范围 (-Inf, Inf)
     */
    explicit operator float() const { return _value; }

    /**
     * @brief 赋值运算符，用于从 float 变量赋值
     * 
     * @param angle 任意角度，范围 (-Inf, Inf)
     * @retval 相对角度类型
     */
    Rotation_t& operator=(float angle) {
        _value = angle;
        return *this;
    }
};

#endif /* ALG_MATH_H */
