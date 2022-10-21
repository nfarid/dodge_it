
#include "window.hpp"

#include "drawable.hpp"
#include "sprite.hpp"

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_mouse.h>

#include <string>


namespace Media
{


using std::string_literals::operator""s;


namespace
{


PixelDisplacement getWindowSize(SDL_Window* window) {
    using Util::Real;
    /*[[uninit]]*/ int w;
    /*[[uninit]]*/ int h;
    SDL_GetWindowSize(window, &w, &h);
    return {
        PixelDistance{static_cast<Real>(w)},
        PixelDistance{static_cast<Real>(h)},
    };
}


} // namespace


std::pair<SDLRendererUniquePtr, SDLWindowUniquePtr>
createSDLRendererWindow(Util::CStringView title, PixelDisplacement windowSize, Uint32 windowFlags)
{
    const auto width = static_cast<int>(windowSize.x.value);
    const auto height = static_cast<int>(windowSize.y.value);

    /*uninitialised*/ Util::DumbPtr<SDL_Window> window;
    /*uninitialised*/ Util::DumbPtr<SDL_Renderer> renderer;
    if(SDL_CreateWindowAndRenderer(width, height, windowFlags, &window, &renderer) != 0)
        throw std::runtime_error("Unable to create renderer or window:\n"s + SDL_GetError() );

    SDL_SetWindowTitle(window, title.c_str() );
    SDL_RenderSetLogicalSize(renderer, width, height); // for resolution independence

    return {
        SDLRendererUniquePtr{renderer},
        SDLWindowUniquePtr{window}
    };
}

std::span<const uint8_t> keyboardState() {
    /*[[uninit]]*/ int len;
    const uint8_t* ptr = SDL_GetKeyboardState(&len);
    return {ptr, static_cast<size_t>(len)};
}


Window::Window(SDLRendererUniquePtr&& renderer_, SDLWindowUniquePtr&& window_) :
    mWindow{std::move(window_)},
    mRenderer{std::move(renderer_)},
    mCamera{getWindowSize(mWindow.get() )}
{}

PixelDisplacement Window::currentSize() const {
    int w; /*uninitialised*/
    /*uninitialised*/ int h;
    SDL_GetWindowSize(mWindow.get(), &w, &h);
    return {
        PixelDistance{static_cast<float>(w)},
        PixelDistance{static_cast<float>(h)},
    };
}

Util::BasePosition Window::mouseWorldCoord() const {
    int x; /*uninitialised*/
    /*uninitialised*/ int y;
    SDL_GetMouseState(&x, &y);
    const PixelDisplacement mouseExactScreenPos{
        PixelDistance{static_cast<float>(x)},
        PixelDistance{static_cast<float>(y)},
    };
    const auto mouseRelPos = elemDiv(mouseExactScreenPos, currentSize() );
    const auto mouseLogicalScreenPos = elemMul(mouseRelPos, mCamera.getWindowBound().size() );
    return mCamera.toWorldCoord(mouseLogicalScreenPos);
}

void Window::clear() {
    SDL_SetRenderDrawColor(mRenderer.get(), 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(mRenderer.get() );
}

void Window::draw(const Drawable& drawable) {
    drawable.draw(*this);
}

void Window::draw(const Sprite& sprite, const Util::BaseRect& posRect) {
    // Obtain the batch corresponding to the sprite's texture
    SDL_Texture* texture = sprite.getTexture();
    TextureBatch& batch = [texture, this]() -> TextureBatch& {
        for(auto& batchElem : mBatchLst) {
            if(batchElem.texture == texture)
                return batchElem;
        }
        mBatchLst.push_back(TextureBatch{texture, {}, {} });
        return mBatchLst.back();
    }();

    // Add the sprite's vertices to the batch
    auto& vertexLst = batch.vertexLst;
    auto& indexLst = batch.indexLst;
    const int indexZero = static_cast<int>(vertexLst.size() );
    for(const auto vertex : sprite.getVertices(posRect, mCamera) )
        vertexLst.push_back(vertex);
    // Two triangles so vertex (0,1,2) and (3,1,2)
    for(int offset : {0, 1, 2, 3, 1, 2})
        indexLst.push_back(indexZero + offset);
}

void Window::draw(const PixelRect& rect, SDL_Color colour) {
    const SDL_FRect drawRect{
        rect.left().value,
        rect.top().value,
        rect.width().value,
        rect.height().value,
    };
    SDL_SetRenderDrawColor(mRenderer.get(), colour.r, colour.g, colour.b, colour.a);
    SDL_RenderFillRectF(mRenderer.get(), &drawRect);
}

void Window::display() {
    // Render all the batches
    for(const auto& batch : mBatchLst) {
        SDL_RenderGeometry(
            mRenderer.get(), batch.texture,
            batch.vertexLst.data(), static_cast<int>(batch.vertexLst.size() ),
            batch.indexLst.data(), static_cast<int>(batch.indexLst.size() )
        );
    }
    mBatchLst.clear();
    // Update the screen with the drawn elements
    SDL_RenderPresent(mRenderer.get() );
}


} // namespace Media

