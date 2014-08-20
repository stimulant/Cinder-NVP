#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "NVPTextBox.h"
#include "NVPFont.h"
#include "cinder/params/Params.h"
#include "cinder/Timeline.h"

#include "cinder/gl/TextureFont.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"

#include "Utils\Globals.h"

using namespace ci;
using namespace ci::app;

//! Sample app showing depth tested, 3d transformed resolution independent dynamic text fields
class NVP3DTextTransformSampleApp : public AppBasic {
  public:
	void prepareSettings ( Settings* settings );
	void setup();
	void draw();
	void update();

	std::vector<NVPTextBoxRef>		mTexts;
	NVPTextBoxRef					mText2;

	ci::params::InterfaceGl			mParams;

	float		mKerning;
	float		mStrokeWidth;
	bool		mFill;
	bool		mUnderline;

	bool		mDebugFonts;
	NVPFontRef	mFont;
    Globals*	mGlobals;
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
	mFont = NVPFont::create ( std::string ( "Lato-Heavy.ttf" ), false );

	mParams = ci::params::InterfaceGl ( "Parameters", Vec2i ( 250, 500 ) );
	mKerning = 1.00f;
	mParams.addParam ( "kerning", &mKerning, "min=0.0000 max=2.000 step=.0001" );
	mParams.addParam ( "fill", &mFill );
	mParams.addParam ( "underline", &mUnderline );
	mParams.addParam ( "debug fonts", &mDebugFonts );
	mParams.addParam ( "stroke width", &mStrokeWidth, "min=0.0000 max=2.000 step=.001" );
	
    mGlobals = new Globals();
}

void NVP3DTextTransformSampleApp::update()
{
	
	mText2->setKerning ( mKerning );
	mText2->setUnderline ( mUnderline );
	mText2->setFilling ( mFill );
	mText2->setKerning ( mKerning );
	mText2->setDebugDraw ( mDebugFonts );
}
void NVP3DTextTransformSampleApp::draw()
{
	gl::clear ( Color ( 0, 0.1f, 0.2f ) );
	gl::setViewport ( getWindowBounds() );
	gl::setMatricesWindow ( getWindowWidth(), getWindowHeight() );
	mGlobals->viewPortCached = gl::getViewport();
    mGlobals->projMatrixCached = gl::getProjection();
	
	mParams.draw();
}

CINDER_APP_BASIC ( NVP3DTextTransformSampleApp, RendererGl ( RendererGl::AA_MSAA_32 ) )