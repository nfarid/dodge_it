
#ifndef HPP_MEDIA_VIEW_7441663627589_
#define HPP_MEDIA_VIEW_7441663627589_

#include "core.hpp"

#include "../util/rect.hpp"


namespace Media
{


/**
 * @brief Represents the viewable space
 */
class Camera
{
public:
    explicit Camera(PixelDisplacement windowSize);

    [[nodiscard]] bool isVisible(Util::BaseRect posRect) const;
    [[nodiscard]] PixelPosition toScreenCoord(Util::BasePosition worldCoordPos) const;

private:
    PixelRect mWindowRect;
    Util::BaseRect mViewRect;
};


}// namespace Media

#endif // ifndef HPP_MEDIA_VIEW_7441663627589_
