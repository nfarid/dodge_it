
#include "sprite.hpp"

#include "camera.hpp"

#include <cassert>
#include <utility>


namespace Media
{


namespace
{


PixelDisplacement getTextureSize(SDL_Texture* texture) {
    UTIL_UNINIT int w;
    UTIL_UNINIT int h;
    SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
    return {
        PixelDistance{static_cast<float>(w)},
        PixelDistance{static_cast<float>(h)},
    };
}


} // namespace


using namespace Util;

Sprite::Sprite(SDL_Texture* texture_, std::vector<Animation> animationLst_) :
    rTexture{texture_},
    mAnimationLst{std::move(animationLst_)},
    mAnimationIndex{0},
    mFrameIndex{0},
    mElasped{0_s}
{
    assert(texture_ && "Sprite cannot take a null texture");
}

std::array<SDL_Vertex, 4> Sprite::getVertices(const BaseRect& posRect, const Camera& camera) const
{
    constexpr SDL_Colour colour{0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE};
    const PixelDisplacement textureSize = getTextureSize(rTexture);
    const PixelRect frameRect = getRect();

    // Get the tex-coordinates
    const Real textureLeft = frameRect.left() / textureSize.x;
    const Real textureRight = frameRect.right() / textureSize.x;
    const Real textureTop = frameRect.top() / textureSize.y;
    const Real textureBottom = frameRect.bottom() / textureSize.y;

    // Get the vertex-cooridantes
    const auto [vertexLeft, vertexTop] = camera.toScreenCoord(posRect.leftTop() );
    const auto [vertexRight, vertexBottom] = camera.toScreenCoord(posRect.rightBottom() );

    return {
        SDL_Vertex{
            {vertexLeft.value, vertexTop.value},
            colour,
            {textureLeft, textureTop},
        },
        SDL_Vertex{
            {vertexRight.value, vertexTop.value},
            colour,
            {textureRight, textureTop},
        },
        SDL_Vertex{
            {vertexLeft.value, vertexBottom.value},
            colour,
            {textureLeft, textureBottom},
        },
        SDL_Vertex{
            {vertexRight.value, vertexBottom.value},
            colour,
            {textureRight, textureBottom},
        },
    };
}

SDL_Texture* Sprite::getTexture() const {
    return rTexture;
}

PixelRect Media::Sprite::getRect() const {
    return mAnimationLst[mAnimationIndex].frameLst[mFrameIndex].rect;
}

void Sprite::switchMode(std::string_view mode, bool resetFrame) {
    const size_t animationCount = size(mAnimationLst);
    for(size_t i=0; i<animationCount; ++i) {
        if(mAnimationLst[i].modeName == mode) {
            if(mAnimationIndex != i) {
                mAnimationIndex = i;
                if(resetFrame) {
                    mFrameIndex = 0;
                    mElasped = -0_s;
                } else {
                    mFrameIndex = mFrameIndex % mAnimationLst[i].frameLst.size();
                }
            }
            return;
        }
    }
    UTIL_UNREACHABLE();
}

void Sprite::update(Util::Second dt) {
    auto& animation = mAnimationLst[mAnimationIndex];
    const auto totalFrameTime = animation.frameLst[mFrameIndex].time;
    if(mElasped >= totalFrameTime) { // assumes that mElasped < 2*totalFrameTime
        mElasped -= totalFrameTime;
        ++mFrameIndex;
        if(mFrameIndex >= size(animation.frameLst) )
            mFrameIndex = 0;
    }
    mElasped += dt;
}


} // namespace Media

