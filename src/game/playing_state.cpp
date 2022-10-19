
#include "playing_state.hpp"

#include "../media/core.hpp"
#include "../media/game_context.hpp"

#include <SDL2/SDL_events.h>


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
    mEnemy{ctx_.resourceManager.getTexture("circles")},
    mPlayer{ctx_.resourceManager.getTexture("circles")}
{}

void PlayingState::handleInput() {
    SDL_Event ev;
    while(SDL_PollEvent(&ev) ) {
        switch(ev.type) {
        case SDL_MOUSEBUTTONDOWN:
            break;
        case SDL_MOUSEBUTTONUP:
            break;
        case SDL_QUIT:
            rCtx.quit = true;
            break;
        default:
            break;
        }
    }
}

void PlayingState::update(Util::Second dt) {
    mEnemy.update(dt);
    if(mEnemy.getCircle().top() <= worldRect.top() || mEnemy.getCircle().bottom() >= worldRect.bottom() )
        mEnemy.applyImpulseY(-2.0f * mEnemy.getMomentumY() );
    if(mEnemy.getCircle().left() <= worldRect.left() || mEnemy.getCircle().right() >= worldRect.right() )
        mEnemy.applyImpulseX(-2.0f * mEnemy.getMomentumX() );
}

void PlayingState::draw() {
    auto& window = rCtx.window;
    window.clear();
    window.draw(mEnemy);
    window.draw(mPlayer);
    window.display();
}


} // namespace Game

