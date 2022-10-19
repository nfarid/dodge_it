
#include "enemy.hpp"

#include "../media/core.hpp"
#include "../media/window.hpp"


namespace Game
{


using namespace Util::Udl;
using namespace Media::Udl;


namespace
{


const Media::AnimationFrame circleFrame{
    .rect = Media::PixelRect::leftTopSize({64_pl, 0_pl}, {64_pl, 64_pl}),
    .time = Media::forever,
};
const Media::Animation circleAnimation = {
    .modeName="default",
    .frameLst={circleFrame},
};


} // namespace


Enemy::Enemy(SDL_Texture* texture_) :
    mCircle{.r=2_bl, .pos={10_bl, 10_bl} },
    mSprite{ texture_, {circleAnimation} },
    mVel{ 1_blPs, -1_blPs}
{}

Circle Enemy::getCircle() const {
    return mCircle;
}

void Enemy::update(Util::Second dt) {
    mCircle.pos += mVel * dt;
}

void Enemy::draw(Media::Window& window) const {
    window.draw(mSprite, mCircle.aabb() );
}


} // namespace Game

