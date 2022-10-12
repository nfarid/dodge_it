
#ifndef HPP_MEDIA_WINDOW_141663353574_
#define HPP_MEDIA_WINDOW_141663353574_

#include "camera.hpp"

#include "../util/rect.hpp"
#include "../util/typedefs.hpp"

#include <SDL2/SDL_render.h>

#include <memory>
#include <span>
#include <vector>


namespace Media
{


class Sprite;
class Drawable;


using UniquePtrSDLWindow = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;
using UniquePtrSDLRenderer = std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

/**
 * @brief Get a snapshot of the current state of the keyboard.
 * @note Only call this after all events have been processed
 */
std::span<const uint8_t> keyboardState();

UniquePtrSDLWindow createSDLWindow(const char* title, int x, int y, int w, int h, Uint32 flags);
UniquePtrSDLRenderer createSDLRenderer(SDL_Window* window, int index, Uint32 flags);

/**
 * @brief A window for 2D rendering.
 */
class Window {
public:
    explicit Window(UniquePtrSDLWindow window_, UniquePtrSDLRenderer renderer_);

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

    UniquePtrSDLWindow mWindow;
    UniquePtrSDLRenderer mRenderer;
    Camera mCamera;
    std::vector<TextureBatch> mBatchLst{};
};


}// namespace Media

#endif // ifndef HPP_MEDIA_WINDOW_141663353574_
