
#ifndef HPP_MENUSTATES_GAMEOVER_
#define HPP_MENUSTATES_GAMEOVER_

#include "../media/game_state.hpp"


namespace Menu
{


class GameOverState : public Media::GameState {
public:
    explicit GameOverState(Media::GameContext& ctx_, Util::Second timeSurvived_);

    void handleInput() override;
    void update(Util::Second) override;
    void draw() override;

private:
    Util::Second mTimeSurvived;
};


}// namespace Menu

#endif // ifndef HPP_MENUSTATES_GAMEOVER_
