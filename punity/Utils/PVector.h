//
// Created by god on 10.11.2022.
//

#ifndef _VECTOR_H
#define _VECTOR_H

#include <cmath>
#include <string>

namespace Punity::Utils {
    struct PVector {
    public:
        float x = 0, y = 0;

        PVector() : x(0), y(0) {}

        PVector(float x, float y) : x(x), y(y) {}

        PVector(const PVector &v) = default;

        PVector &operator=(const PVector &v) = default;


        float mag() const {
            return std::sqrt(x * x + y * y);
        }

        float dot(const PVector &v) const {
            return this->x * v.x + this->y * v.y;
        }

        float cross(const PVector &v) const {
            return this->x * v.y - this->y * v.x;
        }

        PVector norm() const {
            float _mag = mag();

            // If magnitude is extremely close to 0, the vector is 0, 0
            if (std::abs(_mag) < 1e-8) return PVector(0, 0);

            return PVector(x / _mag, y / _mag);
        }

        PVector operator+(const PVector &v) const {
            return PVector(this->x + v.x, this->y + v.y);
        }

        PVector operator-(const PVector &v) const {
            return PVector(this->x - v.x, this->y - v.y);
        }

        PVector operator*(const PVector &v) const {
            return PVector(this->x * v.x, this->y * v.y);
        }

        PVector operator/(const PVector &v) const {
            return PVector(this->x / v.x, this->y / v.y);
        }

        PVector operator*(const float a) const {
            return PVector(this->x * a, this->y * a);
        }

        PVector operator/(const float a) const {
            return PVector(this->x / a, this->y / a);
        }

        PVector operator+() const {
            return PVector(+this->x, +this->y);
        }

        PVector operator-() const {
            return PVector(-this->x, -this->y);
        }

        PVector &operator+=(const PVector &v) {
            this->x += v.x;
            this->y += v.y;
            return *this;
        }

        PVector &operator-=(const PVector &v) {
            this->x -= v.x;
            this->y -= v.y;
            return *this;
        }

        PVector &operator*=(const PVector &v) {
            this->x *= v.x;
            this->y *= v.y;
            return *this;
        }

        PVector &operator/=(const PVector &v) {
            this->x /= v.x;
            this->y /= v.y;
            return *this;
        }

        PVector &operator*=(const float a) {
            this->x *= a;
            this->y *= a;
            return *this;
        }

        PVector &operator/=(const float a) {
            this->x /= a;
            this->y /= a;
            return *this;
        }

        bool operator==(const PVector &v) const {
            return this->x == v.x && this->y == v.y;
        }

        bool operator!=(const PVector &v) const {
            return this->x != v.x || this->y != v.y;
        }

        const std::string str() const {
            return std::string("(") + std::to_string(this->x) +
                   "," + std::to_string(this->y) + ")";
        }

        friend std::ostream &operator<<(std::ostream &os, const PVector &v) {
            os << v.str();
            return os;
        }
    };
}

#endif //_VECTOR_H
