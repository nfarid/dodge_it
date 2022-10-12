
#ifndef HPP_MEDIA_GAMESTATE_8001664048990_
#define HPP_MEDIA_GAMESTATE_8001664048990_

#include "../util/dimension.hpp"


namespace Media
{


struct GameContext;


class GameState
{
public:
    virtual ~GameState(); // = default
    GameState& operator=(GameState&&) = delete; // no copy nor move

    virtual void handleInput() = 0;
    virtual void update(Util::Second dt) = 0;
    virtual void draw() = 0;

    virtual void init() {}
    virtual void pause() {}
    virtual void resume() {}

protected:
    GameContext* rCtx;

    explicit GameState(GameContext* ctx_);
};


}// namespace Media

#endif // ifndef HPP_MEDIA_GAMESTATE_8001664048990_
