
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
    explicit Enemy(SDL_Texture* texture_);

private:
    Circle mCircle{};
    Media::Sprite mSprite;

    void draw(Media::Window& window) const override;
};


}// namespace Game

#endif // ifndef HPP_GAME_ENEMY_
