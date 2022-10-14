
#include "playing_state.hpp"


namespace Game
{


PlayingState::PlayingState(Media::GameContext& ctx_) :
    Media::GameState{ctx_}
{}

void PlayingState::handleInput() {
    Media::GameState::handleInput();
}

void PlayingState::update(Util::Second dt) {
    Media::GameState::update(dt);
}

void PlayingState::draw() {
    Media::GameState::draw();
}


} // namespace Game

