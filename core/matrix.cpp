#include <core/matrix.h>
#include <core/assert.h>

#include <core/vector.h>
#include <core/point.h>

namespace rt {

Matrix::Matrix(const Float4& r1, const Float4& r2, const Float4& r3, const Float4& r4) {
    this -> r1 = r1;
    this -> r2 = r2;
    this -> r3 = r3;
    this -> r4 = r4;
}

Float4& Matrix::operator[](int idx) {
    if (idx == 0) return r1;
    if (idx == 1) return r2;
    if (idx == 2) return r3;
    if (idx == 3) return r4;
    assert(false);

}

Float4 Matrix::operator[](int idx) const {
    if (idx == 0) return r1;
    if (idx == 1) return r2;
    if (idx == 2) return r3;
    if (idx == 3) return r4;
    assert(false);
}

Matrix Matrix::operator+(const Matrix& b) const {
    return Matrix(r1+b[0], r2+b[1], r3+b[2], r4+b[3]);
}

Matrix Matrix::operator-(const Matrix& b) const {
    return Matrix(r1-b[0], r2-b[1], r3-b[2], r4-b[3]);
}

Matrix Matrix::transpose() const {
    return Matrix(
        Float4(r1[0], r2[0], r3[0], r4[0]),
        Float4(r1[1], r2[1], r3[1], r4[1]),
        Float4(r1[2], r2[2], r3[2], r4[2]),
        Float4(r1[3], r2[3], r3[3], r4[3]));
}

Matrix Matrix::invert() const {
    Matrix result;
    const Matrix& m = *this;

    // Taken and modified from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
    result[0][0] =  m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
    result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
    result[2][0] =  m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
    result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

    float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
    if (det == 0)
        return Matrix::zero();

    result[0][1] = -m[0][1] * m[2][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2] + m[2][1] * m[0][2] * m[3][3] - m[2][1] * m[0][3] * m[3][2] - m[3][1] * m[0][2] * m[2][3] + m[3][1] * m[0][3] * m[2][2];
    result[1][1] =  m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2] - m[2][0] * m[0][2] * m[3][3] + m[2][0] * m[0][3] * m[3][2] + m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2];
    result[2][1] = -m[0][0] * m[2][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1] + m[2][0] * m[0][1] * m[3][3] - m[2][0] * m[0][3] * m[3][1] - m[3][0] * m[0][1] * m[2][3] + m[3][0] * m[0][3] * m[2][1];
    result[3][1] =  m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1] - m[2][0] * m[0][1] * m[3][2] + m[2][0] * m[0][2] * m[3][1] + m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1];
    result[0][2] =  m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2] - m[1][1] * m[0][2] * m[3][3] + m[1][1] * m[0][3] * m[3][2] + m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2];
    result[1][2] = -m[0][0] * m[1][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2] + m[1][0] * m[0][2] * m[3][3] - m[1][0] * m[0][3] * m[3][2] - m[3][0] * m[0][2] * m[1][3] + m[3][0] * m[0][3] * m[1][2];
    result[2][2] =  m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1] - m[1][0] * m[0][1] * m[3][3] + m[1][0] * m[0][3] * m[3][1] + m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1];
    result[3][2] = -m[0][0] * m[1][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1] + m[1][0] * m[0][1] * m[3][2] - m[1][0] * m[0][2] * m[3][1] - m[3][0] * m[0][1] * m[1][2] + m[3][0] * m[0][2] * m[1][1];
    result[0][3] = -m[0][1] * m[1][2] * m[2][3] + m[0][1] * m[1][3] * m[2][2] + m[1][1] * m[0][2] * m[2][3] - m[1][1] * m[0][3] * m[2][2] - m[2][1] * m[0][2] * m[1][3] + m[2][1] * m[0][3] * m[1][2];
    result[1][3] =  m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2] - m[1][0] * m[0][2] * m[2][3] + m[1][0] * m[0][3] * m[2][2] + m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2];
    result[2][3] = -m[0][0] * m[1][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1] + m[1][0] * m[0][1] * m[2][3] - m[1][0] * m[0][3] * m[2][1] - m[2][0] * m[0][1] * m[1][3] + m[2][0] * m[0][3] * m[1][1];
    result[3][3] =  m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] - m[1][0] * m[0][1] * m[2][2] + m[1][0] * m[0][2] * m[2][1] + m[2][0] * m[0][1] * m[1][2] - m[2][0] * m[0][2] * m[1][1];

    result = result*(1.0f/det);
    return result;
}

