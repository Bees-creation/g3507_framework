/**
 * @brief 矩阵运算
 * @date 2026/6/18
 * @copyright https://github.com/Bees-creation (c) 2026
 */

#ifndef ALG_MATRIX_H
#define ALG_MATRIX_H

#include <math.h>

/**
 * @brief 3维向量
 */
class Vector3 {
public:
    float x, y, z;

    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
        : x(x), y(y), z(z) {}
};

/**
 * @brief 4x4行主序矩阵
 */
class Matrix4 {
public:
    float m[4][4];

    Matrix4() {
        // 默认初始化为零矩阵
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m[i][j] = 0.0f;
    }
};

/**
 * @brief 矩阵生成器，提供静态生成矩阵方法
 */
class MatrixGen {
public:
    /**
     * @brief 单位矩阵
     */
    static Matrix4 identity() {
        Matrix4 mat;
        for (int i = 0; i < 4; i++) mat.m[i][i] = 1.0f;
        return mat;
    }

    /**
     * @brief 矩阵乘法
     */
    static Matrix4 multiply(const Matrix4& A, const Matrix4& B) {
        Matrix4 C;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                float sum = 0.0f;
                for (int k = 0; k < 4; k++) {
                    sum += A.m[i][k] * B.m[k][j];
                }
                C.m[i][j] = sum;
            }
        }
        return C;
    }

    /**
     * @brief 绕 X 轴旋转矩阵
     */
    static Matrix4 rotationX(float rad) {
        float c = cosf(rad), s = sinf(rad);
        Matrix4 mat = identity();
        mat.m[1][1] = c; mat.m[1][2] = -s;
        mat.m[2][1] = s; mat.m[2][2] = c;
        return mat;
    }

    /**
     * @brief 绕 Y 轴旋转矩阵
     */
    static Matrix4 rotationY(float rad) {
        float c = cosf(rad), s = sinf(rad);
        Matrix4 mat = identity();
        mat.m[0][0] = c; mat.m[0][2] = s;
        mat.m[2][0] = -s; mat.m[2][2] = c;
        return mat;
    }

    /**
     * @brief 绕 Z 轴旋转矩阵
     */
    static Matrix4 rotationZ(float rad) {
        float c = cosf(rad), s = sinf(rad);
        Matrix4 mat = identity();
        mat.m[0][0] = c; mat.m[0][1] = -s;
        mat.m[1][0] = s; mat.m[1][1] = c;
        return mat;
    }

    /**
     * @brief 应用矩阵变换到3维向量，忽略平移部分，但保留仿射变换
     */
    static Vector3 apply(const Vector3& v, const Matrix4& mat) {
        Vector3 out;
        out.x = v.x * mat.m[0][0] + v.y * mat.m[0][1] + v.z * mat.m[0][2] + mat.m[0][3];
        out.y = v.x * mat.m[1][0] + v.y * mat.m[1][1] + v.z * mat.m[1][2] + mat.m[1][3];
        out.z = v.x * mat.m[2][0] + v.y * mat.m[2][1] + v.z * mat.m[2][2] + mat.m[2][3];
        return out;
    }
};

#endif /* ALG_MATRIX_H */
