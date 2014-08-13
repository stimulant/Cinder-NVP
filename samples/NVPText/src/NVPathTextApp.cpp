#include "cinder/app/AppBasic.h"
#include "cinder/Arcball.h"
#include "cinder/Rand.h"
#include "NVPTextBox.h"
#include "NVPFont.h"
#include "cinder/params/Params.h"
#include "cinder/Timeline.h"

#include "cinder/gl/TextureFont.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"

using namespace ci;
using namespace ci::app;

class NVPathTextApp : public AppBasic {
 public:	
	void prepareSettings( Settings* settings );
	void setup();
	void resize();
	void mouseDown( MouseEvent event );
	void mouseDrag( MouseEvent event );
	void keyDown( KeyEvent event );
	void draw();
	void update();
	
	Arcball		mArcball;
	Vec2i		mInitialMouseDown, mCurrentMouseDown;
	bool		mDrawVerbose;
	bool		mUseConstraintAxis;
	Vec3f		mConstraintAxis;

	std::vector<NVPTextBoxRef>		mTexts;
	NVPTextBoxRef		mText2;

	bool		mSetup;
	ci::params::InterfaceGl				mParams;

	Vec2f		mPos;
	float		mScale;
	float		mKerning;
	float		mStrokeWidth;
	bool		mFill;
	bool		mUnderline;
	NVPFontRef mFont;
	bool		mDebugFonts;
	NVPFontRef mFont2;
	
	std::vector<ci::gl::Texture>		mTexs;
};
void NVPathTextApp::prepareSettings( Settings* settings )
{
	//settings->setFullScreen( true );
	settings->setWindowPos(0,0);
	settings->setBorderless(true);
	settings->setWindowSize(1920,1080);
}
void NVPathTextApp::setup()
{
	mSetup = false;
	mFill = true;
	mStrokeWidth = .05f;
	mUnderline = true;
	mDebugFonts = true;
	//ci::gl::initializeGlew();
	gl::enableAlphaBlending();
	gl::enableDepthRead();
	gl::enableDepthWrite();
	mUseConstraintAxis = false;
	mCurrentMouseDown = mInitialMouseDown = Vec2i( 200, 200 );
	//hack because nvidia path rendering won't work in setup with glew not initialized?
	timeline().add( [this] {
		mFont = NVPFont::create(std::string("Arial"));
			
		for(int i=60; i>5; i-=10){
			NVPTextBoxRef mText = NVPTextBox::create();
			mText->setText("Hello Cinder!");
			mText->setFont(mFont);
			mText->setDebugDraw(false);
			mText->setFontPt(i);
			mTexts.push_back(mText);
		}
		mFont2 = NVPFont::create(std::string("Pacifico"));
		//mFont2->setIsOTF(true);
		mText2 = NVPTextBox::create();
		mText2->setText("james Bass");
		mText2->setFont(mFont2);
		mText2->setDebugDraw(true);
		mText2->setFontPt(200);
		//display Cinder textbox
		for(int i=60; i>5; i-=10){
			gl::TextureFont::Format f;
			ci::gl::TextureFontRef mFontRef = cinder::gl::TextureFont::create( Font( "Arial", i ), f );
			TextLayout layout;
			layout.setFont(mFontRef->getFont() );
			layout.setColor(Color::white() );
			layout.addLine( "Hello Cinder!" );
			mTexs.push_back(gl::Texture( layout.render(true,false) ));
		}
	

		mSetup = true;
	},timeline().getCurrentTime()+.01f);

	mPos = Vec2f(105.f,108.f);
	mScale = 1.f;
	 mParams = ci::params::InterfaceGl( "Parameters", Vec2i( 250, 500 ) );
    mKerning = 1.00f;
    mParams.addParam( "posx", &mPos.x );
	 mParams.addParam( "posy", &mPos.y );
	 mParams.addParam( "kerning", &mKerning,"min=0.0000 max=2.000 step=.0001" );
	 mParams.addParam( "fill", &mFill);
	 mParams.addParam( "underline", &mUnderline);
	  mParams.addParam( "debug fonts", &mDebugFonts);
	 mParams.addParam( "stroke width", &mStrokeWidth,"min=0.0000 max=2.000 step=.001" );
	 
	
}

void NVPathTextApp::resize()
{
	mArcball.setWindowSize( getWindowSize() );
	mArcball.setCenter( getWindowCenter() );
	mArcball.setRadius( 150 );
}

void NVPathTextApp::mouseDown( MouseEvent event )
{
	mArcball.mouseDown( event.getPos() );
	mCurrentMouseDown = mInitialMouseDown = event.getPos();
}

void NVPathTextApp::mouseDrag( MouseEvent event )
{
	mArcball.mouseDrag( event.getPos() );
	mCurrentMouseDown = event.getPos();
}

void NVPathTextApp::keyDown( KeyEvent event )
{
	if( event.getChar() == 'v' )
		mDrawVerbose = ! mDrawVerbose;
	else if( event.getChar() == 'c' ) {
		mUseConstraintAxis = ! mUseConstraintAxis;
		if( mUseConstraintAxis ) {
			// make a random constraint axis
			mConstraintAxis = Rand::randVec3f();
			mArcball.setConstraintAxis( mConstraintAxis );
		}
		else
			mArcball.setNoConstraintAxis();
	}
}
void NVPathTextApp::update()
{
	if(mSetup){
		/*mFont->setStrokeWidth(mStrokeWidth);
		mText->setUnderline(mUnderline);
		mText->setFilling(mFill);
		mText->setKerning(mKerning);
		mText->setDebugDraw(mDebugFonts);*/
		mFont2->setStrokeWidth(mStrokeWidth);
		mText2->setKerning(mKerning);
		mText2->setUnderline(mUnderline);
		mText2->setFilling(mFill);
		mText2->setKerning(mKerning);
		mText2->setDebugDraw(mDebugFonts);
	}
}
void NVPathTextApp::draw()
{
	gl::clear( Color( 0, 0.1f, 0.2f ) );

	if(mSetup){
		gl::setViewport( getWindowBounds() );
		gl::setMatricesWindow( getWindowWidth(), getWindowHeight() );
		
		gl::pushMatrices();
		float yOffset = 0;
		gl::translate(mPos);
		for(auto mText : mTexts){
			mText->draw(Vec2f(300,yOffset));
			yOffset+=60;
		}
		gl::popMatrices();
		mText2->draw(Vec2f(200,700.f));
		gl::color(Color::white());
		
		gl::translate(100,0);
		for(auto mTex : mTexs){
			if(mTex)
				gl::translate(0,60);
				gl::draw(mTex);
			
		}
		mParams.draw();
	}
	
}


CINDER_APP_BASIC( NVPathTextApp, RendererGl(RendererGl::AA_MSAA_32 ))