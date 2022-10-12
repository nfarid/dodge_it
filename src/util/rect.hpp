
#ifndef HPP_UTIL_RECT_291659295492_
#define HPP_UTIL_RECT_291659295492_

#include "dimension.hpp"
#include "vec2.hpp"

#include <cassert>


namespace Util
{


/**
 * @brief A class to represent an axis-aligned bounding box
 */
template<typename T, typename R>
class Rect {
public:


    // [SECTION]: Static creation functions

    /**
     * @brief Create a rectangle from 2 opposite corners
     */
    [[nodiscard]] static constexpr Rect cornerCorner(Position<T, R> thisCorner_, Position<T, R> thatCorner_)
    {
        const Position<T, R> leftTop_ = {
            min(thisCorner_.x, thatCorner_.x),
            min(thisCorner_.y, thatCorner_.y),
        };
        const Position<T, R> rightBottom_ = {
            max(thisCorner_.x, thatCorner_.x),
            max(thisCorner_.y, thatCorner_.y),
        };
        const Displacement<T, R> halfExtent_ = (rightBottom_ - leftTop_) * 0.5_r;
        return Rect{leftTop_ + halfExtent_, halfExtent_};
    }

    /**
     * @brief Create a rectangle from a centre and size
     */
    [[nodiscard]] static constexpr Rect centreSize(Position<T, R> centre_, Displacement<T, R> size_)
    {
        assert("Rectangle size must be positive: " && size_.x >= 0_bl && size_.y >= 0_bl);
        const Displacement<T, R> halfExtent_ = size_ * 0.5_r;
        return Rect{centre_, halfExtent_};
    }

    /**
     * @brief Create a rectangle from a the left-top corner and size
     */
    [[nodiscard]] static constexpr Rect leftTopSize(Position<T, R> leftTop_, Displacement<T, R> size_)
    {
        const Displacement<T, R> halfExtent_ = size_ * 0.5_r;
        return Rect{leftTop_ + halfExtent_, halfExtent_};
    }

    /**
     * @brief Create a rectangle from a the right-bottom corner and size
     */
    [[nodiscard]] static constexpr Rect rightBottomSize(Position<T, R> rightBottom_, Displacement<T, R> size_)
    {
        const Displacement<T, R> halfExtent_ = size_ * 0.5_r;
        return Rect{rightBottom_ - halfExtent_, halfExtent_};
    }

    /**
     * @brief Create a rectangle from a the left-bottom corner and size
     */
    [[nodiscard]] static constexpr Rect leftBottomSize(Position<T, R> leftBottom_, Displacement<T, R> size_)
    {
        const Displacement<T, R> halfExtent_ = size_ * 0.5_r;
        const Position<T, R> centre_ = {leftBottom_.x + halfExtent_.x, leftBottom_.y - halfExtent_.y};
        return Rect{centre_, halfExtent_};
    }

    /**
     * @brief Create a rectangle from a the right-top corner and size
     */
    [[nodiscard]] static constexpr Rect rightTopSize(Position<T, R> rightTop_, Displacement<T, R> size_)
    {
        const Displacement<T, R> halfExtent_ = size_ * 0.5_r;
        const Position<T, R> centre_ = {rightTop_.x - halfExtent_.x, rightTop_.y + halfExtent_.y};
        return Rect{centre_, halfExtent_};
    }

    /**
     * @brief Create a zero sized rectangle with its centre at the origin
     */
    [[nodiscard]] static constexpr Rect zero() {
        return Rect{ Position<T, R>{}, Displacement<T, R>{} };
    }


    // [SECTION]: Position getter functions

    /**
     * @brief Get the position of the left-top corner
     */
    [[nodiscard]] constexpr Position<T, R> leftTop() const {
        return mCentre - mHalfExtent;
    }

    /**
     * @brief Get the position of the right-bottom corner
     */
    [[nodiscard]] constexpr Position<T, R> rightBottom() const {
        return mCentre + mHalfExtent;
    }

    /**
     * @brief Get the position of the left-bottom corner
     */
    [[nodiscard]] constexpr Position<T, R> leftBottom() const {
        return {mCentre.x - mHalfExtent.x,  mCentre.y + mHalfExtent.y};
    }

    /**
     * @brief Get the position of the right-top corner
     */
    [[nodiscard]] constexpr Position<T, R> rightTop() const {
        return {mCentre.x + mHalfExtent.x,  mCentre.y - mHalfExtent.y};
    }

