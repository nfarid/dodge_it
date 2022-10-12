
#ifndef HPP_MEDIA_SPRITE_161663166514_
#define HPP_MEDIA_SPRITE_161663166514_

#include "core.hpp"

#include "../util/macros.hpp"
#include "../util/rect.hpp"

#include <array>
#include <limits>
#include <string>
#include <string_view>
#include <vector>

#include <SDL2/SDL_render.h>


namespace Media
{


class Camera;

constexpr Util::Second forever{std::numeric_limits<Util::Real>::infinity()};

struct AnimationFrame {
    PixelRect rect;
    Util::Second time;
};

struct Animation {
    std::string modeName;
    std::vector<AnimationFrame> frameLst;
};

/**
 * @brief An animated sprite
 * @todo maybe use the flyweight pattern to reduce memory usage
 */
class Sprite
{
public:
    UTIL_IMPLICIT Sprite(SDL_Texture* texture_, std::vector<Animation> animationLst_);

    [[nodiscard]] std::array<SDL_Vertex, 4> getVertices(const Util::BaseRect& posRect, const Camera& camera) const;
    [[nodiscard]] SDL_Texture* getTexture() const;
    [[nodiscard]] PixelRect getRect() const;

    void switchMode(std::string_view mode, bool resetFrame = true);
    void update(Util::Second dt);

private:
    SDL_Texture* rTexture{};
    std::vector<Animation> mAnimationLst{};
    size_t mAnimationIndex{};
    size_t mFrameIndex{};
    Util::Second mElasped{};
};


}// namespace Media

#endif // HPP_MEDIA_SPRITE_161663166514_
