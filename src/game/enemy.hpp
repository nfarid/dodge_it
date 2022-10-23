
#ifndef HPP_GAME_ENEMY_
#define HPP_GAME_ENEMY_

#include "circle.hpp"

#include "../media/drawable.hpp"
#include "../media/sprite.hpp"

#include <SDL2/SDL_render.h>


namespace Game
{


class Enemy : public Media::Drawable {
public:
    explicit Enemy(SDL_Texture* texture_, Circle circle_);

    Circle getCircle() const;
    Util::BaseMomentum getMomentum() const;
    Util::BaseMomentumScalar getMomentumX() const;
    Util::BaseMomentumScalar getMomentumY() const;

    void update(Util::Second dt);
    void multipleSpeedX(float x);
    void multipleSpeedY(float y);
    void applyImpulse(Util::BaseImpulse dp);
    void applyImpulseX(Util::BaseImpulseScalar dpX);
    void applyImpulseY(Util::BaseImpulseScalar dpY);

private:
    Circle mCircle{};
    Media::Sprite mSprite;
    Util::BaseVelocity mVel{};
    Util::BaseMass mMass{};

    void draw(Media::Window& window) const override;
};


}// namespace Game

#endif // ifndef HPP_GAME_ENEMY_