    /**
     * @brief Get the x-position of the left
     */
    [[nodiscard]] constexpr PositionScalar<T, R> left() const {
        return mCentre.x - mHalfExtent.x;
    }

    /**
     * @brief Get the x-position of the right
     */
    [[nodiscard]] constexpr PositionScalar<T, R> right() const {
        return mCentre.x + mHalfExtent.x;
    }

    /**
     * @brief Get the y-position of the top
     */
    [[nodiscard]] constexpr PositionScalar<T, R> top() const {
        return mCentre.y - mHalfExtent.y;
    }

    /**
     * @brief Get the y-position of the bottom
     */
    [[nodiscard]] constexpr PositionScalar<T, R> bottom() const {
        return mCentre.y + mHalfExtent.y;
    }

    /**
     * @brief Get the position of the centre
     */
    [[nodiscard]] constexpr Position<T, R> centre() const {
        return mCentre;
    }

    /**
     * @brief Get the x-position of the centre
     */
    [[nodiscard]] constexpr PositionScalar<T, R> midX() const {
        return mCentre.x;
    }

    /**
     * @brief Get the y-position of the centre
     */
    [[nodiscard]] constexpr PositionScalar<T, R> midY() const {
        return mCentre.y;
    }


    // [SECTION]:  Size getter functions

    /**
     * @brief Get the rectangle's dimensions
     */
    [[nodiscard]] constexpr Displacement<T, R> size() const {
        return mHalfExtent * 2_r;
    }

    /**
     * @brief Get the rectangle's area
     */
    [[nodiscard]] constexpr Area<T, R> area() const {
        return mHalfExtent.x * mHalfExtent.y * 4_r;
    }

    /**
     * @brief Get the rectangle's width
     */
    [[nodiscard]] constexpr Distance<T, R> width() const {
        return mHalfExtent.x * 2_r;
    }

    /**
     * @brief Get the rectangle's height
     */
    [[nodiscard]] constexpr Distance<T, R> height() const {
        return mHalfExtent.y * 2_r;
    }


    // [SECTION]: Movement functions

    /**
     * @brief Move this rect by the specified displacement
     */
    constexpr void moveThisBy(Displacement<T, R> dis) {
        mCentre += dis;
    }

    /**
     * @brief Get a rect that is moved by this amount
     */
    [[nodiscard]] constexpr Rect movedBy(Displacement<T, R> dis) const {
        return Rect{mCentre + dis, mHalfExtent};
    }

    /**
     * @brief Move this rect by the specified distance along the x-axis
     */
    constexpr void moveThisHorBy(Distance<T, R> dis) {
        mCentre.x += dis;
    }

    /**
     * @brief Get a rect that is moved by this amount along the x-axis
     */
    [[nodiscard]] constexpr Rect movedHorBy(Distance<T, R> dis) const {
        return Rect{ {mCentre.x + dis, mCentre.y}, mHalfExtent};
    }

    /**
     * @brief Move this rect by the specified distance along the y-axis
     */
    constexpr void moveThisVerBy(Distance<T, R> dis) {
        mCentre.y += dis;
    }

    /**
     * @brief Get a rect that is moved by this amount along the y-axis
     */
    [[nodiscard]] constexpr Rect movedVerBy(Distance<T, R> dis) const {
        return Rect{ {mCentre.x, mCentre.y + dis}, mHalfExtent};
    }

    /**
     * @brief Set this rect's centre
     */
    constexpr void moveCentre(Position<T, R> centre_) {
        mCentre = centre_;
    }

    /**
     * @brief Get a rect with the specified centre
     */
    [[nodiscard]] constexpr Rect withCentre(Position<T, R> centre_) const {
        return Rect{centre_, mHalfExtent};
    }

    /**
     * @brief Move the rect so that the left-top is at the specified location
     * @note The size will not change
     */
    constexpr void moveLeftTop(Position<T, R> newLeftTop_) {
        const auto dis = newLeftTop_ - leftTop();
        moveThisBy(dis);
    }

    /**
     * @brief Obtain a moved rect with the left-top is at the specified location
     * @note New rect will have same size as old rect
     */
    [[nodiscard]] constexpr Rect withMovedLeftTop(Position<T, R> newLeftTop_) const {
        const auto dis = newLeftTop_ - leftTop();
        return movedBy(dis);
    }

