
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
    mVel{ 4_blPs, -4_blPs},
    mMass{1_bm}
{}

Circle Enemy::getCircle() const {
    return mCircle;
}

Util::BaseMomentum Enemy::getMomentum() const {
    return mMass * mVel;
}

Util::BaseMomentumScalar Enemy::getMomentumX() const {
    return mMass * mVel.x;
}

Util::BaseMomentumScalar Enemy::getMomentumY() const {
    return mMass * mVel.y;
}

void Enemy::update(Util::Second dt) {
    mCircle.pos += mVel * dt;
}

void Enemy::multipleSpeedX(float x) {
    mVel.x *= x;
}

void Enemy::multipleSpeedY(float y) {
    mVel.y *= y;
}

void Enemy::applyImpulse(Util::BaseImpulse dp) {
    mVel += dp/mMass;
}

void Enemy::applyImpulseX(Util::BaseImpulseScalar dpX) {
    mVel.x += dpX/mMass;
}

void Enemy::applyImpulseY(Util::BaseImpulseScalar dpY) {
    mVel.y += dpY/mMass;
}

void Enemy::draw(Media::Window& window) const {
    window.draw(mSprite, mCircle.aabb() );
}


} // namespace Game

