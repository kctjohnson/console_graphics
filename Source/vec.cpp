#include <cmath>
#include <stdio.h>

#include "../Headers/vec.h"

vec2d::vec2d(double x, double y) {
    this->x = x;
    this->y = y;
}

vec2d vec2d::calculateRemainder(double x, double y) {
    if (x != 0) {
        this->x = (long)this->x % (long)x;
    }

    if (y != 0) {
        this->y = (long)this->y % (long)y;
    }

    return *this;
}

std::string vec2d::toString() {
    char tmpStr[50];
    sprintf(tmpStr, "(%f, %f)\n", this->x, this->y);
    return std::string(tmpStr);
}

void vec2d::set(double x, double y) {
    this->x = x;
    this->y = y;
}

void vec2d::set(vec2d vec) {
    this->x = vec.x;
    this->y = vec.y;
}

vec2d vec2d::copy() {
    return vec2d(this->x, this->y);
}

void vec2d::add(double x, double y) {
    this->x += x;
    this->y += y;
}

void vec2d::add(vec2d vec) {
    this->x += vec.x;
    this->y += vec.y;
}

void vec2d::sub(double x, double y) {
    this->x -= x;
    this->y -= y;
}

void vec2d::sub(vec2d vec) {
    this->x -= vec.x;
    this->y -= vec.y;
}

void vec2d::rem(double x, double y) {
    calculateRemainder(x, y);
}

void vec2d::rem(vec2d vec) {
    calculateRemainder(vec.x, vec.y);
}

void vec2d::mult(double scalar) {
    this->x *= scalar;
    this->y *= scalar;
}

void vec2d::mult(double x, double y) {
    this->x *= x;
    this->y *= y;
}

void vec2d::mult(vec2d vec) {
    this->x *= vec.x;
    this->y *= vec.y;
}

void vec2d::div(double scalar) {
    if (scalar == 0) {
        throw "Divide by zero error, vec2d::div";
    }

    this->x /= scalar;
    this->y /= scalar;
}

void vec2d::div(double x, double y) {
    if (x == 0 || y == 0) {
        throw "Divide by zero error, vec2d::div";
    }

    this->x /= x;
    this->y /= y;
}

void vec2d::div(vec2d vec) {
    if (vec.x == 0 || vec.y == 0) {
        throw "Divide by zero error, vec2d::div";
    }

    this->x /= vec.x;
    this->y /= vec.y;
}

double vec2d::mag() {
    return std::sqrt(this->magSq());
}

double vec2d::magSq() {
    double x = this->x;
    double y = this->y;
    return x * x + y * y;
}

void vec2d::setMag(double mag) {
    this->normalize();
    this->mult(mag);
}

double vec2d::dot(double x, double y) {
    return this->x * x + this->y * y;
}

double vec2d::dot(vec2d vec) {
    return this->dot(vec.x, vec.y);
}

double vec2d::cross(vec2d vec) {
    return this->x * vec.y - this->y * vec.x;
}

double vec2d::dist(vec2d vec) {
    vec2d tmp = vec.copy();
    tmp.sub(*this);
    return tmp.mag();
}

void vec2d::normalize() {
    const double len = this->mag();
    if (len != 0) {
        this->mult(1 / len);
    }
}

void vec2d::limit(double max) {
    const double mSq = this->magSq();
    if (mSq > max * max) {
        this->div(std::sqrt(mSq));
        this->mult(max);
    }
}

double vec2d::heading() {
    return std::atan2(this->y, this->x);
}

void vec2d::setHeading(double angle) {
    double mag = this->mag();
    this->x = mag * std::cos(angle);
    this->y = mag * std::sin(angle);
}

void vec2d::rotate(double angle) {
    double newHeading = this->heading() + angle;
    const double mag = this->mag();
    this->x = std::cos(newHeading) * mag;
    this->y = std::sin(newHeading) * mag;
}

double vec2d::angleBetween(vec2d vec) {
    const double dotmagmag = this->dot(vec) / (this->mag() * vec.mag());
    double angle = std::acos(std::min(1.0, std::max(-1.0, dotmagmag)));
    angle = angle * copysign(1.0, this->cross(vec) || 1);
    return angle;
}

void vec2d::lerp(vec2d vec, double amount) {
    this->x += (vec.x - this->x) * amount;
    this->y += (vec.y - this->y) * amount;
}

void vec2d::reflect(vec2d surfaceNormal) {
    vec2d tmpVec = surfaceNormal.copy();
    tmpVec.normalize();
    tmpVec.mult(2 * this->dot(tmpVec));
    this->sub(tmpVec);
}

bool vec2d::equals(vec2d vec) {
    return this->x == vec.x && this->y == vec.y;
}

bool vec2d::equals(double x, double y) {
    return this->x == x && this->y == y;
}

vec2d vec2dFromAngle(double angle, double length) {
    return vec2d(length * std::cos(angle), length * std::sin(angle));
}
