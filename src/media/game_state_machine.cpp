
#include "game_state_machine.hpp"

#include <cassert>


namespace Media
{


void GameStateMachine::addState(std::unique_ptr<GameState> newState_, bool replacing_) {
    mIsReplacing = replacing_;
    mStateToBeAdded = std::move(newState_);
}

void GameStateMachine::removeState() {
    mIsRemoving = true;
}

void GameStateMachine::processStateChanges()
{
    if(mIsRemoving && mStateStack.empty() ) {
        mStateStack.pop();
        if(!mStateStack.empty() )
            mStateStack.top()->resume();
        mIsRemoving = false;
    }

    if(mStateToBeAdded) {
        if(!mStateStack.empty() ) {
            if(mIsReplacing)
                mStateStack.pop();
            else
                mStateStack.top()->pause();
        }
        mStateStack.push(std::move(mStateToBeAdded) );
        mStateStack.top()->init();
        mIsReplacing = false;
    }
}

GameState& GameStateMachine::getActiveState() {
    assert(!mStateStack.empty() );
    return *mStateStack.top();
}


} // namespace Media

