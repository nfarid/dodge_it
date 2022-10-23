
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
    mEnemyLst{},
    mPlayer{ctx_.resourceManager.getTexture("circles")},
    mRng{},
    mTimeUntilEnemySpawn{0_s}
{}

void PlayingState::handleInput() {
    SDL_Event ev;
    while(SDL_PollEvent(&ev) ) {
        switch(ev.type) {
        case SDL_MOUSEBUTTONDOWN:
            mPlayer.startFollowingMouse();
            break;
        case SDL_MOUSEBUTTONUP:
            mPlayer.stopFollowingMouse();
            break;
        case SDL_QUIT:
            rCtx.quit = true;
            break;
        default:
            break;
        }
    }
    mPlayer.takeMousePosition(rCtx.window.mouseWorldCoord() );
}

void PlayingState::update(Util::Second dt) {
    for(auto& enemy : mEnemyLst) {
        enemy.update(dt);
        if(enemy.getCircle().top() <= worldRect.top() || enemy.getCircle().bottom() >= worldRect.bottom() )
            enemy.applyImpulseY(-2.0f * enemy.getMomentumY() );
        if(enemy.getCircle().left() <= worldRect.left() || enemy.getCircle().right() >= worldRect.right() )
            enemy.applyImpulseX(-2.0f * enemy.getMomentumX() );
    }

    mPlayer.update(dt);

    mTimeUntilEnemySpawn -= dt;
    if(mTimeUntilEnemySpawn <= 0_s) {
        mTimeUntilEnemySpawn = 5_s;
        const Util::BaseDistance r{mRng.getFloat(0.25, 2.5)};
        const Util::BasePositionScalar cx{mRng.getFloat(worldRect.left().value, worldRect.right().value)};
        const Util::BasePositionScalar cy{mRng.getFloat(worldRect.top().value, worldRect.bottom().value)};
        const Circle circle{.radius=r, .centre={cx, cy} };
        mEnemyLst.emplace_back(rCtx.resourceManager.getTexture("circles"), circle);
    }
}

void PlayingState::draw() {
    auto& window = rCtx.window;
    window.clear();
    for(const auto& enemy : mEnemyLst)
        window.draw(enemy);
    window.draw(mPlayer);
    window.display();
}


} // namespace Game

