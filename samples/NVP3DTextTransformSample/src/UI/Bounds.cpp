
#include "cinder/app/App.h"
#include "cinder/Timeline.h"
#include "UI/Bounds.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace ui;
using namespace std;
using namespace ci;
using namespace app;


/******************************************************************************
 * Bounds
 */
#define define_bounds_point_layout_method_convenience_delegators( methodName, boundsReferencePt )\
	Bounds& Bounds::methodName( const Bounds &bounds ) { return methodName( bounds.boundsReferencePt() ); }

define_bounds_point_layout_method_convenience_delegators( centerOn, getCenter );
Bounds& Bounds::centerOn( const Vec2i &pt )
{
	moveULTo( (Vec2i)(pt - ((Vec2d)getSize() * 0.5)) );	
	return *this;
}

define_bounds_point_layout_method_convenience_delegators( centerXOn, getCenter );
Bounds& Bounds::centerXOn( const ci::Vec2i &pt )
{
	centerOn( Vec2i( pt.x, (int)getCenter().y  ) );
	return *this;
}


define_bounds_point_layout_method_convenience_delegators( centerYOn, getCenter );
Bounds& Bounds::centerYOn( const ci::Vec2i &pt )
{
	centerOn( Vec2i( (int)getCenter().x, pt.y ) ); 
	return *this;
}

define_bounds_point_layout_method_convenience_delegators( alignRightTo, getUR );
Bounds& Bounds::alignRightTo( const ci::Vec2i &pt )
{
	moveULTo( Vec2i( pt.x - getSize().x, getUL().y ) );
	return *this;
}

define_bounds_point_layout_method_convenience_delegators( alignLeftTo, getUL );
Bounds& Bounds::alignLeftTo( const ci::Vec2i &pt )
{
	moveULTo( Vec2i( pt.x, getUL().y ) );
	return *this;
}

define_bounds_point_layout_method_convenience_delegators( alignTopTo, getUL );
Bounds& Bounds::alignTopTo( const ci::Vec2i &pt )
{
	moveULTo( Vec2i( getUL().x, pt.y ) );
	return *this;
}

define_bounds_point_layout_method_convenience_delegators( alignBottomTo, getLR );
Bounds& Bounds::alignBottomTo( const ci::Vec2i &pt )
{
	moveULTo( Vec2i( getUL().x, pt.y - getSize().y ) );
	return *this;
}

define_bounds_point_layout_method_convenience_delegators( alignTopRightTo, getUR );
Bounds& Bounds::alignTopRightTo( const ci::Vec2i &pt )
{
	moveULTo( Vec2i( pt.x - getSize().x, pt.y ) );
	return *this;
}

define_bounds_point_layout_method_convenience_delegators( alignTopLeftTo, getUL );
Bounds& Bounds::alignTopLeftTo( const ci::Vec2i &pt )
{
	moveULTo( Vec2i( pt.x, pt.y ) );
	return *this;
}

define_bounds_point_layout_method_convenience_delegators( alignBottomRightTo, getLR );
Bounds& Bounds::alignBottomRightTo( const ci::Vec2i &pt )
{
	moveULTo( Vec2i( pt.x - getSize().x, pt.y - getSize().y ) );
	return *this;
}

define_bounds_point_layout_method_convenience_delegators( alignBottomLeftTo, getLL );
Bounds& Bounds::alignBottomLeftTo( const ci::Vec2i &pt )
{
	moveULTo( Vec2i( pt.x, pt.y - getSize().y ) );
	return *this;
}

Bounds& Bounds::inset( const Bounds &bounds, const Vec2i &amount )
{
	setUL( bounds.getUL() );
	setLR( bounds.getLR() );
	return inset( amount );
}

Bounds& Bounds::inset( const Vec2i &amount )
{
	moveULTo( getUL() + amount );
	setLR( getLR() - amount * 2 );
	return *this;
}

Bounds& Bounds::outset( const Bounds &bounds, const Vec2i &amount )
{
	setUL( bounds.getUL() );
	setLR( bounds.getLR() );
	return outset( amount );
}

Bounds& Bounds::outset( const Vec2i &amount )
{
	moveULTo( getUL() - amount );
	setLR( getLR() + amount * 2 );
	return *this;
}