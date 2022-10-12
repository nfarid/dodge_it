
#ifndef HPP_UTIL_TYPEDEFS_1658149805_
#define HPP_UTIL_TYPEDEFS_1658149805_

#include <cstddef>
#include <cstdint>


namespace Util
{


// To indicate owning pointers when smart pointers can't be used
template<typename T>
using DumbPtr = T*;


}  // namespace Util


inline namespace ShouldBeGlobalAnyway_
{


// These are already in the global namespace anyway, and should be
using std::int8_t, std::int16_t, std::int32_t, std::int64_t;
using std::int_fast8_t, std::int_fast16_t, std::int_fast32_t, std::int_fast64_t;
using std::int_least8_t, std::int_least16_t, std::int_least32_t, std::int_least64_t;
using std::intmax_t, std::intptr_t;
using std::uint8_t, std::uint16_t, std::uint32_t, std::uint64_t;
using std::uint_fast8_t, std::uint_fast16_t, std::uint_fast32_t, std::uint_fast64_t;
using std::uint_least8_t, std::uint_least16_t, std::uint_least32_t, std::uint_least64_t;
using std::uintmax_t, std::uintptr_t;
using std::size_t, std::ptrdiff_t;
using std::max_align_t;


} // namespace ShouldBeGlobalAnyway_

#endif  // HPP_UTIL_TYPEDEFS_1658149805_
