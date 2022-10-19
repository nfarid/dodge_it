
#include "playing_state.hpp"

#include "../media/core.hpp"
#include "../media/game_context.hpp"


namespace Game
{


using namespace Util::Udl;


namespace
{


// Currently the world fill the entire screen
constexpr auto worldSize = static_cast<Util::BaseDisplacement>(Media::windowsSize);
constexpr auto worldRect = Util::BaseRect::leftTopSize({0_bl, 0_bl}, worldSize);


} // namespace


PlayingState::PlayingState(Media::GameContext& ctx_) :
    Media::GameState{ctx_},
    mEnemy{ctx_.resourceManager.getTexture("circles")}
{}

void PlayingState::handleInput() {
    Media::GameState::handleInput();
}

void PlayingState::update(Util::Second dt) {
    mEnemy.update(dt);
}

void PlayingState::draw() {
    auto& window = rCtx.window;
    window.clear();
    window.draw(mEnemy);
    window.display();
}


} // namespace Game

