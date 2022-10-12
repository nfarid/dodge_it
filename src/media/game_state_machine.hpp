
#ifndef HPP_MEDIA_GAMESTATEMACHINE_6791664059226_
#define HPP_MEDIA_GAMESTATEMACHINE_6791664059226_

#include "game_state.hpp"

#include <memory>
#include <stack>


namespace Media
{


class GameStateMachine {
public:
    void addState(std::unique_ptr<GameState> newState_, bool isReplacing_ = true);
    void removeState();
    void processStateChanges();
    GameState& getActiveState();

private:
    std::stack<std::unique_ptr<GameState> > mStateStack{};
    bool mIsReplacing = false;
    bool mIsRemoving = false;
    std::unique_ptr<GameState> mStateToBeAdded{};
};


}// namespace Media

#endif // ifndef HPP_MEDIA_GAMESTATEMACHINE_6791664059226_
