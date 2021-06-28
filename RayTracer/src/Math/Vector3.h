#pragma once

namespace RayT
{
    class Vector3
    {
    public:
        Vector3();
        Vector3(double X, double Y, double Z);

        ~Vector3();

        Vector3(const Vector3 &v);
        Vector3 &operator=(const Vector3 &v);

        Vector3 operator+(const Vector3 &v) const;
        Vector3 operator-(const Vector3 &v) const;
        Vector3 operator*(const double s) const;
        Vector3 operator/(const double s) const;
        Vector3 operator%(const Vector3 &v) const;

        void operator+=(const Vector3 &v);
        void operator-=(const Vector3 &v);
        void operator*=(const double s);
        void operator/=(const double s);
        void operator%=(const Vector3 &v);

        double operator*(const Vector3 &v) const;

        double dot(const Vector3 &v) const;

        Vector3 cross(const Vector3 &v) const;
        Vector3 unitVector(Vector3 v);

        void conjugate();
        void normalize();
        double magnitude();
        double magnitudeSquare();
        void zero();
        void absolute();

        void show();
        void negate();

        double GetX() { return x; }
        double GetY() { return y; }
        double GetZ() { return z; }

    private:
        double x, y, z;
    };

    using point3 = Vector3; // 3D point
    using color = Vector3;  // RGB color
}