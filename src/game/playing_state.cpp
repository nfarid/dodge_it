
#include "playing_state.hpp"

#include "../media/game_context.hpp"


namespace Game
{


PlayingState::PlayingState(Media::GameContext& ctx_) :
    Media::GameState{ctx_},
    mEnemy{ctx_.resourceManager.getTexture("circles")}
{}

void PlayingState::handleInput() {
    Media::GameState::handleInput();
}

void PlayingState::update(Util::Second dt) {
    Media::GameState::update(dt);
}

void PlayingState::draw() {
    auto& window = rCtx.window;
    window.clear();
    window.draw(mEnemy);
    window.display();
}


} // namespace Game

