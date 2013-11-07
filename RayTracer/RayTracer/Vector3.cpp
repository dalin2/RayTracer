//
//  Vector3.cpp
//  Ray Tracer
//
//  Created by Dustin Alin on 11/3/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "Vector3.h"

Vector3::Vector3(float x, float y, float z) {
    e[0] = x;
    e[1] = y;
    e[2] = z;
}

const Vector3& Vector3::operator+() const {
    return *this;
}

Vector3 Vector3::operator-() const {
    return Vector3(-e[0], -e[1], -e[2]);
}

float Vector3::magnitude() const {
    return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
}

float Vector3::squaredMagnitude() const {
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}

void Vector3::normalize() {
    *this = *this / (*this).magnitude();
}

float Vector3::minComponent() const {
    float temp = e[0];
    if (e[1] < temp) temp = e[1];
    if (e[2] < temp) temp = e[2];
    
    return temp;
}

float Vector3::maxComponent() const {
    float temp = e[0];
    if (e[1] > temp) temp = e[1];
    if (e[2] > temp) temp = e[2];
    
    return temp;
}

float Vector3::minAbsComponent() const {
    float temp = fabs(e[0]);
    if (fabs(e[1]) < temp) temp = fabs(e[1]);
    if (fabs(e[2]) < temp) temp = fabs(e[2]);
    
    return temp;
}

float Vector3::maxAbsComponent() const {
    float temp = fabs(e[0]);
    if (fabs(e[1]) > temp) temp = fabs(e[1]);
    if (fabs(e[2]) > temp) temp = fabs(e[2]);
    
    return temp;
}

bool operator==(const Vector3& v1, const Vector3& v2) {
    if (v1.getX() != v2.getX()) return false;
    if (v1.getY() != v2.getY()) return false;
    if (v1.getZ() != v2.getZ()) return false;
    return true;
}

bool operator!=(const Vector3& v1, const Vector3& v2) {
    return !(v1 == v2);
}

Vector3 operator+(const Vector3& v1, const Vector3& v2) {
    return Vector3(v1.getX() + v2.getX(), v1.getY() + v2.getY(), v1.getZ() + v2.getZ());
}

Vector3 operator-(const Vector3& v1, const Vector3& v2) {
    return Vector3(v1.getX() - v2.getX(), v1.getY() - v2.getY(), v1.getZ() - v2.getZ());
}

Vector3 operator/(const Vector3& v1, float scal) {
    return Vector3(v1.getX() / scal, v1.getY() / scal, v1.getZ() / scal);
}

Vector3 operator*(const Vector3& v1, float scal) {
    return Vector3(v1.getX() * scal, v1.getY() * scal, v1.getZ() * scal);
}

Vector3 operator*(float scal, const Vector3& v1) {
    return Vector3(v1.getX() * scal, v1.getY() * scal, v1.getZ() * scal);
}

Vector3& Vector3::operator=(const Vector3& v2) {
    (*this).setX(v2.getX());
    (*this).setY(v2.getY());
    (*this).setZ(v2.getZ());
    return *this;
}

Vector3& Vector3::operator+=(const Vector3& v2) {
    *this = *this + v2;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& v2) {
    *this = *this - v2;
    return *this;
}

Vector3& Vector3::operator*=(const float scal) {
    *this = *this * scal;
    return *this;
}

Vector3& Vector3::operator/=(const float scal) {
    *this = *this / scal;
    return *this;
}

Vector3 cross(const Vector3& v1, const Vector3& v2) {
    float x = v1.getY() * v2.getZ() - v1.getZ() * v2.getY();
    float y = v1.getZ() * v2.getX() - v1.getX() * v2.getZ();
    float z = v1.getX() * v2.getY() - v1.getY() * v2.getX();
    return Vector3(x, y, z);
}

float dot(const Vector3& v1, const Vector3& v2) {
    return v1.getX() * v2.getX() + v1.getY() * v2.getY() + v1.getZ() * v2.getZ();
}

float tripleProduct(const Vector3& v1, const Vector3& v2, const Vector3& v3) {
    return dot(cross(v1, v2), v3);
}

Vector3 normalize(const Vector3& v) {
    return v / v.magnitude();
}
