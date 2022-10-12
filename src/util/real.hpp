
#ifndef HPP_UTIL_REAL_1657306623_
#define HPP_UTIL_REAL_1657306623_

#include "macros.hpp"

#include <algorithm>
#include <functional>
#include <limits>
#include <type_traits>


namespace Util
{


#ifdef REAL_TYPE
using Real = REAL_TYPE;
#else
using Real = float;
#endif  // ifdef REAL_TYPE


inline namespace Udl
{


[[nodiscard]] constexpr Real operator"" _r(long double f) noexcept {
    return static_cast<Real>(f);
}

[[nodiscard]] constexpr Real operator"" _r(unsigned long long int i) noexcept {
    return static_cast<Real>(i);
}


}  // namespace Udl


/**
 * @brief Checks if two values are exactly equal
 * @note used for "safe" exact float comparison without raising a warning
 * @note exact comparison for floats should be rarely used due to rounding errors
 * @example: const bool is_zero = equal(number, 0.F);
 */
template<typename T> UTIL_ALWAYS_INLINE
bool equal(T lhs, T rhs) noexcept {
    return std::equal_to{}(lhs, rhs);
}

/**
 * \brief Checks if lhs and rhs are almost equal (as floats can contain rounding errors)
 * \note Assumes that floats are IEEE 754 (as this function uses implementation-defined behaviour)
 * \param eps - the epsilon which determines the error margin (default is machine epsilon)
 */
template<typename T, typename T_ = std::enable_if_t<std::is_floating_point_v<T> > > inline
bool nearly_equal(T lhs, T rhs, T eps = std::numeric_limits<T>::epsilon() ) {
    constexpr static auto max_value = std::numeric_limits<T>::max();
    constexpr static auto smallest_normal = std::numeric_limits<T>::min();  // smallest positive
    constexpr static T zero{};

    if(equal(lhs, rhs) ) // shortcut, handles infinities
        return true;

    const auto abs_sum = std::abs(lhs) + std::abs(rhs);
    const auto diff = std::abs(lhs - rhs);

    if( (lhs == zero) || (rhs == zero) || (abs_sum < smallest_normal) ) {
        // either are zero or both are very close to it, so relative error is less meaningful here
        return diff < (eps * smallest_normal);
    } else {     // use relative error
        return diff < (eps * std::min(abs_sum, max_value) );
    }
}


} // namespace Util

#endif  // HPP_UTIL_REAL_1657306623_