    /**
     * @brief Change the left-top corner
     * @note The right-bottom corner will not change
     */
    constexpr void setLeftTop(Position<T, R> newLeftTop_) {
        const auto rightBottom_ = rightBottom();
        mHalfExtent = 0.5_r * (rightBottom_ - newLeftTop_);
        mCentre = newLeftTop_ + mHalfExtent;
    }

    /**
     * @brief Obtain a rect with the specified left-top corner
     * @note New rect will have the same right-bottom corner as the old-rect
     */
    [[nodiscard]] constexpr Rect withLeftTopAs(Position<T, R> newLeftTop_) const {
        const auto rightBottom_ = rightBottom();
        const auto halfExtent_ = 0.5_r * (rightBottom_ - newLeftTop_);
        const auto centre_ = newLeftTop_ + halfExtent_;
        return Rect{centre_, halfExtent_};
    }

    /**
     * @brief Move the rect so that the right-top is at the specified location
     * @note The size will not change
     */
    constexpr void moveRightTop(Position<T, R> newRightTop_) {
        const auto dis = newRightTop_ - rightTop();
        moveThisBy(dis);
    }

    /**
     * @brief Obtain a moved rect with the right-top is at the specified location
     * @note New rect will have same size as old rect
     */
    [[nodiscard]] constexpr Rect withMovedRightTop(Position<T, R> newRightTop_) const {
        const auto dis = newRightTop_ - rightTop();
        return movedBy(dis);
    }

    /**
     * @brief Change the right-top corner
     * @note The left-bottom corner will not change
     */
    constexpr void setRightTop(Position<T, R> newRightTop_) {
        const auto leftBottom_ = leftBottom();
        mHalfExtent = 0.5_r * Displacement<T, R>{
            newRightTop_.x - leftBottom_.x,
            leftBottom_.y - newRightTop_.y,
        };
        mCentre = {
            newRightTop_.x - mHalfExtent.x,
            newRightTop_.y + mHalfExtent.y,
        };
    }

    /**
     * @brief Obtain a rect with the specified right-top corner
     * @note New rect will have the same left-bottom corner as the old-rect
     */
    [[nodiscard]] constexpr Rect withRightTopAs(Position<T, R> newRightTop_) const {
        const auto leftBottom_ = leftBottom();
        const auto halfExtent_ = 0.5_r * Displacement<T, R>{
            newRightTop_.x - leftBottom_.x,
            leftBottom_.y - newRightTop_.y,
        };
        const Position<T, R> centre_ = {
            newRightTop_.x - halfExtent_.x,
            newRightTop_.y + halfExtent_.y,
        };
        return Rect{centre_, halfExtent_};
    }

    /**
     * @brief Move the rect so that the left-bottom is at the specified location
     * @note The size will not change
     */
    constexpr void moveLeftBottom(Position<T, R> newLeftBottom_) {
        const auto dis = newLeftBottom_ - leftBottom();
        moveThisBy(dis);
    }

    /**
     * @brief Obtain a moved rect with the left-bottom is at the specified location
     * @note New rect will have same size as old rect
     */
    [[nodiscard]] constexpr Rect withMovedLeftBottom(Position<T, R> newLeftBottom_) const {
        const auto dis = newLeftBottom_ - leftBottom();
        return movedBy(dis);
    }

    /**
     * @brief Change the left-bottom corner
     * @note The right-top corner will not change
     */
    constexpr void setLeftBottom(Position<T, R> newLeftBottom_) {
        const auto rightTop_ = rightTop();
        mHalfExtent = 0.5_r * Displacement<T, R>{
            rightTop_.x - newLeftBottom_.x,
            newLeftBottom_.y - rightTop_.y,
        };
        mCentre = {
            newLeftBottom_.x + mHalfExtent.x,
            newLeftBottom_.y - mHalfExtent.y,
        };
    }

    /**
     * @brief Obtain a rect with the specified left-bottom corner
     * @note New rect will have the same right-top corner as the old-rect
     */
    [[nodiscard]] constexpr Rect withLeftBottomAs(Position<T, R> newLeftBottom_) const {
        const auto rightTop_ = rightTop();
        const auto halfExtent_ = 0.5_r * Displacement<T, R>{
            rightTop_.x - newLeftBottom_.x,
            newLeftBottom_.y - rightTop_.y,
        };
        const Position<T, R> centre_ = {
            newLeftBottom_.x + halfExtent_.x,
            newLeftBottom_.y - halfExtent_.y,
        };
        return Rect{centre_, halfExtent_};
    }

