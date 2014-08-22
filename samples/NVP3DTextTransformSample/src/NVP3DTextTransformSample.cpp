#include "cinder/app/AppBasic.h"
#include "cinder/params/Params.h"
#include "cinder/Timeline.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/Arcball.h"
#include "cinder/Rand.h"

#include "UI/Node/Node.h"
#include "UI/Nodes/NodeNVPTextBox3D.h"

#include "Utils/Globals.h"

#include "NVPFont.h"

using namespace ci;
using namespace ci::app;
using namespace ui;
using namespace node;
using namespace std;

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

	void addText(string pTxt);
	ci::params::InterfaceGl		mParams;

	float						mKerning;
	float						mStrokeWidth;
	bool						mFill;
	bool						mUnderline;

	bool						mDebugFonts;
	NVPFontRef					mFont;
	Globals*					mGlobals;
	ui::node::Node3DRef			mRoot;

	ci::CameraPersp						mCamera;
	ci::Vec3f							mEyePos;
	ci::Arcball							mArcball;
	std::vector<std::vector<NodeNVPTextBox3DRef>>	mTexts;

	std::vector<ci::Anim<float>>		mRots;
	std::vector<float>					mTargetRots;

	float								mSpawnTime;
	int									mCurTxt;
	std::vector<string>					mStrings;
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
	mEyePos = Vec3f ( 0.f, 0.f, -100.9f );
	mCamera.setEyePoint ( mEyePos );
	// Set up the arcball
	mArcball = Arcball ( getWindowSize() );
	mArcball.setRadius ( ( float ) getWindowHeight() * 0.5f );
	//set up nodes
	mRoot = ( Node3DRef ) ( new Node3D() );

	float mFontPt = 10;
	float emScale = 2048;
	float resolution = NVPTextBox::DPI;
	float fScale = mFontPt * resolution / ( NVPTextBox::DPI * emScale );
	//not sure why this scale is needed to match point size?
	float fscal = fScale * .75f;
	mRoot->setScale(fscal);

	mStrings.push_back("JUAN");
	mStrings.push_back("KEVIN");
	mStrings.push_back("DERRICK");
	mStrings.push_back("JEFF");
	mStrings.push_back("SHAKE");
	mStrings.push_back("CARL");
	mStrings.push_back("MIKE");
	mStrings.push_back("BUZZ");
	mStrings.push_back("AARON");
	mStrings.push_back("KEITH");
	NodeNVPTextBox3DRef	txt = NodeNVPTextBox3D::create ( mFont, mStrings[0], false, 10 );
	mRoot->addChild ( txt );
	std::vector<NodeNVPTextBox3DRef> texts;
	texts.push_back ( txt );
	mTexts.push_back(texts);
	mTargetRots.push_back(0);
	mRots.push_back(0);
	mSpawnTime = .83f;
	mCurTxt = 1;
	string nextWord = mStrings[mCurTxt];
	timeline().add( [this, nextWord]
    {
        addText(nextWord);
    }, timeline().getCurrentTime() + mSpawnTime );

	
	mRoot->treeSetup();
}
void NVP3DTextTransformSampleApp::addText(string pTxt){
	
	NodeNVPTextBox3DRef	mText = NodeNVPTextBox3D::create ( mFont, pTxt, false, 10 );
	NodeNVPTextBox3DRef	lastText = mTexts[mCurTxt-1];
	mText->setPosition( lastText->getBounds().getWidth(), 0.f, 0.f );
	ci::Anim<float> rot = 0;
	float rotval = ci::randFloat(-90,90);
	mTargetRots.push_back(rotval);
	//timeline().apply(&rot,0.f,rotval,.3,EaseInBack()).updateFn([rot,mText]{
		 
	//});
	
	lastText->addChild ( mText );
	mTexts.push_back ( mText );
	mRots.push_back( 180 );
	mCurTxt++;
	string nextWord = mStrings[mCurTxt%10];
	timeline().add( [this, nextWord]
    {
        addText(nextWord);
    }, timeline().getCurrentTime() + mSpawnTime );
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
	eye.z += event.getWheelIncrement() * 5.f;
	mCamera.setEyePoint ( eye );
}
void NVP3DTextTransformSampleApp::update()
{
	int i = 0;
	for(auto txt : mTexts){
		mRots[i] = (mTargetRots[i]-mRots[i])*.01+mRots[i];
		txt->setRotation( Vec3f( 0, 1, 0 ), toRadians(mRots[i]) );
		i++;
	}
	mRoot->treeUpdate();
}
void NVP3DTextTransformSampleApp::draw()
{
	gl::enableAlphaBlending();
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::clear ( Color ( 0, 0.1f, 0.2f ) );
	gl::setViewport ( getWindowBounds() );
	//gl::setMatricesWindow ( getWindowWidth(), getWindowHeight() );
	// Use arcball to rotate model view
	gl::setMatrices ( mCamera );
	mGlobals->viewPortCached = gl::getViewport();
	mGlobals->projMatrixCached = gl::getProjection();
	glMultMatrixf ( mArcball.getQuat() );
	mRoot->treeDraw();
	
	//gl::setViewport ( getWindowBounds() );
	//gl::setMatricesWindow ( getWindowWidth(), getWindowHeight() );
	gl::disableDepthRead();
	gl::disableDepthWrite();
	mParams.draw();
}

CINDER_APP_BASIC ( NVP3DTextTransformSampleApp, RendererGl ( RendererGl::AA_MSAA_32 ) )