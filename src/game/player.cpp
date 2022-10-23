
#include "player.hpp"

#include "../media/window.hpp"


namespace Game
{


using namespace Util::Udl;
using namespace Media::Udl;


namespace
{


const Media::AnimationFrame playerFrame{
    .rect = Media::PixelRect::leftTopSize({0_pl, 0_pl}, {64_pl, 64_pl}),
    .time = Media::forever,
};
const Media::Animation playerAnimation = {
    .modeName="default",
    .frameLst={playerFrame},
};

const Util::BaseSpeed playerSpeed = 5_blPs;


} // namespace


Player::Player(SDL_Texture* texture_) :
    mCircle{.radius=1_bl, .centre={20_bl, 20_bl} },
    mSprite{ texture_, {playerAnimation} },
    mVel{ 0_blPs, 0_blPs}
{}

void Player::update(Util::Second dt) {
    mCircle.centre += mVel * dt;
}

void Player::startFollowingMouse() {
    mFollowMouse = true;
}

void Player::stopFollowingMouse() {
    mFollowMouse = false;
}

void Player::takeMousePosition(Util::BasePosition mousePos_) {
    if(!mFollowMouse)
        return;
    const auto disp = mousePos_ - mCircle.centre;
    mVel = disp.unit() * playerSpeed;
}

void Player::draw(Media::Window& window) const {
    window.draw(mSprite, mCircle.aabb() );
}


} // namespace Game

