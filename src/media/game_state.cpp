
#include "game_state.hpp"


namespace Media
{


GameState::~GameState() = default;

GameState::GameState(GameContext* ctx_) :
    rCtx{ctx_}
{}

// prevents weak-vtables


} // namespace Media

