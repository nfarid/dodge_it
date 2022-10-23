
#include "game_over.hpp"

#include "../media/game_context.hpp"



namespace Menu
{


using namespace Util::Udl;
using namespace Media::Udl;
using namespace std::string_literals;


GameOverState::GameOverState(Media::GameContext& ctx_, Util::Second timeSurvived_) :
    Media::GameState{ctx_},
    mTimeSurvived{"Time survived: "s + std::to_string(timeSurvived_.value) + "s"s}
{
    rCtx.resourceManager.loadFont(u8"fonts/andika_regular.ttf", "andika");
    mFont = rCtx.resourceManager.getFont("andika");
}

void GameOverState::handleInput() {
    Media::GameState::handleInput();
}

void GameOverState::update(Util::Second) {}

void GameOverState::draw() {
    auto& window = rCtx.window;
    window.clear();

    const Media::PixelPosition fontLeftTop = {200_pl, 200_pl};
    window.draw(mFont, fontLeftTop, mTimeSurvived);

    window.display();
}


} // namespace Menu

