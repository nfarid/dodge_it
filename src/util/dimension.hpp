
#ifndef HPP_UTIL_DIMENSION_1657307060_
#define HPP_UTIL_DIMENSION_1657307060_

#include "macros.hpp"
#include "real.hpp"
#include "typedefs.hpp"

#include <chrono>
#include <cmath>
#include <cstdint>
#include <ostream>
#include <ratio>
#include <type_traits>
#include <utility>


namespace Util
{


using Real = float;

/**
 * @brief Strong typed dimension to represent phyiscal quantities
 * @tparam T - the underlying arithmetic type
 * @tparam L - the length dimension
 * @tparam M - the mass dimension
 * @tparam S - the time dimension
 * @tparam R - the ratio from the base unit
 */
template<typename T, int L, int M, int S, typename R>
struct Dim {
    using Underlying = T;
    inline static constexpr int lengthDimension = L;
    inline static constexpr int massDimension = M;
    inline static constexpr int timeDimension = S;
    using Ratio = R;
    inline static constexpr intmax_t RatioNumerator = Ratio::num;
    inline static constexpr intmax_t RatioDenominator = Ratio::den;


    T value;

    [[nodiscard]] constexpr static Dim zero() noexcept {
        return Dim{T{} };
    }

    [[nodiscard]] constexpr bool isZero() const noexcept {
        return equal(value, T{});
    }

    template<typename TOut, typename ROut>
    constexpr explicit operator Dim<TOut, L, M, S, ROut>() const {
        using Ct = std::common_type_t<T, TOut, intmax_t>;
        using Rt = std::ratio_divide<R, ROut>;
        return Dim<TOut, L, M, S, ROut>{static_cast<TOut>(static_cast<Ct>(value)
                                        * static_cast<Ct>(Rt::num) / static_cast<Ct>(Rt::den) )};
    }