bool Matrix::operator==(const Matrix& b) const {
    return(r1==b[0] && r2==b[1] && r3==b[2] && r4==b[3]);
}

bool Matrix::operator!=(const Matrix& b) const {
    return !(r1==b[0] && r2==b[1] && r3==b[2] && r4==b[3]);
}

Matrix product(const Matrix& a, const Matrix& b) {
    float r10 = a.r1[0]*b.r1[0]+a.r1[1]*b.r2[0]+a.r1[2]*b.r3[0]+a.r1[3]*b.r4[0];
    float r11 = a.r1[0]*b.r1[1]+a.r1[1]*b.r2[1]+a.r1[2]*b.r3[1]+a.r1[3]*b.r4[1];
    float r12 = a.r1[0]*b.r1[2]+a.r1[1]*b.r2[2]+a.r1[2]*b.r3[2]+a.r1[3]*b.r4[2];
    float r13 = a.r1[0]*b.r1[3]+a.r1[1]*b.r2[3]+a.r1[2]*b.r3[3]+a.r1[3]*b.r4[3];
    float r20 = a.r2[0]*b.r1[0]+a.r2[1]*b.r2[0]+a.r2[2]*b.r3[0]+a.r2[3]*b.r4[0];
    float r21 = a.r2[0]*b.r1[1]+a.r2[1]*b.r2[1]+a.r2[2]*b.r3[1]+a.r2[3]*b.r4[1];
    float r22 = a.r2[0]*b.r1[2]+a.r2[1]*b.r2[2]+a.r2[2]*b.r3[2]+a.r2[3]*b.r4[2];
    float r23 = a.r2[0]*b.r1[3]+a.r2[1]*b.r2[3]+a.r2[2]*b.r3[3]+a.r2[3]*b.r4[3];
    float r30 = a.r3[0]*b.r1[0]+a.r3[1]*b.r2[0]+a.r3[2]*b.r3[0]+a.r3[3]*b.r4[0];
    float r31 = a.r3[0]*b.r1[1]+a.r3[1]*b.r2[1]+a.r3[2]*b.r3[1]+a.r3[3]*b.r4[1];
    float r32 = a.r3[0]*b.r1[2]+a.r3[1]*b.r2[2]+a.r3[2]*b.r3[2]+a.r3[3]*b.r4[2];
    float r33 = a.r3[0]*b.r1[3]+a.r3[1]*b.r2[3]+a.r3[2]*b.r3[3]+a.r3[3]*b.r4[3];
    float r40 = a.r4[0]*b.r1[0]+a.r4[1]*b.r2[0]+a.r4[2]*b.r3[0]+a.r4[3]*b.r4[0];
    float r41 = a.r4[0]*b.r1[1]+a.r4[1]*b.r2[1]+a.r4[2]*b.r3[1]+a.r4[3]*b.r4[1];
    float r42 = a.r4[0]*b.r1[2]+a.r4[1]*b.r2[2]+a.r4[2]*b.r3[2]+a.r4[3]*b.r4[2];
    float r43 = a.r4[0]*b.r1[3]+a.r4[1]*b.r2[3]+a.r4[2]*b.r3[3]+a.r4[3]*b.r4[3];
    
    return Matrix(
        Float4(r10,r11,r12,r13), 
        Float4(r20,r21,r22,r23),
        Float4(r30,r31,r32,r33),
        Float4(r40,r41,r42,r43));
}

