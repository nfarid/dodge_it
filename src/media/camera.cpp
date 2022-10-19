
#include "camera.hpp"


namespace Media
{


using namespace Util;


Camera::Camera(PixelDisplacement windowSize) :
    mWindowRect{PixelRect::leftTopSize({0_pl, 0_pl}, windowSize)},
    mViewRect{BaseRect::leftTopSize({0_bl, 0_bl}, static_cast<BaseDisplacement>(windowSize) )}
{}

PixelRect Camera::getWindowBound() const {
    return mWindowRect;
}

BaseRect Camera::getViewBound() const {
    return mViewRect;
}

bool Camera::isVisible(Util::BaseRect posRect) const {
    return hasCollision(mViewRect, posRect);
}

PixelPosition Camera::toScreenCoord(Util::BasePosition worldCoord) const {
    const auto viewCoord = worldCoord - mViewRect.leftTop();
    const auto relCoord = elemDiv(viewCoord, mViewRect.size() );
    const auto screenCoord = elemMul(relCoord, mWindowRect.size() ) + mWindowRect.leftTop();
    return screenCoord;
}

BasePosition Camera::toWorldCoord(PixelPosition screenCoord) const {
    const auto relCoord = elemDiv(screenCoord - mWindowRect.leftTop(), mWindowRect.size() );
    const auto viewCoord = elemMul(relCoord, mViewRect.size() );
    const auto worldCoord = viewCoord + mViewRect.leftTop();
    return worldCoord;
}


} // namespace Media