    /**
     * @brief Move the rect so that the right-bottom is at the specified location
     * @note The size will not change
     */
    constexpr void moveRightBottom(Position<T, R> newRightBottom_) {
        const auto dis = newRightBottom_ - rightBottom();
        moveThisBy(dis);
    }

    /**
     * @brief Obtain a moved rect with the right-bottom is at the specified location
     * @note New rect will have same size as old rect
     */
    [[nodiscard]] constexpr Rect withMovedRightBottom(Position<T, R> newRightBottom_) const {
        const auto dis = newRightBottom_ - rightBottom();
        return movedBy(dis);
    }

    /**
     * @brief Change the right-bottom corner
     * @note The left-top corner will not change
     */
    constexpr void setRightBottom(Position<T, R> newRightBottom_) {
        const auto leftTop_ = leftTop();
        mHalfExtent = 0.5_r * (newRightBottom_ - leftTop_);
        mCentre = newRightBottom_ - mHalfExtent;
    }

    /**
     * @brief Obtain a rect with the specified right-bottom corner
     * @note New rect will have the same left-top corner as the old-rect
     */
    [[nodiscard]] constexpr Rect withRightBottomAs(Position<T, R> newRightBottom_) const {
        const auto leftTop_ = leftTop();
        const auto halfExtent_ = 0.5_r * (newRightBottom_ - leftTop_);
        const auto centre_ = newRightBottom_ - halfExtent_;
        return Rect{centre_, halfExtent_};
    }

    /**
     * @brief Move the rect so that the left is at the specified x-location
     * @note The size will not change
     */
    constexpr void moveLeft(PositionScalar<T, R> newLeft_) {
        const auto dis = newLeft_ - left();
        moveThisHorBy(dis);
    }

    /**
     * @brief Obtain a moved rect with the left is at the specified x-location
     * @note New rect will have same size as old rect
     */
    [[nodiscard]] constexpr Rect withMovedLeft(PositionScalar<T, R> newLeft_) const {
        const auto dis = newLeft_ - left();
        return movedHorBy(dis);
    }

    /**
     * @brief Change the left edge
     * @note The right edge will not change
     */
    constexpr void setLeft(PositionScalar<T, R> newLeft_) {
        mHalfExtent.x = 0.5_r * (right() - newLeft_);
        mCentre.x = newLeft_ + mHalfExtent.x;
    }

    /**
     * @brief Obtain a rect with the specified left edge
     * @note New rect will have the same right edge as the old rect
     */
    [[nodiscard]] constexpr Rect withLeftAs(PositionScalar<T, R> newLeft_) const {
        const Displacement<T, R> newHalfExtent = {
            0.5_r * (right() - newLeft_),
            mHalfExtent.y,
        };
        const Position<T, R> newCentre = {
            newLeft_ + newHalfExtent.x,
            mCentre.y,
        };
        return Rect{newCentre, newHalfExtent};
    }

    /**
     * @brief Move the rect so that the right is at the specified x-location
     * @note The size will not change
     */
    constexpr void moveRight(PositionScalar<T, R> newRight_) {
        const auto dis = newRight_ - right();
        moveThisHorBy(dis);
    }

    /**
     * @brief Obtain a moved rect with the right is at the specified x-location
     * @note New rect will have same size as old rect
     */
    [[nodiscard]] constexpr Rect withMovedRight(PositionScalar<T, R> newRight_) const {
        const auto dis = newRight_ - right();
        return movedHorBy(dis);
    }

    /**
     * @brief Change the right edge
     * @note The left edge will not change
     */
    constexpr void setRight(PositionScalar<T, R> newRight_) {
        mHalfExtent.x = 0.5_r * (newRight_ - left() );
        mCentre.x = newRight_ - mHalfExtent.x;
    }

    /**
     * @brief Obtain a rect with the specified right edge
     * @note New rect will have the same left edge as the old rect
     */
    [[nodiscard]] constexpr Rect withRightAs(PositionScalar<T, R> newRight_) const {
        const Displacement<T, R> newHalfExtent = {
            0.5_r * (newRight_ - left() ),
            mHalfExtent.y,
        };
        const Position<T, R> newCentre = {
            newRight_ - newHalfExtent.x,
            mCentre.y,
        };
        return Rect{newCentre, newHalfExtent};
    }

