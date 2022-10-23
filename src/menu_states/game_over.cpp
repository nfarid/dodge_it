
#include "game_over.hpp"


namespace Menu
{


using namespace Util::Udl;


GameOverState::GameOverState(Media::GameContext& ctx_, Util::Second timeSurvived_) :
    Media::GameState{ctx_},
    mTimeSurvived{timeSurvived_}
{}

void GameOverState::handleInput() {}

void GameOverState::update(Util::Second) {}

void GameOverState::draw() {}


} // namespace Menu

