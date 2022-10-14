
#include "game_state.hpp"

#include "game_context.hpp"

#include <SDL2/SDL_events.h>


namespace Media
{


GameState::GameState(GameContext& ctx_) :
    rCtx{ctx_}
{}

// Abstract methods can have bodies (can be used for manually default implementation)

void GameState::handleInput() {
    // Windows is closable
    SDL_Event ev;
    while(SDL_PollEvent(&ev) ) {
        switch(ev.type) {
        case SDL_QUIT:
            rCtx.quit = true;
            break;
        default:
            break;
        }
    }
}

void GameState::update(Util::Second) {}

void GameState::draw() {
    // A blank screen
    rCtx.window.clear();
    rCtx.window.display();
}


} // namespace Media

