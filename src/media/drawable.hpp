
#ifndef HPP_MEDIA_DRAWABLE_931663459344_
#define HPP_MEDIA_DRAWABLE_931663459344_

#include "../util/macros.hpp"


namespace Media
{


class Window;

/**
 * @brief An abstract base class for objects that can be drawn
 * @example window.draw(drawable);
 */
class Drawable
{
protected:
    friend class Window;

    // Virtual destructor for polymorphic base class
    virtual ~Drawable() = default;
    // Rule of 5
    explicit Drawable() = default;
    /*[[implicit]]*/ Drawable(const Drawable&) = default;
    Drawable& operator=(const Drawable&) = default;
    /*[[implicit]]*/ Drawable(Drawable&&) = default;
    Drawable& operator=(Drawable&&) = default;

    // The draw method that must be implemented for Drawable classes
    virtual void draw(Window& window) const = 0;
};


}// namespace Media

#endif // ifndef HPP_MEDIA_DRAWABLE_931663459344_
