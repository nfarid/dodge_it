
#include "media/game_context.hpp"
#include "media/game_state_machine.hpp"
#include "media/resource_manager.hpp"
#include "media/window.hpp"

#include "util/dimension.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
#elif defined(_WIN32)
    #include <Windows.h>
#endif // ifdef platform

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>


namespace
{


class BasicState : public Media::GameState {
public:
    explicit BasicState(Media::GameContext& ctx_) :
        Media::GameState{ctx_} {
        auto& resources = rCtx.resourceManager;
    }

    void handleInput() override {
        Media::GameState::handleInput();
    }

    void update(Util::Second dt) override {
        Media::GameState::update(dt);
    }

    void draw() override {
        Media::GameState::draw();
    }
};


} // namespace


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    using namespace Util::Udl;
    using namespace std::chrono;

    // Initialising phase
    {
        // SDL_Init returns 0 on success or a negative error code on failure
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
            std::cerr<<"SDL_Init failed: "<<SDL_GetError()<<std::endl;
            return EXIT_FAILURE;
        }
        std::atexit(SDL_Quit);

        // IMG_Init returns the flags successfully initialized, or 0 on failure.
        constexpr auto imgFlags = IMG_INIT_PNG;
        if(IMG_Init(imgFlags) != imgFlags) {
            std::cerr<<"IMG_Init failed: "<<IMG_GetError()<<std::endl;
            return EXIT_FAILURE;
        }
        std::atexit(IMG_Quit);

        // TTF_Init returns 0 on success, -1 on error.
        if(TTF_Init() != 0) {
            std::cerr<<"TTF_Init failed: "<<TTF_GetError()<<std::endl;
            return EXIT_FAILURE;
        }
        std::atexit(TTF_Quit);

        // Mix_Init returns the flags successfully initialized, or 0 on failure.
        constexpr auto mixFlags = MIX_INIT_OGG;
        if(Mix_Init(mixFlags) != mixFlags) {
            std::cerr<<"Mix_Init failed: "<<Mix_GetError()<<std::endl;
            return EXIT_FAILURE;
        }
        std::atexit(Mix_Quit);

        // Mix_OpenAudio returns 0 if successful, -1 on error.
        // Arguments are frequency, audio format, channels, chunk size
        if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) != 0) {
            std::cerr<<"Mix_OpenAudio failed: "<<Mix_GetError()<<std::endl;
            return EXIT_FAILURE;
        }
        std::atexit(Mix_CloseAudio);
    }

    // Creating the game context
    static std::unique_ptr<Media::GameContext> sCtx = nullptr;
    {
        // Window and renderer creation
        auto sdlWindow = Media::createSDLWindow("basic",
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                800, 600,
                0);
        if(!sdlWindow) {
            std::cerr<<"Failed creating the sdl window: "<<SDL_GetError()<<std::endl;
            return EXIT_FAILURE;
        }
        auto sdlRenderer = Media::createSDLRenderer(sdlWindow.get(), -1, 0);
        if(!sdlRenderer) {
            std::cerr<<"Failed create the sdl renderer: "<<SDL_GetError()<<std::endl;
            return EXIT_FAILURE;
        }
        #if defined(_WIN32) && defined(NDEBUG)
        HWND windowHandle = GetConsoleWindow();
        ShowWindow(windowHandle, SW_HIDE);
        #endif // if defined(_WIN32) && defined(NDEBUG)

        Media::ResourceManager resourceManager{sdlRenderer.get()};
        Media::GameStateMachine gameStateMachine;
        Media::Window window{std::move(sdlWindow), std::move(sdlRenderer)};

        sCtx = std::make_unique<Media::GameContext>(Media::GameContext{
            std::move(gameStateMachine),
            std::move(resourceManager),
            std::move(window),
            false,
        });
    }

    // Initial state
    sCtx->stateMachine.addState(std::make_unique<BasicState>(*sCtx) );
    sCtx->stateMachine.processStateChanges();

    // Game loop variables
    constexpr static Util::Hertz idealTickRate = 64_hz;
    constexpr static Util::Second idealTickDuration = 1_r / idealTickRate;
    static Util::Second sAccumulator = 0_s;
    static decltype(high_resolution_clock::now() ) sCurrentTime{};

    // Game loop function
    constexpr static auto gameLoop = []{
        assert(sCtx);
        auto& stateMachine = sCtx->stateMachine;
        auto& currentState = stateMachine.getActiveState();
        const auto newTime = high_resolution_clock::now();
        const auto actualTickDuration = Util::fromChrono<Util::Real, Util::BaseRatio>(newTime - sCurrentTime);
        sCurrentTime = newTime;
        sAccumulator += actualTickDuration;
        while(sAccumulator >= idealTickDuration) {
            sAccumulator -= idealTickDuration;
            currentState.handleInput();
            currentState.update(idealTickDuration);
        }
        currentState.draw();
        stateMachine.processStateChanges();
    #ifdef __EMSCRIPTEN__
        if(sCtx->quit) {
            emscripten_cancel_main_loop();
            sCtx.reset();
        }
    #endif // ifdef __EMSCRIPTEN__
    };

    // Start the game loop
    sCurrentTime = high_resolution_clock::now();
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(gameLoop, -1, true);
#else
    while(!sCtx->quit)
        gameLoop();
#endif // ifdef __EMSCRIPTEN__

    return EXIT_SUCCESS;
}
