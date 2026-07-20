/**
 * @brief 图形运算
 * @date 2026/6/18
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef ALG_GRAPHICS_H
#define ALG_GRAPHICS_H

#include "Algorithm/Math/alg_matrix.h"

/**
 * @brief 立方体渲染器
 *        管理立方体顶点数据，计算旋转后投影到屏幕的像素坐标
 */
class CubeRenderer {
public:
    /**
     * @brief 屏幕像素坐标点
     */
    struct ScreenPoint {
        int x, y;
    };

    /**
     * @brief 构造函数
     * @param screen_w 屏幕宽度
     * @param screen_h 屏幕高度
     */
    CubeRenderer(int screen_w, int screen_h)
        : screen_w_(screen_w), screen_h_(screen_h) {
        // 缩放系数为屏幕短边的 10%（使立方体在屏幕内大小适中）
        scale_ = (screen_w < screen_h) ? screen_w * 0.10f : screen_h * 0.10f;
        camera_dist_ = 5.0f;   // 相机到原点的距离
    }

    /**
     * @brief 更新屏幕尺寸
     */
    void setScreenSize(int screen_w, int screen_h) {
        screen_w_ = screen_w;
        screen_h_ = screen_h;
        scale_ = (screen_w < screen_h) ? screen_w * 0.10f : screen_h * 0.10f;
    }

    /**
     * @brief 计算旋转后的 8 个顶点在屏幕上的像素坐标
     * @param rx 绕 X 轴旋转角
     * @param ry 绕 Y 轴旋转角
     * @param rz 绕 Z 轴旋转角
     * @param out 输出数组，需至少容纳 8 个 ScreenPoint
     */
    void computeScreenPoints(float rx, float ry, float rz, ScreenPoint out[8]) const;

    /**
     * @brief 计算随时间变化的RGB565颜色值
     * 
     * @param time 时间
     * @retval uint16_t RGB565颜色值
     */
    static uint16_t _rgb565Gen(float time) {
        // 三个不同频率的正余弦交叉调制
        float raw_hue = 0.5f + 0.5f * sinf(time * 0.3f) * cosf(time * 0.7f)
                    + 0.15f * sinf(time * 1.1f + 0.8f);
        // 安全归一化到[0,1]
        float hue = fmodf(raw_hue, 1.0f);
        if (hue < 0) hue += 1.0f;
        // 饱和度与明度也带点不规则变化
        float sat = 0.6f + 0.3f * sinf(time * 0.4f + 1.5f);
        float val = 0.9f + 0.1f * sinf(time * 0.2f + 2.3f);

        // HSV~RGB
        int sector = (int)(hue * 6.0f);
        float frac = hue * 6.0f - sector;

        float p = val * (1.0f - sat);
        float q = val * (1.0f - sat * frac);
        float t = val * (1.0f - sat * (1.0f - frac));

        float r, g, b;
        switch (sector) {
            case 0: r = val; g = t;  b = p;  break;// 红~黄
            case 1: r = q;  g = val; b = p;  break;// 黄~绿
            case 2: r = p;  g = val; b = t;  break;// 绿~青
            case 3: r = p;  g = q;  b = val; break;// 青~蓝
            case 4: r = t;  g = p;  b = val; break;// 蓝~紫
            default:r = val; g = p;  b = q;  break;// 紫~红
        }

        // 量化到RGB565
        uint8_t R = (uint8_t)(r * 31.0f + 0.5f);
        uint8_t G = (uint8_t)(g * 63.0f + 0.5f);
        uint8_t B = (uint8_t)(b * 31.0f + 0.5f);
        return (uint16_t)((R << 11) | (G << 5) | B);
    }

private:
    // 立方体局部坐标顶点，范围[-1,1]
    static const Vector3 cube_vertices_[8];

    int screen_w_;
    int screen_h_;
    float scale_;
    float camera_dist_;
};

#endif /* ALG_GRAPHICS_H */
