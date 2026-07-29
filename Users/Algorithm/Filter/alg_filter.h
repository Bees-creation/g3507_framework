/**
 * @brief 滤波算法
 * @date 2026/6/12
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef ALG_FILTER_H
#define ALG_FILTER_H

/**
 * @brief 一阶滤波
 *
 * @tparam Type 类型
 * @param x 当前值
 * @param y 上次输出
 * @param a 滤波系数
 * @retval Type y输出值
 */
template<typename Type>
Type Filter_First_Order(Type x, Type y, Type a) {
    y = (a * x + (1 - a) * y);
    return (y);
}
template<typename Type>
Type Filter_First_Order(Type *x, Type *y, Type a) {
    *y = (a * x + (1 - a) * y);
    return (*y);
}

// 计数器滤波
class Class_RepeatCounter {
public:
    Class_RepeatCounter(uint32_t __Threshold)
    : Threshold(__Threshold) {
    }

    bool Count() {
        Repeat++;
        if (Repeat >= Threshold) {
            Repeat = 0;
            return 1;
        }
        else {
            return 0;
        }
    }

    void Collapse() {
        Repeat = 0;
    }

private:
    uint32_t Repeat = 0;
    uint32_t Threshold;
};

#endif /* ALG_FILTER_H */
