
#ifndef HPP_MEDIA_CORE_1581663618097_
#define HPP_MEDIA_CORE_1581663618097_

#include "../util/rect.hpp"
#include "../util/typedefs.hpp"


namespace Media
{


inline namespace Udl
{


using Util::Udl::operator""_hz;
using Util::Udl::operator""_r;


} // namespace Udl


// Constants
constexpr Util::Hertz idealTickRate = 64_hz;
constexpr Util::Second idealTickDuration = 1_r / idealTickRate;


// Typedefs
constexpr intmax_t defaultPixelsPerBlock = 32;
using PixelRatio = std::ratio<1, defaultPixelsPerBlock>;
using PixelLength = Util::Length<Util::Real, PixelRatio>;
using PixelPositionScalar = Util::PositionScalar<Util::Real, PixelRatio>;
using PixelDistance = Util::Distance<Util::Real, PixelRatio>;
using PixelPosition = Util::Position<Util::Real, PixelRatio>;
using PixelDisplacement = Util::Displacement<Util::Real, PixelRatio>;
using PixelRect = Util::Rect<Util::Real, PixelRatio>;

// User-defined literals
inline namespace Udl
{


[[nodiscard]] constexpr PixelLength operator"" _pl(long double f) noexcept {
    return PixelLength{static_cast<Util::Real>(f)};
}

[[nodiscard]] constexpr PixelLength operator"" _pl(unsigned long long int i) noexcept {
    return PixelLength{static_cast<Util::Real>(i)};
}


} // namespace Udl


} // namespace Media

#endif // ifndef HPP_MEDIA_CORE_1581663618097_
