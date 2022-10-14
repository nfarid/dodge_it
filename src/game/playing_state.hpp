
#ifndef HPP_GAME_PLAYINGSTATE_
#define HPP_GAME_PLAYINGSTATE_

#include "../media/game_state.hpp"


namespace Game
{


class PlayingState : public Media::GameState {
public:

    virtual void handleInput();
    virtual void update(Util::Second dt);
    virtual void draw();

private:
};


}// namespace Game

#endif // ifndef HPP_GAME_PLAYINGSTATE_
