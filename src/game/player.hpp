
#ifndef HPP_GAME_PLAYER_
#define HPP_GAME_PLAYER_

#include "circle.hpp"

#include "../media/drawable.hpp"
#include "../media/sprite.hpp"

#include "../util/vec2.hpp"

#include <SDL2/SDL_render.h>


namespace Game
{


class Player : public Media::Drawable  {
public:
    explicit Player(SDL_Texture* texture_);

private:
    Circle mCircle{};
    Media::Sprite mSprite;
    Util::BaseVelocity mVel{};

    void draw(Media::Window& window) const override;
};


} // namespace Game

#endif // ifndef HPP_GAME_PLAYER_
