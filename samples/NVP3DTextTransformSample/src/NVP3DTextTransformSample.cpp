#include "cinder/app/AppBasic.h"
#include "cinder/params/Params.h"
#include "cinder/Timeline.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/Arcball.h"

#include "UI/Node/Node.h"
#include "UI/Nodes/NodeText3D.h"

#include "Utils/Globals.h"

#include "NVPFont.h"

using namespace ci;
using namespace ci::app;
using namespace ui;
using namespace node;

//! Sample app showing depth tested, 3d transformed resolution independent dynamic text fields
class NVP3DTextTransformSampleApp : public AppBasic {
  public:
	void prepareSettings ( Settings* settings );
	void setup();
	void draw();
	void update();
	void mouseDown ( ci::app::MouseEvent event );
	void mouseDrag ( ci::app::MouseEvent event );
	void mouseWheel ( ci::app::MouseEvent event );

	ci::params::InterfaceGl		mParams;

	float						mKerning;
	float						mStrokeWidth;
	bool						mFill;
	bool						mUnderline;

	bool						mDebugFonts;
	NVPFontRef					mFont;
	Globals*					mGlobals;
	ui::node::Node3DRef			mRoot;

	ci::CameraPersp				mCamera;
	ci::Vec3f					mEyePos;
	ci::Arcball					mArcball;

};
void NVP3DTextTransformSampleApp::prepareSettings ( Settings* settings )
{
	//settings->setFullScreen( true );
	settings->setWindowPos ( 0, 0 );
	settings->setBorderless ( true );
	settings->setWindowSize ( 1920, 1080 );
}
void NVP3DTextTransformSampleApp::setup()
{
	//initializeNVPR("");
	mFill = true;
	mStrokeWidth = .05f;
	mUnderline = true;
	mDebugFonts = true;
	gl::enableAlphaBlending();
	gl::enableDepthRead();
	gl::enableDepthWrite();
	mParams = ci::params::InterfaceGl ( "Parameters", Vec2i ( 250, 500 ) );
	mKerning = 1.00f;
	mParams.addParam ( "kerning", &mKerning, "min=0.0000 max=2.000 step=.0001" );
	mParams.addParam ( "fill", &mFill );
	mParams.addParam ( "underline", &mUnderline );
	mParams.addParam ( "debug fonts", &mDebugFonts );
	mParams.addParam ( "stroke width", &mStrokeWidth, "min=0.0000 max=2.000 step=.001" );
	mGlobals = new Globals();
	mFont = NVPFont::create ( std::string ( "Lato-Heavy.ttf" ), false );
	// Set up the camera
	mCamera = CameraPersp ( getWindowWidth(), getWindowHeight(), 60.0f, 0.0001f, 1000.0f );
	mCamera.setViewDirection ( Vec3f ( 0.f, 0.f, 1.f ) );
	mEyePos = Vec3f ( 0.f, 0.f, -.9f );
	mCamera.setEyePoint ( mEyePos );
	// Set up the arcball
	mArcball = Arcball ( getWindowSize() );
	mArcball.setRadius ( ( float ) getWindowHeight() * 0.5f );
	//set up nodes
	mRoot = ( Node3DRef ) ( new Node3D() );
	NodeText3DRef				mText = NodeText3D::create ( mFont, "Test!", true, 90 );
	mRoot->addChild ( mText );
	mRoot->treeSetup();
}
void NVP3DTextTransformSampleApp::mouseDown ( MouseEvent event )
{
	// Rotate with arcball
	mArcball.mouseDown ( event.getPos() );
}
void NVP3DTextTransformSampleApp::mouseDrag ( MouseEvent event )
{
	mArcball.mouseDrag ( event.getPos() );
}
void NVP3DTextTransformSampleApp::mouseWheel ( MouseEvent event )
{
	// Zoom in/out with mouse wheel
	Vec3f eye = mCamera.getEyePoint();
	eye.z += event.getWheelIncrement() * 0.7f;
	mCamera.setEyePoint ( eye );
}
void NVP3DTextTransformSampleApp::update()
{
	mCamera.setEyePoint ( mEyePos );
}
void NVP3DTextTransformSampleApp::draw()
{
	gl::clear ( Color ( 0, 0.1f, 0.2f ) );
	gl::setViewport ( getWindowBounds() );
	gl::setMatricesWindow ( getWindowWidth(), getWindowHeight() );
	mGlobals->viewPortCached = gl::getViewport();
	mGlobals->projMatrixCached = gl::getProjection();
	// Use arcball to rotate model view
	gl::setMatrices ( mCamera );
	glMultMatrixf ( mArcball.getQuat() );
	mRoot->treeDraw();
	gl::setViewport ( getWindowBounds() );
	gl::setMatricesWindow ( getWindowWidth(), getWindowHeight() );
	gl::disableDepthRead();
	gl::disableDepthWrite();
	mParams.draw();
}

CINDER_APP_BASIC ( NVP3DTextTransformSampleApp, RendererGl ( RendererGl::AA_MSAA_32 ) )