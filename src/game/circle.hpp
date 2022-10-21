
#ifndef HPP_GAME_CIRCLE_
#define HPP_GAME_CIRCLE_

#include "../util/macros.hpp"
#include "../util/rect.hpp"


namespace Game
{


struct Circle {
    Util::BaseDistance r;
    Util::BasePosition pos;

    /*[[discardable]]*/ Util::BasePositionScalar& x() {
        return pos.x;
    }

    [[nodiscard]] Util::BasePositionScalar x() const {
        return pos.x;
    }

    /*[[discardable]]*/ Util::BasePositionScalar& y() {
        return pos.y;
    }

    [[nodiscard]] Util::BasePositionScalar y() const {
        return pos.y;
    }

    [[nodiscard]] Util::BaseRect aabb() const {
        return Util::BaseRect::centreSize(pos, {r*2.0f, r*2.0f});
    }

    [[nodiscard]] Util::BasePositionScalar left() const {
        return x() - r;
    }

    [[nodiscard]] Util::BasePositionScalar right() const {
        return x() + r;
    }

    [[nodiscard]] Util::BasePositionScalar top() const {
        return y() - r;
    }

    [[nodiscard]] Util::BasePositionScalar bottom() const {
        return y() + r;
    }

    [[nodiscard]] bool isValid() const {
        return r >= Util::BaseDistance::zero();
    }

    void makeValid() {
        r = abs(r);
    }
};


} // namespace Game

#endif // HPP_GAME_CIRCLE_
