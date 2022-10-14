
#ifndef HPP_MEDIA_GAMESTATE_8001664048990_
#define HPP_MEDIA_GAMESTATE_8001664048990_

#include "../util/dimension.hpp"


namespace Media
{


struct GameContext;

/**
 * @brief An abstract base class to represent the current state of the game
 */
class GameState
{
public:

    virtual ~GameState() = default; // A default virtual destructor
    GameState& operator=(GameState&&) = delete; // no copy nor move

    // These abstract methods must be implemented in the dervied classes
    virtual void handleInput() = 0;
    virtual void update(Util::Second) = 0;
    virtual void draw() = 0;

    // These virtual method are optional to implement
    virtual void init() {}
    virtual void pause() {}
    virtual void resume() {}

protected:
    GameContext& rCtx; // GameContext will outlive the GameState

    explicit GameState(GameContext& ctx_);
};


}// namespace Media

#endif // ifndef HPP_MEDIA_GAMESTATE_8001664048990_
