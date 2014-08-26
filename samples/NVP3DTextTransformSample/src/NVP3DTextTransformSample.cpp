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


namespace nvp {

class TextStrip;
typedef boost::shared_ptr<class TextStrip>	TextStripRef;
class TextStrip : public node::Node3D {
  public:

	static TextStripRef create ( NVPFontRef	pFont )
	{
		return ( TextStripRef ) ( new TextStrip ( pFont ) );
	}
	TextStrip ( NVPFontRef	pFont )
	{
		mFontRef = pFont;
		mStrings.push_back ( "JUAN" );
		mStrings.push_back ( "KEVIN" );
		mStrings.push_back ( "DERRICK" );
		mStrings.push_back ( "JEFF" );
		mStrings.push_back ( "SHAKE" );
		mStrings.push_back ( "CARL" );
		mStrings.push_back ( "MIKE" );
		mStrings.push_back ( "BUZZ" );
		mStrings.push_back ( "AARON" );
		mStrings.push_back ( "KEITH" );
		mSpawnTime = .4f;
		mMaxTxt = 14;
	};

	void start()
	{
		mReset = 0;
		mCurTxt = 0;
		mTexts.clear();
		mTexts.clear();
		string nextWord = mStrings[mCurTxt % mStrings.size()];
		addText ( nextWord );
		timeline().add ( [this] {
			for(auto txt : mTexts){
				auto pitch = txt->getRotation();
				float test = pitch.getYaw();
				test = toDegrees(test);
				txt->setTargetRot ( test, 180.f );
			}
			start();
		}, timeline().getCurrentTime() + 5.5f );
	}

	void addText ( std::string pTxt )
	{
		NodeNVPTextBox3DRef	mText = NodeNVPTextBox3D::create ( mFontRef, pTxt, false, 10 );

		if ( mTexts.size() == 0 ) {
			mText->setPosition ( 0.f, 0.f, 0 );
			addChild ( mText );
		}
		else {
			NodeNVPTextBox3DRef	lastText = mTexts[mCurTxt - 1];
			mText->setPosition ( lastText->getBounds().getWidth(), 0.f, 0 );
			lastText->addChild ( mText );
		}

		int rotval = ci::randInt ( 0, 2 );

		if ( mCurTxt < mMaxTxt / 2 )
			rotval = -rotval;

		mText->setRotation ( Vec3f ( 0, 1, 0 ), toRadians ( 180.f ) );
		mText->setTargetRot ( 180.f, rotval * 45.f );
		timeline().apply ( &mText->mLife, 1.f, .2f, ci::EaseOutQuad() ).finishFn ( [ &, mText] {
			//timeline().apply(&mText->getLife(),0.f,.3f,ci::EaseInBounce()).delay(2.f);
		} );
		mTexts.push_back ( mText );

		if ( mCurTxt < mMaxTxt ) {
			string nextWord = mStrings[mCurTxt % mStrings.size()];
			timeline().add ( [this, nextWord] {
				addText ( nextWord );
			}, timeline().getCurrentTime() + mSpawnTime );
			mCurTxt++;
		}
	}
	void update ( double elapsed = 0.0 )
	{
	};

  private:
	std::vector<ci::Anim<float>>		mRots;
	std::vector<float>					mTargetRots;
	int									mCurTxt;
	NVPFontRef							mFontRef;
	std::vector<NodeNVPTextBox3DRef>	mTexts;
	std::vector<string>					mStrings;
	float								mSpawnTime;
	int									mMaxTxt;
	int									mReset;
};
}

using namespace nvp;

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

	ci::CameraPersp						mCamera;
	ci::Vec3f							mEyePos;
	ci::Arcball							mArcball;
	std::vector<string>					mStrings;
	std::vector<TextStripRef>			mStrips;

	float								mSpawnTime;
	int									mNumRows;
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
	mRoot->setScale ( fscal );
	mNumRows = 16;

	for ( int i = 0; i < mNumRows; i++ ) {
		TextStripRef strip = TextStrip::create ( mFont );
		mRoot->addChild ( strip );
		strip->setPosition ( 0, i * 1200, 0 );
		strip->start();
		mStrips.push_back ( strip );
	}

	for ( auto strip : mStrips )
	{
		strip->start();
		console() << "mstrips start" << endl;
	}

	timeline().add ( [&] {
		
	}, timeline().getCurrentTime() + 13.f )->setLoop ( true );
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
	eye.z += event.getWheelIncrement() * 5.f;
	mCamera.setEyePoint ( eye );
}
void NVP3DTextTransformSampleApp::update()
{
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