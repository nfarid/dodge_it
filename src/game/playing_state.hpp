
#ifndef HPP_GAME_PLAYINGSTATE_
#define HPP_GAME_PLAYINGSTATE_

#include "enemy.hpp"

#include "../media/game_state.hpp"


namespace Game
{


class PlayingState : public Media::GameState {
public:
    explicit PlayingState(Media::GameContext& ctx_);

    void handleInput() override;
    void update(Util::Second dt) override;
    void draw() override;

private:
    Enemy mEnemy;
};


}// namespace Game

#endif // ifndef HPP_GAME_PLAYINGSTATE_
