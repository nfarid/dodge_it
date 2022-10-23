
#ifndef HPP_UTIL_VEC2_1657498456_
#define HPP_UTIL_VEC2_1657498456_

#include "dimension.hpp"
#include "real.hpp"


namespace Util
{


/**
 * @brief A two dimensional vector class
 * @tparam U - the underlying type
 */
template<typename U>
struct Vec2 {
    using Underlying = U;

    U x;
    U y;

    [[nodiscard]] static constexpr Vec2 zero() noexcept {
        return {U{}, U{} };
    }

    [[nodiscard]] constexpr bool isZero() const noexcept {
        return x == U{} && y == U{};
    }

    [[nodiscard]] constexpr auto squareMag() const {
        return x*x + y*y;
    }

    [[nodiscard]] auto magnitude() const {
        return sqrt(x*x + y*y);
    }

    [[nodiscard]] auto unit() const {
        const auto vecMag = magnitude();
        using NoUnit = decltype(std::declval<U>() / vecMag);
        return Vec2<NoUnit>{
            x/vecMag,
            y/vecMag,
        };
    }

    template<typename V>
    constexpr explicit operator Vec2<V>() const {
        return {static_cast<V>(x), static_cast<V>(y)};
    }
};


// Typedefs

template<typename T, typename R>
using Position = Vec2<PositionScalar<T, R> >;
template<typename T, typename R>
using Displacement = Vec2<Distance<T, R> >;

template<typename T, typename R>
using Velocity = Vec2<Speed<T, R> >;

template<typename T, typename R>
using Acceleration = Vec2<AccelerationScalar<T, R> >;

template<typename T, typename R>
using Momentum = Vec2<MomentumScalar<T, R> >;
template<typename T, typename R>
using Impulse = Vec2<ImpulseScalar<T, R> >;

template<typename T, typename R>
using Force = Vec2<ForceScalar<T, R> >;


// Base typedefs
using BasePosition = Position<Real, BaseRatio>;
using BaseDisplacement = Displacement<Real, BaseRatio>;
using BaseVelocity = Velocity<Real, BaseRatio>;
using BaseAcceleration = Acceleration<Real, BaseRatio>;
using BaseMomentum = Momentum<Real, BaseRatio>;
using BaseImpulse = Impulse<Real, BaseRatio>;
using BaseForce = Force<Real, BaseRatio>;


// Functions

template<typename U1, typename U2>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
dot(const Vec2<U1>& lhs, const Vec2<U2>& rhs) {
    return lhs.x * rhs.x  + lhs.y * rhs.y;
}

template<typename U1, typename U2>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
elemMul(const Vec2<U1>& lhs, const Vec2<U2>& rhs) {
    using Uout = decltype(std::declval<U1>() * std::declval<U2>() );
    return Vec2<Uout>{lhs.x * rhs.x, lhs.y * rhs.y};
}

template<typename U1, typename U2>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
elemDiv(const Vec2<U1>& lhs, const Vec2<U2>& rhs) {
    using Uout = decltype(std::declval<U1>() / std::declval<U2>() );
    return Vec2<Uout>{lhs.x / rhs.x, lhs.y / rhs.y};
}


// Operators

template<typename U>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr Vec2<U>
operator-(const Vec2<U>& vec) {
    return {-vec.x, -vec.y};
}

template<typename U>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr Vec2<U>
operator+(const Vec2<U>& lhs, const Vec2<U>& rhs) {
    return {lhs.x + rhs.x,  lhs.y + rhs.y};
}

template<typename U>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr Vec2<U>
operator-(const Vec2<U>& lhs, const Vec2<U>& rhs) {
    return {lhs.x - rhs.x,  lhs.y - rhs.y};
}

template<typename U>
UTIL_ALWAYS_INLINE constexpr Vec2<U>&
operator+=(Vec2<U>& lhs, const Vec2<U>& rhs) {
    return lhs = lhs + rhs;
}

template<typename U>
UTIL_ALWAYS_INLINE constexpr Vec2<U>&
operator-=(Vec2<U>& lhs, const Vec2<U>& rhs) {
    return lhs = lhs - rhs;
}

template<typename T, typename U>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
operator*(const Vec2<U>& lhs, const T& rhs) {
    using Uout = decltype(std::declval<U>() * std::declval<T>() );
    return Vec2<Uout>{lhs.x * rhs,  lhs.y * rhs};
}

template<typename T, typename U>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
operator*(const T& lhs, const Vec2<U>& rhs) {
    using Uout = decltype(std::declval<T>() * std::declval<U>() );
    return Vec2<Uout>{lhs* rhs.x,  lhs* rhs.y};
}

template<typename T, typename U>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
operator/(const Vec2<U>& lhs, const T& rhs) {
    using Uout = decltype(std::declval<U>() / std::declval<T>() );
    return Vec2<Uout>{lhs.x / rhs,  lhs.y / rhs};
}

template<typename T, typename U>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
operator/(const T& lhs, const Vec2<U>& rhs) {
    using Uout = decltype(std::declval<T>() / std::declval<U>() );
    return Vec2<Uout>{lhs / rhs.x,  lhs / rhs.y};
}

template<typename T, typename U>
UTIL_ALWAYS_INLINE constexpr Vec2<U>&
operator*=(Vec2<U>& lhs, const T& rhs) {
    return lhs = lhs * rhs;
}

template<typename T, typename U>
UTIL_ALWAYS_INLINE constexpr Vec2<U>&
operator/=(Vec2<U>& lhs, const T& rhs) {
    return lhs = lhs / rhs;
}

template<typename T>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr bool
operator==(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return lhs.x == rhs.x  &&  lhs.y == rhs.y;
}

template<typename T>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr bool
operator!=(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return !(lhs == rhs);
}

template<typename T>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr bool
equal(const Vec2<T>& lhs, const Vec2<T>& rhs) {
    return equal(lhs.x, rhs.x) && equal(lhs.y, rhs.y);
}

template<typename T>
[[nodiscard]] inline constexpr bool
nearly_equal(Vec2<T> lhs, Vec2<T> rhs) {
    return nearly_equal(lhs.x, rhs.x) && nearly_equal(lhs.y, rhs.y);
}

// Utility functions

template<typename T>
std::ostream& operator<<(std::ostream& os, Vec2<T> vec) {
    return os<<"{"<<vec.x<<", "<<vec.y<<"} ";
}


}  // namespace Util

#endif  // HPP_UTIL_VEC2_1657498456_
