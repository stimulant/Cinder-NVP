#pragma once

#include "cinder/Function.h"
#include "cinder/Area.h"
#include "cinder/Tween.h"
#include <vector>
#include <limits>

namespace ui {

class Bounds;

/******************************************************************************
 * Bounds
 * Extends ci::Area to provide useful functions for layout
 */

#define declare_bounds_point_layout_method( methodName ) \
	Bounds& methodName( const Bounds &bounds );\
	Bounds& methodName( const ci::Vec2i &pt );

class Bounds : public ci::Area
{
public:
	static Bounds	zero() { return Bounds( ci::Vec2i::zero(), ci::Vec2i::zero() ); }

	Bounds() : ci::Area() {}
	Bounds( const ci::Vec2i &UL, const ci::Vec2i &LR ) : ci::Area( UL, LR ) {}
	Bounds( const ci::Area &area ) : ci::Area( area ) {}
	Bounds( const ci::RectT< float > &rect ) : ci::Area( rect ) {}

	// Getters/setters
	ci::Vec2i		getUR() const { return ci::Vec2i( x2, y1 ); }
	ci::Vec2i		getLL() const { return ci::Vec2i( x1, y2 ); }
	Bounds &		setUL( ci::Vec2i ul ) { setX1( ul.x ); setY1( ul.y ); return *this; }
	Bounds &		setLR( ci::Vec2i lr ) { setX2( lr.x ); setY2( lr.y ); return *this; }
	Bounds &		setUR( ci::Vec2i ur ) { setX2( ur.x ); setY1( ur.y ); return *this; }
	Bounds &		setLL( ci::Vec2i ll ) { setX1( ll.x ); setY2( ll.y ); return *this; }

	// Layout
	declare_bounds_point_layout_method( centerOn )
	declare_bounds_point_layout_method( centerXOn )
	declare_bounds_point_layout_method( centerYOn )
	declare_bounds_point_layout_method( alignRightTo )
	declare_bounds_point_layout_method( alignLeftTo )
	declare_bounds_point_layout_method( alignTopTo )
	declare_bounds_point_layout_method( alignBottomTo )
	declare_bounds_point_layout_method( alignTopLeftTo )
	declare_bounds_point_layout_method( alignTopRightTo )
	declare_bounds_point_layout_method( alignBottomLeftTo )
	declare_bounds_point_layout_method( alignBottomRightTo )
	Bounds& inset( const Bounds &bounds, const ci::Vec2i &amount );
	Bounds& inset( const ci::Vec2i &amount );
	Bounds& outset( const Bounds &bounds, const ci::Vec2i &amount );
	Bounds& outset( const ci::Vec2i &amount );
};

}