    /**
     * @brief Move the rect so that the top is at the specified y-location
     * @note The size will not change
     */
    constexpr void moveTop(PositionScalar<T, R> newTop_) {
        const auto dis = newTop_ - top();
        moveThisVerBy(dis);
    }

    /**
     * @brief Obtain a moved rect with the top is at the specified y-location
     * @note New rect will have same size as old rect
     */
    [[nodiscard]] constexpr Rect withMovedTop(PositionScalar<T, R> newTop_) const {
        const auto dis = newTop_ - top();
        return movedVerBy(dis);
    }

    /**
     * @brief Change the top edge
     * @note The bottom edge will not change
     */
    constexpr void setTop(PositionScalar<T, R> newTop_) {
        mHalfExtent.y = 0.5_r * (bottom() - newTop_);
        mCentre.y = newTop_ + mHalfExtent.y;
    }

    /**
     * @brief Obtain a rect with the specified top edge
     * @note New rect will have the same bottom edge as the old rect
     */
    [[nodiscard]] constexpr Rect withTopAs(PositionScalar<T, R> newTop_) const {
        const Displacement<T, R> newHalfExtent = {
            mHalfExtent.x,
            0.5_r * (bottom() - newTop_),
        };
        const Position<T, R> newCentre = {
            mCentre.x,
            newTop_ + newHalfExtent.y,
        };
        return Rect{newCentre, newHalfExtent};
    }

    /**
     * @brief Move the rect so that the bottom is at the specified y-location
     * @note The size will not change
     */
    constexpr void moveBottom(PositionScalar<T, R> newBottom_) {
        const auto dis = newBottom_ - bottom();
        moveThisVerBy(dis);
    }

    /**
     * @brief Obtain a moved rect with the bottom is at the specified y-location
     * @note New rect will have same size as old rect
     */
    [[nodiscard]] constexpr Rect withMovedBottom(PositionScalar<T, R> newBottom_) const {
        const auto dis = newBottom_ - bottom();
        return movedVerBy(dis);
    }

    /**
     * @brief Change the bottom edge
     * @note The top edge will not change
     */
    constexpr void setBottom(PositionScalar<T, R> newBottom_) {
        mHalfExtent.y = 0.5_r * (newBottom_ - top() );
        mCentre.y = newBottom_ - mHalfExtent.y;
    }

    /**
     * @brief Obtain a rect with the specified bottom edge
     * @note New rect will have the same top edge as the old rect
     */
    [[nodiscard]] constexpr Rect withBottomAs(PositionScalar<T, R> newBottom_) const {
        const Displacement<T, R> newHalfExtent = {
            mHalfExtent.x,
            0.5_r * (newBottom_ - top() ),
        };
        const Position<T, R> newCentre = {
            mCentre.x,
            newBottom_ - newHalfExtent.y,
        };
        return Rect{newCentre, newHalfExtent};
    }


    // [SECTION]: Scale functions

    /**
     * @brief Change the rect's size by the specified scale factor with its centre as the scale origin
     */
    constexpr void scaleThis(Real scaleFactor) {
        mHalfExtent *= scaleFactor;
    }

    /**
     * @brief Change the rect's size by the specified scale factor and scale origin
     */
    constexpr void scaleThis(Real scaleFactor, Position<T, R> scaleOrigin) {
        const auto scaleOriginToCentre = mCentre - scaleOrigin;
        const auto newScaleOriginToCentre = scaleOriginToCentre * scaleFactor;
        mHalfExtent *= scaleFactor;
        mCentre = scaleOrigin + newScaleOriginToCentre;
    }

    /**
     * @brief Obtain a rect with a size that's scaled by the specified scale factor with its centre as the scale origin
     */
    [[nodiscard]] constexpr Rect withScaled(Real scaleFactor) const {
        return Rect{mCentre, mHalfExtent* scaleFactor};
    }

