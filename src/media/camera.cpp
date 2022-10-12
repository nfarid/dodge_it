
#include "camera.hpp"


namespace Media
{


using namespace Util;


Camera::Camera(PixelDisplacement windowSize) :
    mWindowRect{PixelRect::leftTopSize({0_pl, 0_pl}, windowSize)},
    mViewRect{BaseRect::leftTopSize({0_bl, 0_bl}, static_cast<BaseDisplacement>(windowSize) )}
{}

bool Camera::isVisible(Util::BaseRect posRect) const {
    return hasCollision(mViewRect, posRect);
}

PixelPosition Camera::toScreenCoord(Util::BasePosition worldCoord) const {
    const auto viewCoord = worldCoord - mViewRect.leftTop();
    const auto relCoord = elemDiv(viewCoord, mViewRect.size() );
    const auto screenCoord = elemMul(relCoord, mWindowRect.size() ) + mWindowRect.leftTop();
    return screenCoord;
}


} // namespace Media

