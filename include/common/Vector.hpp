#pragma once

// ONLY GAME TYPE //

#include "pch.hpp"

template<typename T = int32_t>
struct Vec3
{
    T x = 0, y = 0, z = 0;

    bool operator==(const Vec3&) const = default;

    constexpr Vec3 operator-() const noexcept { return {-x, -y, -z}; }

    constexpr Vec3 operator+(const Vec3& rhs) const noexcept
    {
        return {x + rhs.x, y + rhs.y, z + rhs.z};
    }

    constexpr Vec3 operator-(const Vec3& rhs) const noexcept
    {
        return {x - rhs.x, y - rhs.y, z - rhs.z};
    }

    constexpr Vec3& operator+=(const Vec3& rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    constexpr Vec3& operator-=(const Vec3& rhs) noexcept
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    constexpr Vec3 operator*(T s) const noexcept
    {
        return {x * s, y * s, z * s};
    }

    constexpr Vec3 operator/(T s) const noexcept
    {
        return {x / s, y / s, z / s};
    }

    constexpr Vec3& operator*=(T s) noexcept
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    constexpr Vec3& operator/=(T s) noexcept
    {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    constexpr int& operator[](size_t i) noexcept
    {
        return (&x)[i];
    }

    constexpr const int& operator[](size_t i) const noexcept
    {
        return (&x)[i];
    }

    friend constexpr Vec3 operator*(T s, const Vec3& v) noexcept
    {
        return v * s;
    }
};

template<>
struct std::hash<Vec3<uint64_t>>
{
    size_t operator()(const Vec3<uint64_t>& v) const noexcept
    {
        size_t h = std::hash<uint64_t>{}(v.x);
        h ^= std::hash<uint64_t>{}(v.y) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<uint64_t>{}(v.z) + 0x9e3779b9 + (h << 6) + (h >> 2);
        return h;
    }
};

template<>
struct std::hash<Vec3<uint32_t>>
{
    size_t operator()(const Vec3<uint32_t>& v) const noexcept
    {
        size_t h = std::hash<uint32_t>{}(v.x);
        h ^= std::hash<uint32_t>{}(v.y) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<uint32_t>{}(v.z) + 0x9e3779b9 + (h << 6) + (h >> 2);
        return h;
    }
};

template<>
struct std::hash<Vec3<int64_t>>
{
    size_t operator()(const Vec3<int64_t>& v) const noexcept
    {
        size_t h = std::hash<int64_t>{}(v.x);
        h ^= std::hash<int64_t>{}(v.y) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<int64_t>{}(v.z) + 0x9e3779b9 + (h << 6) + (h >> 2);
        return h;
    }
};

template<>
struct std::hash<Vec3<int32_t>>
{
    size_t operator()(const Vec3<int32_t>& v) const noexcept
    {
        size_t h = std::hash<int32_t>{}(v.x);
        h ^= std::hash<int32_t>{}(v.y) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= std::hash<int32_t>{}(v.z) + 0x9e3779b9 + (h << 6) + (h >> 2);
        return h;
    }
};

using vec3i16 = Vec3<int16_t>;
using vec3i32 = Vec3<int32_t>;
using vec3i64 = Vec3<int64_t>;

using vec3u16 = Vec3<uint16_t>;
using vec3u32 = Vec3<uint32_t>;
using vec3u64 = Vec3<uint64_t>;

using vec3f32 = Vec3<float>;
using vec3f64 = Vec3<double>;




template<typename T = int32_t>
struct Vec2
{
    T x = 0, y = 0;

    bool operator==(const Vec2&) const = default;

    constexpr Vec2 operator-() const noexcept { return {-x, -y}; }

    constexpr Vec2 operator+(const Vec2& rhs) const noexcept
    {
        return {x + rhs.x, y + rhs.y};
    }

    constexpr Vec2 operator-(const Vec2& rhs) const noexcept
    {
        return {x - rhs.x, y - rhs.y};
    }

    constexpr Vec2& operator+=(const Vec2& rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    constexpr Vec2& operator-=(const Vec2& rhs) noexcept
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    constexpr Vec2 operator*(T s) const noexcept
    {
        return {x * s, y * s};
    }

    constexpr Vec2 operator/(T s) const noexcept
    {
        return {x / s, y / s};
    }

    constexpr Vec2& operator*=(T s) noexcept
    {
        x *= s;
        y *= s;
        return *this;
    }

    constexpr Vec2& operator/=(T s) noexcept
    {
        x /= s;
        y /= s;
        return *this;
    }

    constexpr int& operator[](size_t i) noexcept
    {
        return (&x)[i];
    }

    constexpr const int& operator[](size_t i) const noexcept
    {
        return (&x)[i];
    }

    friend constexpr Vec2 operator*(T s, const Vec2& v) noexcept
    {
        return v * s;
    }
};

template<>
struct std::hash<Vec2<uint64_t>>
{
    size_t operator()(const Vec3<uint64_t>& v) const noexcept
    {
        size_t h = std::hash<uint64_t>{}(v.x);
        h ^= std::hash<uint64_t>{}(v.y) + 0x9e3779b9 + (h << 6) + (h >> 2);
        return h;
    }
};

template<>
struct std::hash<Vec2<uint32_t>>
{
    size_t operator()(const Vec3<uint32_t>& v) const noexcept
    {
        return (uint64_t(uint32_t(v.x)) << 32) | uint32_t(v.z);
    }
};

template<>
struct std::hash<Vec2<int64_t>>
{
    size_t operator()(const Vec3<uint64_t>& v) const noexcept
    {
        size_t h = std::hash<uint64_t>{}(v.x);
        h ^= std::hash<uint64_t>{}(v.y) + 0x9e3779b9 + (h << 6) + (h >> 2);
        return h;
    }
};

template<>
struct std::hash<Vec2<int32_t>>
{
    size_t operator()(const Vec3<uint32_t>& v) const noexcept
    {
        return (uint64_t(int32_t(v.x)) << 32) | int32_t(v.z);
    }
};
