
#ifndef HPP_MEDIA_WINDOW_141663353574_
#define HPP_MEDIA_WINDOW_141663353574_

#include "camera.hpp"

#include "../util/cstring_view.hpp"
#include "../util/rect.hpp"
#include "../util/typedefs.hpp"

#include <SDL2/SDL_render.h>

#include <memory>
#include <span>
#include <vector>
#include <utility>


namespace Media
{


class Sprite;
class Drawable;

struct SDLRendererWindowDeleter {
    void operator()(SDL_Window* window) {
        SDL_DestroyWindow(window);
    }
    void operator()(SDL_Renderer* renderer){
        SDL_DestroyRenderer(renderer);
    }
};

using SDLWindowUniquePtr = std::unique_ptr<SDL_Window, SDLRendererWindowDeleter>;
using SDLRendererUniquePtr = std::unique_ptr<SDL_Renderer, SDLRendererWindowDeleter>;

/**
 * @brief Creates an SDL_Renderer and SDL_Window
 * @param title: the title of the window
 * @param windowSize: the size of the window as a vector
 * @param windowFlags: can be these flags OR'd from https://wiki.libsdl.org/SDL_CreateWindow#remarks
 * @throws runtime_error if this is unable to create a renderer or window
 */
std::pair<SDLRendererUniquePtr, SDLWindowUniquePtr>
createSDLRendererWindow(Util::CStringView title, PixelDisplacement windowSize, Uint32 windowFlags);


/**
 * @brief Get a snapshot of the current state of the keyboard.
 * @note Only call this after all events have been processed
 */
std::span<const uint8_t> keyboardState();


/**
 * @brief A window for 2D rendering.
 */
class Window {
public:
    explicit Window(SDLRendererUniquePtr&& renderer_, SDLWindowUniquePtr&& window_);

    PixelDisplacement currentSize() const;
    Util::BasePosition mouseWorldCoord() const;

    void clear();
    void draw(const Drawable& drawable);
    void draw(const Sprite& sprite, const Util::BaseRect& posRect);
    void draw(const PixelRect& rect, SDL_Colour colour);
    void display();

private:
    struct TextureBatch {
        SDL_Texture* texture;
        std::vector<SDL_Vertex> vertexLst;
        std::vector<int> indexLst;
    };

    SDLWindowUniquePtr mWindow;
    SDLRendererUniquePtr mRenderer;
    Camera mCamera;
    std::vector<TextureBatch> mBatchLst{};
};


}// namespace Media

#endif // ifndef HPP_MEDIA_WINDOW_141663353574_