    /**
     * @brief Obtain a rect with a scaled size by the specified scale factor and scale origin
     */
    [[nodiscard]] constexpr Rect withScaled(Real scaleFactor, Position<T, R> scaleOrigin) const {
        const auto scaleOriginToCentre = mCentre - scaleOrigin;
        const auto newScaleOriginToCentre = scaleOriginToCentre * scaleFactor;
        const auto halfExtent_ = mHalfExtent * scaleFactor;
        const auto centre_ = scaleOrigin + newScaleOriginToCentre;
        return Rect{centre_, halfExtent_};
    }

    /**
     * @brief Change the rect's width by the specified scale factor with its centre as the scale origin
     */
    constexpr void scaleThisWidth(Real scaleFactor) {
        mHalfExtent.x *= scaleFactor;
    }

    /**
     * @brief Change the rect's width by the specified scale factor and horizontal scale origin
     */
    constexpr void scaleThisWidth(Real scaleFactor, PositionScalar<T, R> scaleOriginX) {
        const auto scaleOriginToCentreX = mCentre.x - scaleOriginX;
        const auto newScaleOriginToCentreX = scaleOriginToCentreX * scaleFactor;
        mHalfExtent.x *= scaleFactor;
        mCentre.x = scaleOriginX + newScaleOriginToCentreX;
    }

    /**
     * @brief Obtain a rect with a width that's scaled by the specified scale factor with its centre as the scale origin
     */
    [[nodiscard]] constexpr Rect withScaledWidth(Real scaleFactor) const {
        return Rect{mCentre, {mHalfExtent.x* scaleFactor, mHalfExtent.y} };
    }

    /**
     * @brief Obtain a rect with a scaled width by the specified scale factor and horizontal scale origin
     */
    [[nodiscard]] constexpr Rect withScaledWidth(Real scaleFactor, PositionScalar<T, R> scaleOriginX) const
    {
        const auto scaleOriginToCentreX = mCentre.x - scaleOriginX;
        const auto newScaleOriginToCentreX = scaleOriginToCentreX * scaleFactor;
        const Displacement<T, R> halfExtent_ = {
            mHalfExtent.x* scaleFactor,
            mHalfExtent.y,
        };
        const Position<T, R> centre_ = {
            scaleOriginX + newScaleOriginToCentreX,
            mCentre.y,
        };
        return Rect{centre_, halfExtent_};
    }

    /**
     * @brief Change the rect's height by the specified scale factor with its centre as the scale origin
     */
    constexpr void scaleThisHeight(Real scaleFactor) {
        mHalfExtent.y *= scaleFactor;
    }

    /**
     * @brief Change the rect's height by the specified scale factor and vertical scale origin
     */
    constexpr void scaleThisHeight(Real scaleFactor, PositionScalar<T, R> scaleOriginY) {
        const auto scaleOriginToCentreY = mCentre.y - scaleOriginY;
        const auto newScaleOriginToCentreY = scaleOriginToCentreY * scaleFactor;
        mHalfExtent.y *= scaleFactor;
        mCentre.y = scaleOriginY + newScaleOriginToCentreY;
    }

    /**
     * @brief Obtain a rect with a height that's scaled by the specified scale factor with its centre as the scale origin
     */
    [[nodiscard]] constexpr Rect withScaledHeight(Real scaleFactor) const {
        return Rect{mCentre, {mHalfExtent.x, mHalfExtent.y * scaleFactor} };
    }

    /**
     * @brief Obtain a rect with a scaled height by the specified scale factor and vertical scale origin
     */
    [[nodiscard]] constexpr Rect withScaledHeight(Real scaleFactor, PositionScalar<T, R> scaleOriginY) const
    {
        const auto scaleOriginToCentreY = mCentre.y - scaleOriginY;
        const auto newScaleOriginToCentreY = scaleOriginToCentreY * scaleFactor;
        const Displacement<T, R> halfExtent_ = {
            mHalfExtent.x,
            mHalfExtent.y * scaleFactor,
        };
        const Position<T, R> centre_ = {
            mCentre.x,
            scaleOriginY + newScaleOriginToCentreY,
        };
        return Rect{centre_, halfExtent_};
    }

    /**
     * @brief Change the rect's width and height by the specified scale factor with its centre as the scale origin
     */
    constexpr void scaleThisBoth(Vec2<Real> scaleFactor) {
        scaleThisWidth(scaleFactor.x);
        scaleThisHeight(scaleFactor.y);
    }

