#pragma once

#include "cinder/app/App.h"
#include "cinder/Matrix.h"
#include "cinder/Rect.h"
#include "cinder/Color.h"
#include "cinder/Rand.h"

#include "PinchRecognizer.h"
#include "TapRecognizer.h"

using namespace ci;

class TouchRect {
public:

    PinchRecognizer mPinchRecognizer;
    TapRecognizer   mTapRecognizer;

    Matrix44f mMatrix;
    Rectf     mBounds;
    Color     mColor;
    
    float     mGlow;
    float     mFlipRotation, mFlipRotationGoal;
    bool      mIsPinching;
	int			mId;
    
    bool pinchBegan(PinchEvent event)
    {
		mIsPinching = true;
        return true;
    }
    bool pinchMoved(PinchEvent event)
    {
		if(mIsPinching){
            mMatrix = event.getTransformDelta() * mMatrix;
            return true;
        }
        return false;
    }
    bool pinchEnded(PinchEvent event)
    {
        mIsPinching = false;
        return false;
    }
    
    bool singleTapped(SingleTapEvent event)
    {
        mGlow = 1.0f;
        return true;
    }
    bool doubleTapped(DoubleTapEvent event)
    {
        mFlipRotationGoal = mFlipRotationGoal > 0 ? 0 : M_PI;
        return true;
    }
    
    bool getIsHit(TouchEvent::Touch touch)
    {
        //return mBounds.contains((mMatrix.inverted() * Vec3f(touch.getPos(), 0.0f)).xy());
		return mBounds.contains((Vec3f(touch.getPos(), 0.0f)).xy());
    }
    
    TouchRect(app::AppBasic *app, const Rectf &bounds, const Vec3f &pos, float rot, float id)
    : mIsPinching(false), mFlipRotation(0), mFlipRotationGoal(0), mGlow(0)
    {
		mId = id;
        mBounds = bounds;
        mMatrix.translate(pos);
        mMatrix.rotate(Vec3f::zAxis(), rot);
        mColor.set(CM_HSV, Vec3f(Rand::randFloat(), Rand::randFloat(), 1));
        
        mPinchRecognizer.init(app);
        mPinchRecognizer.registerBegan(this, &TouchRect::pinchBegan);
        mPinchRecognizer.registerMoved(this, &TouchRect::pinchMoved);
        mPinchRecognizer.registerEnded(this, &TouchRect::pinchEnded);
        mPinchRecognizer.setKeepTouchCallback(this, &TouchRect::getIsHit);
        
		//TapRecognizer must register last in order to not block touches from the Pinch Recognizer
		mTapRecognizer.init(app);
		mTapRecognizer.registerSingleTap(this, &TouchRect::singleTapped);
		mTapRecognizer.registerDoubleTap(this, &TouchRect::doubleTapped);
		mTapRecognizer.setKeepTouchCallback(this, &TouchRect::getIsHit);
    }
    
    void draw()
    {
        mFlipRotation = lerp(mFlipRotation, mFlipRotationGoal, 0.1f);
        gl::pushModelView();
        //gl::multModelView(mMatrix * Matrix44f::createRotation(Vec3f::yAxis(), mFlipRotation));
        gl::color(mColor - (Color(1,1,1) * mGlow));
        gl::drawSolidRect(mBounds);
        gl::popModelView();
        
        mGlow *= 0.9f;
    }

};
