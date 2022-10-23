
#ifndef HPP_GAME_CIRCLE_
#define HPP_GAME_CIRCLE_

#include "../util/macros.hpp"
#include "../util/rect.hpp"

#include <cassert>


namespace Game
{


struct Circle {
    Util::BaseDistance radius;
    Util::BasePosition centre;

    /*[[discardable]]*/ constexpr Util::BasePositionScalar& x() {
        return centre.x;
    }

    [[nodiscard]] constexpr Util::BasePositionScalar x() const {
        return centre.x;
    }

    /*[[discardable]]*/ constexpr Util::BasePositionScalar& y() {
        return centre.y;
    }

    [[nodiscard]] constexpr Util::BasePositionScalar y() const {
        return centre.y;
    }

    /*[[discardable]]*/ constexpr Util::BasePositionScalar& r() {
        return radius;
    }

    [[nodiscard]] constexpr Util::BasePositionScalar r() const {
        return radius;
    }

    [[nodiscard]] constexpr Util::BaseRect aabb() const {
        return Util::BaseRect::centreSize(centre, {radius*2.0f, radius*2.0f});
    }

    [[nodiscard]] constexpr Util::BasePositionScalar left() const {
        return x() - radius;
    }

    [[nodiscard]] constexpr Util::BasePositionScalar right() const {
        return x() + radius;
    }

    [[nodiscard]] constexpr Util::BasePositionScalar top() const {
        return y() - radius;
    }

    [[nodiscard]] constexpr Util::BasePositionScalar bottom() const {
        return y() + radius;
    }

    [[nodiscard]] constexpr bool isValid() const {
        return radius >= Util::BaseDistance::zero();
    }

    void makeValid() {
        // TODO: make a constexpr abs()
        radius = abs(radius);
    }
};


/**
 * @brief Checks if 2 circles are interesecting
 * @param lhs - One of the valid circles to be tested for collision
 * @param rhs - One of the valid circles to be tested for collision
 * @note If only the edges are touching (i.e. interesection length is zero) then it return false
 */
[[nodiscard]] constexpr bool
hasCollision(const Circle& lhs, const Circle& rhs) {
    assert(lhs.isValid() && rhs.isValid() && "hasCollision needs both circles to be valid");
    const auto distSq = (lhs.centre - rhs.centre).squareMag();
    const auto totalRadSq = square(lhs.radius + rhs.radius);
    return distSq < totalRadSq;
}


} // namespace Game

#endif // HPP_GAME_CIRCLE_