    /**
     * @brief Change the rect's width and height by the specified scale factor and scale origin
     */
    constexpr void scaleThisBoth(Vec2<Real> scaleFactor, Position<T, R> scaleOrigin) {
        scaleThisWidth(scaleFactor.x, scaleOrigin.x);
        scaleThisHeight(scaleFactor.y, scaleOrigin.y);
    }

    /**
     * @brief Obtain a rect with a width and height that's scaled by the specified scale factor with its centre as the scale origin
     */
    [[nodiscard]] constexpr Rect withScaledBoth(Vec2<Real> scaleFactor) const {
        return withScaledWidth(scaleFactor.x).withScaledHeight(scaleFactor.y);
    }

    /**
     * @brief Obtain a rect with a scaled width and height by the specified scale factor and vertical scale origin
     */
    [[nodiscard]] constexpr Rect withScaledBoth(Vec2<Real> scaleFactor, Position<T, R> scaleOrigin) const
    {
        return withScaledWidth(scaleFactor.x, scaleOrigin.x).withScaledHeight(scaleFactor.y, scaleOrigin.y);
    }


    // [SECTION]: Size setter function

    /**
     * @brief Change the rect's size to specified length with its centre as the scale origin
     */
    constexpr void setSize(Distance<T, R> newLength) {
        const auto halfNewLength = 0.5_r * newLength;
        mHalfExtent = {halfNewLength, halfNewLength};
    }

    /**
     * @brief Obtain a rect with the specified length and with its centre as the scale origin
     */
    constexpr Rect withSize(Distance<T, R> newLength) const {
        const auto halfNewLength = 0.5_r * newLength;
        return Rect{mCentre, {halfNewLength, halfNewLength} };
    }

    /**
     * @brief Change the rect's width to specified length with its centre as the scale origin
     */
    constexpr void setWidth(Distance<T, R> newWidth) {
        mHalfExtent.x = 0.5_r * newWidth;
    }

    /**
     * @brief Obtain a rect with the specified width and with its centre as the scale origin
     */
    constexpr Rect withWidth(Distance<T, R> newWidth) const {
        return Rect{
            mCentre,
            {0.5_r * newWidth, mHalfExtent.y}
        };
    }

    /**
     * @brief Change the rect's height to specified length with its centre as the scale origin
     */
    constexpr void setHeight(Distance<T, R> newHeight) {
        mHalfExtent.y = 0.5_r * newHeight;
    }

    /**
     * @brief Obtain a rect with the specified height and with its centre as the scale origin
     */
    constexpr Rect withHeight(Distance<T, R> newHeight) const {
        return Rect{
            mCentre,
            {mHalfExtent.x, 0.5_r * newHeight},
        };
    }

    /**
     * @brief Change the rect's size to specified size with its centre as the scale origin
     */
    constexpr void setSize(Displacement<T, R> newSize) {
        mHalfExtent = 0.5_r * newSize;
    }

    /**
     * @brief Obtain a rect with the specified size and with its centre as the scale origin
     */
    constexpr Rect withSize(Displacement<T, R> newSize) const {
        return Rect{mCentre, 0.5_r * newSize};
    }


    // [SECTION]: Misc functions

    /**
     * @brief Checks if the rectangle fully contains the position
     * @note If the position is on the edge or corner, then it would return false
     */
    [[nodiscard]] constexpr bool contains(Position<T, R> pos) const {
        return pos.x > left() &&
               pos.x < right() &&
               pos.y > top() &&
               pos.y < bottom();
    }

    /**
     * @brief Checks if the size of the rectangle is valid (i.e. neither width nor height are negative)
     * @note Rectangles should be valid for non-trivial operations
     */
    [[nodiscard]] constexpr bool isValid() const noexcept {
        return mHalfExtent.x >= 0_bl && mHalfExtent.y >= 0_bl;
    }

    /**
     * @brief Checks if the area of the rectangle is zero
     */
    [[nodiscard]] constexpr bool isZero() const noexcept {
        return mHalfExtent.x.isZero() || mHalfExtent.y.isZero();
    }

    /**
     * @brief Makes the height and width non-negative
     * @note Rectangles should be valid for non-trivial operations
     */
    constexpr void makeValid() {
        mHalfExtent.x = mHalfExtent.x > 0_bl ? mHalfExtent.x :
                    mHalfExtent.x < 0_bl ? -mHalfExtent.x :
                        0_bl;
        mHalfExtent.y = mHalfExtent.y > 0_bl ? mHalfExtent.y :
                    mHalfExtent.y < 0_bl ? -mHalfExtent.y :
                        0_bl;
    }