    template<int L_ = L, int M_ = M, int S_ = S,
            typename E_ = std::enable_if_t<(L_ == 0 && M_ == 0 && S_ == 0)> >
    constexpr /*[[implicit]]*/ operator T() const {
        return value * R::num / R::den;
    }
};



// Typedefs for some dimensions

template<typename T, typename R>
using Unitless = Dim<T, 0, 0, 0, R>;

template<typename T, typename R>
using Length = Dim<T, 1, 0, 0, R>;
template<typename T, typename R>
using PositionScalar = Length<T, R>;
template<typename T, typename R>
using Distance = Length<T, R>;

template<typename T, typename R>
using Mass = Dim<T, 0, 1, 0, R>;

template<typename T, typename R>
using InverseMass = Dim<T, 0, -1, 0, R>;

template<typename T, typename R>
using Duration = Dim<T, 0, 0, 1, R>;

template<typename T, typename R>
using Frequency = Dim<T, 0, 0, -1, R>;

template<typename T, typename R>
using Area = Dim<T, 2, 0, 0, R>;

template<typename T, typename R>
using Speed = Dim<T, 1, 0, -1, R>;

template<typename T, typename R>
using AccelerationScalar = Dim<T, 1, 0, -2, R>;

template<typename T, typename R>
using MomentumScalar = Dim<T, 1, 1, -1, R>;
template<typename T, typename R>
using ImpulseScalar = MomentumScalar<T, R>;

template<typename T, typename R>
using ForceScalar = Dim<T, 1, 1, -2, R>;


// Base dimensions

using BaseRatio = std::ratio<1, 1>;
using BaseLength = Length<Real, BaseRatio>;
using BasePositionScalar = PositionScalar<Real, BaseRatio>;
using BaseDistance = Distance<Real, BaseRatio>;
using BaseMass = Mass<Real, BaseRatio>;
using BaseInverseMass = InverseMass<Real, BaseRatio>;
using Second = Duration<Real, BaseRatio>;
using Hertz = Frequency<Real, BaseRatio>;
using BaseArea = Area<Real, BaseRatio>;
using BaseSpeed = Speed<Real, BaseRatio>;
using BaseAccelerationScalar = AccelerationScalar<Real, BaseRatio>;
using BaseMomentumScalar = MomentumScalar<Real, BaseRatio>;
using BaseImpulseScalar = ImpulseScalar<Real, BaseRatio>;
using BaseForceScalar = ForceScalar<Real, BaseRatio>;


// Literals

inline namespace Udl
{


[[nodiscard]] constexpr BaseLength operator"" _bl(long double f) noexcept {
    return BaseLength{static_cast<Real>(f)};
}

[[nodiscard]] constexpr BaseLength operator"" _bl(unsigned long long int i) noexcept {
    return BaseLength{static_cast<Real>(i)};
}

[[nodiscard]] constexpr BaseSpeed operator"" _blPs(long double f) noexcept {
    return BaseSpeed{static_cast<Real>(f)};
}

[[nodiscard]] constexpr BaseSpeed operator"" _blPs(unsigned long long int i) noexcept {
    return BaseSpeed{static_cast<Real>(i)};
}

[[nodiscard]] constexpr BaseMass operator"" _bm(long double f) noexcept {
    return BaseMass{static_cast<Real>(f)};
}

[[nodiscard]] constexpr BaseMass operator"" _bm(unsigned long long int i) noexcept {
    return BaseMass{static_cast<Real>(i)};
}

[[nodiscard]] constexpr Second operator"" _s(long double f) noexcept {
    return Second{static_cast<Real>(f)};
}

[[nodiscard]] constexpr Second operator"" _s(unsigned long long int i) noexcept {
    return Second{static_cast<Real>(i)};
}

[[nodiscard]] constexpr Hertz operator"" _hz(long double f) noexcept {
    return Hertz{static_cast<Real>(f)};
}

[[nodiscard]] constexpr Hertz operator"" _hz(unsigned long long int i) noexcept {
    return Hertz{static_cast<Real>(i)};
}


}  // namespace Udl



// Operators

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
operator -(const Dim<T, L, M, S, R>& dim) {
    return Dim<T, L, M, S, R>{-dim.value};
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
operator +(const Dim<T, L, M, S, R>& lhs, const Dim<T, L, M, S, R>& rhs) {
    return Dim<T, L, M, S, R>{lhs.value + rhs.value};
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
operator -(const Dim<T, L, M, S, R>& lhs, const Dim<T, L, M, S, R>& rhs) {
    return Dim<T, L, M, S, R>{lhs.value - rhs.value};
}

template<typename T, int L, int M, int S, typename R>
UTIL_ALWAYS_INLINE constexpr auto&
operator +=(Dim<T, L, M, S, R>& lhs, const Dim<T, L, M, S, R>& rhs) {
    lhs.value += rhs.value;
    return lhs;
}

template<typename T, int L, int M, int S, typename R>
UTIL_ALWAYS_INLINE constexpr auto&
operator -=(Dim<T, L, M, S, R>& lhs, const Dim<T, L, M, S, R>& rhs) {
    lhs.value -= rhs.value;
    return lhs;
}

template<typename T, int L1, int L2, int M1, int M2, int S1, int S2, typename R1, typename R2>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
operator *(const Dim<T, L1, M1, S1, R1>& lhs, const Dim<T, L2, M2, S2, R2>& rhs) {
    using Rout = std::ratio_multiply<R1, R2>;
    return Dim<T, L1 + L2, M1 + M2, S1 + S2, Rout>{lhs.value * rhs.value};
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
operator *(const Dim<T, L, M, S, R>& lhs, const T& rhs) {
    return Dim<T, L, M, S, R>{lhs.value * rhs};
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
operator *(const T& lhs, const Dim<T, L, M, S, R>& rhs) {
    return Dim<T, L, M, S, R>{lhs* rhs.value};
}

template<typename T, int L1, int L2, int M1, int M2, int S1, int S2, typename R1, typename R2>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
operator /(const Dim<T, L1, M1, S1, R1>& lhs, const Dim<T, L2, M2, S2, R2>& rhs) {
    using Rout = std::ratio_divide<R1, R2>;
    return Dim<T, L1 - L2, M1 - M2, S1 - S2, Rout>{lhs.value / rhs.value};
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
operator /(const Dim<T, L, M, S, R>& lhs, const T& rhs) {
    return Dim<T, L, M, S, R>{lhs.value / rhs};
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
operator /(const T& lhs, const Dim<T, L, M, S, R>& rhs) {
    return Dim<T, -L, -M, -S, R>{lhs / rhs.value};
}

template<typename T, int L, int M, int S, typename R>
UTIL_ALWAYS_INLINE constexpr auto&
operator *=(Dim<T, L, M, S, R>& lhs, const T& rhs) {
    lhs.value *= rhs;
    return lhs;
}

template<typename T, int L, int M, int S, typename R>
UTIL_ALWAYS_INLINE constexpr auto&
operator *=(Dim<T, L, M, S, R>& lhs, const Unitless<T, R>& rhs) {
    lhs.value *= rhs.value;
    return lhs;
}

template<typename T, int L, int M, int S, typename R>
UTIL_ALWAYS_INLINE constexpr auto&
operator /=(Dim<T, L, M, S, R>& lhs, const T& rhs) {
    lhs.value /= rhs;
    return lhs;
}

template<typename T, int L, int M, int S, typename R>
UTIL_ALWAYS_INLINE constexpr auto&
operator /=(Dim<T, L, M, S, R>& lhs, const Unitless<T, R>& rhs) {
    lhs.value /= rhs.value;
    return lhs;
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr bool
operator <(const Dim<T, L, M, S, R>& lhs, const Dim<T, L, M, S, R>& rhs) {
    return lhs.value < rhs.value;
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr bool
operator >(const Dim<T, L, M, S, R>& lhs, const Dim<T, L, M, S, R>& rhs) {
    return lhs.value > rhs.value;
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr bool
operator <=(const Dim<T, L, M, S, R>& lhs, const Dim<T, L, M, S, R>& rhs) {
    return lhs.value <= rhs.value;
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr bool
operator >=(const Dim<T, L, M, S, R>& lhs, const Dim<T, L, M, S, R>& rhs) {
    return lhs.value >= rhs.value;
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr bool
operator ==(const Dim<T, L, M, S, R>& lhs, const Dim<T, L, M, S, R>& rhs) {
    return equal(lhs.value, rhs.value);
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr bool
operator !=(const Dim<T, L, M, S, R>& lhs, const Dim<T, L, M, S, R>& rhs) {
    return lhs.value != rhs.value;
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr bool
equal(const Dim<T, L, M, S, R>& lhs, const Dim<T, L, M, S, R>& rhs) noexcept {
    return equal(lhs.value, rhs.value);
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] inline constexpr bool
nearly_equal(Dim<T, L, M, S, R> lhs, Dim<T, L, M, S, R> rhs, Dim<T, L, M, S, R> ep)
{
    return nearly_equal(lhs.value, rhs.value, ep.value);
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] inline constexpr bool
nearly_equal(Dim<T, L, M, S, R> lhs, Dim<T, L, M, S, R> rhs, T ep)
{
    return nearly_equal(lhs.value, rhs.value, ep);
}



// Utility functions

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] inline auto sqrt(Dim<T, L, M, S, R> u) {
    constexpr static auto isEven = [](int x){return (x%2)==0;};
    static_assert(isEven(L), "length dimension must be even");
    static_assert(isEven(M), "mass dimension must be even");
    static_assert(isEven(S), "time dimension must be even");
    return Dim<T, L/2, M/2, S/2, R>{std::sqrt(u.value)};
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
min(const Dim<T, L, M, S, R>& lhs, const Dim<T, L, M, S, R>& rhs) {
    return lhs.value < rhs.value ? lhs : rhs;
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
max(const Dim<T, L, M, S, R>& lhs, const Dim<T, L, M, S, R>& rhs) {
    return lhs.value > rhs.value ? lhs : rhs;
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE constexpr auto
minMax(const Dim<T, L, M, S, R>& lhs, const Dim<T, L, M, S, R>& rhs) {
    return lhs.value < rhs.value ? std::pair{lhs, rhs} : std::pair{rhs, lhs};
}

template<typename T, int L, int M, int S, typename R>
[[nodiscard]] UTIL_ALWAYS_INLINE auto
abs(const Dim<T, L, M, S, R>& dim) {
    return Dim<T, L, M, S, R>{std::abs(dim.value)};
}

template<typename T, int L, int M, int S, typename R>
std::ostream& operator<<(std::ostream& os, Dim<T, L, M, S, R> dim) {
    return os<<dim.value;
}

// Functions to convert from and to std::chrono::duration

template<typename T, typename R>
[[nodiscard]] constexpr Duration<T, R>
fromChrono(std::chrono::duration<T, R> dur) {
    return Duration<T, R>{dur.count()};
}

template<typename TOut, typename ROut, typename TIn, typename RIn,
        typename E_ = std::enable_if_t<!std::is_same_v<TOut, TIn> || !std::is_same_v<ROut, RIn> > >
[[nodiscard]] constexpr Duration<TOut, ROut>
fromChrono(std::chrono::duration<TIn, RIn> durIn) {
    const auto durOut = std::chrono::duration_cast<std::chrono::duration<TOut, ROut> >(durIn);
    return Duration<TOut, ROut>{durOut.count()};
}

template<typename T, typename R>
[[nodiscard]] constexpr std::chrono::duration<T, R>
toChrono(Duration<T, R> dur) {
    return std::chrono::duration<T, R>{dur.value};
}

template<typename TOut, typename ROut, typename TIn, typename RIn,
        typename E_ = std::enable_if_t<!std::is_same_v<TOut, TIn> || !std::is_same_v<ROut, RIn> > >
[[nodiscard]] constexpr std::chrono::duration<TOut, ROut>
toChrono(Duration<TIn, RIn> durIn) {
    const auto durOut = static_cast<Duration<TOut, ROut> >(durIn);
    return std::chrono::duration<TOut, ROut>{durOut.value};
}


}  // namespace Util

#endif  // HPP_UTIL_DIMENSION_1657307060_
