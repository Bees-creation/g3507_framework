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

private:
    // 立方体局部坐标顶点（范围 -1 ~ 1）
    static const Vector3 cube_vertices_[8];

    int screen_w_;
    int screen_h_;
    float scale_;
    float camera_dist_;
};

#endif /* ALG_GRAPHICS_H */
