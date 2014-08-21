
#include "UI/Nodes/NodeText3D.h"

#include "cinder/app/AppBasic.h"
#include "cinder/Utilities.h"

using namespace ci;
using namespace ci::app;
using namespace ui::node;
using namespace ui;

using namespace std;

NodeText3D::NodeText3D ( NVPFontRef pFont, string pTxt, bool pDebug, float pPointSize )
{
	mTextBox = NVPTextBox::create();
	mTextBox->setText ( pTxt );
	mTextBox->setFont ( pFont );
	mTextBox->setDebugDraw ( pDebug );
	mTextBox->setFontPt ( pPointSize );
}

NodeText3D::~NodeText3D ( void )
{
}

void NodeText3D::setup()
{
	Node3D::setup();
}

void NodeText3D::update ( double elapsed )
{
	Node3D::update();
}

void NodeText3D::draw()
{
	gl::translate ( getAnchor() );
	gl::color ( Color ( 1, 0, 0 ) );
	gl::drawCoordinateFrame ( .1, .01, .01 );
	gl::translate ( -getAnchor() );
	mTextBox->draw();
}