Matrix operator*(const Matrix& a, float scalar) {
    return Matrix(
        Float4(a.r1[0]*scalar, a.r1[1]*scalar, a.r1[2]*scalar, a.r1[3]*scalar),
        Float4(a.r2[0]*scalar, a.r2[1]*scalar, a.r2[2]*scalar, a.r2[3]*scalar),
        Float4(a.r3[0]*scalar, a.r3[1]*scalar, a.r3[2]*scalar, a.r3[3]*scalar),
        Float4(a.r4[0]*scalar, a.r4[1]*scalar, a.r4[2]*scalar, a.r4[3]*scalar));
}

Matrix operator*(float scalar, const Matrix& a) {
    return Matrix(
        Float4(a.r1[0]*scalar, a.r1[1]*scalar, a.r1[2]*scalar, a.r1[3]*scalar),
        Float4(a.r2[0]*scalar, a.r2[1]*scalar, a.r2[2]*scalar, a.r2[3]*scalar),
        Float4(a.r3[0]*scalar, a.r3[1]*scalar, a.r3[2]*scalar, a.r3[3]*scalar),
        Float4(a.r4[0]*scalar, a.r4[1]*scalar, a.r4[2]*scalar, a.r4[3]*scalar));
}

Float4 Matrix::operator*(const Float4& b) const {
    return Float4(
        r1[0]*b[0]+r1[1]*b[1]+r1[2]*b[2]+r1[3]*b[3],
        r2[0]*b[0]+r2[1]*b[1]+r2[2]*b[2]+r2[3]*b[3],
        r3[0]*b[0]+r3[1]*b[1]+r3[2]*b[2]+r3[3]*b[3],
        r4[0]*b[0]+r4[1]*b[1]+r4[2]*b[2]+r4[3]*b[3]
        );
}

Vector Matrix::operator*(const Vector& b) const {
    Float4 f4(b);
    Float4 res = *this*(f4);
    return (Vector(res));
}

Point Matrix::operator*(const Point& b) const {
    Float4 f4(b);
    Float4 res = *this*(f4);
    return (Point(res));
}

float Matrix::det() const {
    return r1[3] * r2[2] * r3[1] * r4[0] - r1[2] * r2[3] * r3[1] * r4[0] -
         r1[3] * r2[1] * r3[2] * r4[0] + r1[1] * r2[3] * r3[2] * r4[0] +
         r1[2] * r2[1] * r3[3] * r4[0] - r1[1] * r2[2] * r3[3] * r4[0] -
         r1[3] * r2[2] * r3[0] * r4[1] + r1[2] * r2[3] * r3[0] * r4[1] +
         r1[3] * r2[0] * r3[2] * r4[1] - r1[0] * r2[3] * r3[2] * r4[1] -
         r1[2] * r2[0] * r3[3] * r4[1] + r1[0] * r2[2] * r3[3] * r4[1] +
         r1[3] * r2[1] * r3[0] * r4[2] - r1[1] * r2[3] * r3[0] * r4[2] -
         r1[3] * r2[0] * r3[1] * r4[2] + r1[0] * r2[3] * r3[1] * r4[2] +
         r1[1] * r2[0] * r3[3] * r4[2] - r1[0] * r2[1] * r3[3] * r4[2] -
         r1[2] * r2[1] * r3[0] * r4[3] + r1[1] * r2[2] * r3[0] * r4[3] +
         r1[2] * r2[0] * r3[1] * r4[3] - r1[0] * r2[2] * r3[1] * r4[3] -
         r1[1] * r2[0] * r3[2] * r4[3] + r1[0] * r2[1] * r3[2] * r4[3];
}

Matrix Matrix::zero() {
    return Matrix(
        Float4(0,0,0,0),
        Float4(0,0,0,0),
        Float4(0,0,0,0),
        Float4(0,0,0,0));
}

Matrix Matrix::identity() {
    return Matrix(
        Float4(1,0,0,0),
        Float4(0,1,0,0),
        Float4(0,0,1,0),
        Float4(0,0,0,1));
}

Matrix Matrix::system(const Vector& e1, const Vector& e2, const Vector& e3) {
    return(Matrix(
        Float4(e1.x, e2.x, e3.x, 0),
        Float4(e1.y, e2.y, e3.y, 0),
        Float4(e1.z, e2.z, e3.z, 0),
        Float4(0, 0, 0, 1)
    ));
}

}