
#ifndef HPP_MENUSTATES_GAMEOVER_
#define HPP_MENUSTATES_GAMEOVER_

#include "../media/game_state.hpp"

#include <SDL_FontCache/SDL_FontCache.h>

#include <string>


namespace Menu
{


class GameOverState : public Media::GameState {
public:
    explicit GameOverState(Media::GameContext& ctx_, Util::Second timeSurvived_);

    void handleInput() override;
    void update(Util::Second) override;
    void draw() override;

private:
    std::string mTimeSurvived{};
    FC_Font* mFont{};
};


}// namespace Menu

#endif // ifndef HPP_MENUSTATES_GAMEOVER_
