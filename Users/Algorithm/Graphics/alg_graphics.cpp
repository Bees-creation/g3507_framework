/**
 * @brief 图形运算
 * @date 2026/6/18
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#include "alg_graphics.h"

const Vector3 CubeRenderer::cube_vertices_[8] = {
    Vector3(-1, -1, -1), Vector3( 1, -1, -1),
    Vector3( 1,  1, -1), Vector3(-1,  1, -1),
    Vector3(-1, -1,  1), Vector3( 1, -1,  1),
    Vector3( 1,  1,  1), Vector3(-1,  1,  1)
};

void CubeRenderer::computeScreenPoints(float rx, float ry, float rz, ScreenPoint out[8]) const {
    // 构建总旋转矩阵 R = Rz * Ry * Rx
    Matrix4 rx_m = MatrixGen::rotationX(rx);
    Matrix4 ry_m = MatrixGen::rotationY(ry);
    Matrix4 rz_m = MatrixGen::rotationZ(rz);
    Matrix4 rot_mat = MatrixGen::multiply(rz_m, MatrixGen::multiply(ry_m, rx_m));

    float cx = screen_w_ / 2.0f;
    float cy = screen_h_ / 2.0f;

    for (int i = 0; i < 8; i++) {
        // 旋转顶点
        Vector3 v = MatrixGen::apply(cube_vertices_[i], rot_mat);

        // 透视投影
        float factor = camera_dist_ / (camera_dist_ + v.z);
        float px_ndc = v.x * factor;
        float py_ndc = v.y * factor;

        // 视口变换（屏幕 Y 轴向下，取反；并加上额外偏移）
        out[i].x = (int)(px_ndc * scale_ + cx);
        out[i].y = (int)(-py_ndc * scale_ + cy);
    }
}
