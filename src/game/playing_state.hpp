
#ifndef HPP_GAME_PLAYINGSTATE_
#define HPP_GAME_PLAYINGSTATE_

#include "enemy.hpp"
#include "player.hpp"

#include "../media/game_state.hpp"

#include "../util/rng.hpp"

#include <vector>


namespace Game
{


class PlayingState : public Media::GameState {
public:
    explicit PlayingState(Media::GameContext& ctx_);

    void handleInput() override;
    void update(Util::Second dt) override;
    void draw() override;

private:
    std::vector<Enemy> mEnemyLst{};
    Player mPlayer;
    Util::Rng mRng{};
    Util::Second mTimeUntilEnemySpawn{};
    Util::Second mTimeSurvived{};
};


}// namespace Game

#endif // ifndef HPP_GAME_PLAYINGSTATE_
