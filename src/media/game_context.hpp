
#ifndef HPP_GAMECONTEXT_3431664107561_
#define HPP_GAMECONTEXT_3431664107561_

#include "game_state_machine.hpp"
#include "resource_manager.hpp"
#include "window.hpp"

#include "../util/dimension.hpp"


namespace Media
{


struct GameContext {
    GameStateMachine stateMachine;
    ResourceManager resourceManager;
    Window window;
    bool quit{};
};


} // namespace Media

#endif // ifndef HPP_GAMECONTEXT_3431664107561_