    [[nodiscard]] constexpr friend bool operator==(const Rect<T, R>& lhs, const Rect<T, R>& rhs) {
        return lhs.mCentre == rhs.mCentre && lhs.mHalfExtent == rhs.mHalfExtent;
    }

    [[nodiscard]] constexpr friend bool operator!=(const Rect<T, R>& lhs, const Rect<T, R>& rhs) {
        return !(lhs == rhs);
    }

private:
    explicit constexpr Rect(Position<T, R> centre_, Displacement<T, R> halfExtent_) :
        mCentre{centre_},
        mHalfExtent{halfExtent_}
    {}

    Position<T, R> mCentre;
    Displacement<T, R> mHalfExtent;
};


// [SECTION]: Additional functions

/**
 * @brief Checks if 2 rectangles are interesecting
 * @param lhs - One of the valid rectangles to be tested for collision (must be valid)
 * @param rhs - One of the valid rectangles to be tested for collision (must be valid)
 * @note If only the edges are touching (i.e. interesection length is zero) then it return false
 */
template<typename T, typename R>
[[nodiscard]] constexpr bool hasCollision(const Rect<T, R>& lhs, const Rect<T, R>& rhs) {
    assert(lhs.isValid() && rhs.isValid() && "hasCollision needs both rects to be valid");
    return lhs.left()   < rhs.right()   &&
           lhs.right()  > rhs.left()    &&
           lhs.top()    < rhs.bottom()  &&
           lhs.bottom() > rhs.top();
}

/**
 * @brief Obtain the intersection of both rectangles
 * @param lhs - One of the valid rectangles to be tested for intersection (must be valid)
 * @param rhs - One of the valid rectangles to be tested for intersection (must be valid)
 * @return the rect that represents the overlap, or a zero-sized rect if there's no overlap
 */
template<typename T, typename R>
[[nodiscard]] constexpr Rect<T, R> intersection(const Rect<T, R>& lhs, const Rect<T, R>& rhs) {
    assert(lhs.isValid() && rhs.isValid() && "intersection needs both rects to be valid");
    const auto left =   max(lhs.left(), rhs.left() );
    const auto right =  min(lhs.right(), rhs.right() );
    if(left > right)
        return Rect<T, R>::zero();
    const auto top  =   max(lhs.top(), rhs.top() );
    const auto bottom = min(lhs.bottom(), rhs.bottom() );
    if(top > bottom)
        return Rect<T, R>::zero();
    return Rect<T, R>::cornerCorner({left, top}, {right, bottom});
}


// [SECTION]: Operators

template<typename T, typename R>
inline Rect<T, R> operator+(const Rect<T, R>& rect, Displacement<T, R> dis) {
    return rect.movedBy(dis);
}

template<typename T, typename R>
inline Rect<T, R> operator+(Displacement<T, R> dis, const Rect<T, R>& rect) {
    return rect.movedBy(dis);
}

template<typename T, typename R>
inline Rect<T, R> operator-(const Rect<T, R>& rect, Displacement<T, R> dis) {
    return rect.movedBy(-dis);
}

template<typename T, typename R>
inline Rect<T, R> operator-(Displacement<T, R> dis, const Rect<T, R>& rect) {
    return rect.movedBy(-dis);
}

template<typename T, typename R>
inline Rect<T, R> operator*(const Rect<T, R>& rect, Real scaleFactor) {
    return rect.withScaled(scaleFactor);
}

template<typename T, typename R>
inline Rect<T, R> operator*(Real scaleFactor, const Rect<T, R>& rect) {
    return rect.withScaled(scaleFactor);
}

template<typename T, typename R>
inline Rect<T, R> operator/(const Rect<T, R>& rect, Real scaleFactor) {
    return rect.withScaled(1_r / scaleFactor);
}

/**
 * @brief Outputs the rect's to a stream
 */
template<typename T, typename R>
inline std::ostream& operator<<(std::ostream& os, const Rect<T, R>& rect) {
    return os<<"{left_top: "<<rect.leftTop()<<" ; right_bottom: "<<rect.rightBottom()<<"}";
}

using BaseRect = Rect<Real, BaseRatio>;


}// namespace Util

#endif  // ifndef HPP_UTIL_RECT_291659295492_
