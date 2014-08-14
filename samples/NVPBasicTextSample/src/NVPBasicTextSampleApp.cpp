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

using namespace ci;
using namespace ci::app;

class NVPBasicTextSampleApp : public AppBasic {
public:	
	void prepareSettings( Settings* settings );
	void setup();
	void draw();
	void update();

	std::vector<NVPTextBoxRef>		mTexts;
	NVPTextBoxRef					mText2;

	bool		mSetup;
	ci::params::InterfaceGl			mParams;

	Vec2f		mPos;
	float		mScale;
	float		mKerning;
	float		mStrokeWidth;
	bool		mFill;
	bool		mUnderline;
	
	bool		mDebugFonts;
	NVPFontRef mFont;
	NVPFontRef mFont2;

	std::vector<ci::gl::Texture>		mTexs;
};
void NVPBasicTextSampleApp::prepareSettings( Settings* settings )
{
	//settings->setFullScreen( true );
	settings->setWindowPos(0,0);
	settings->setBorderless(true);
	settings->setWindowSize(1920,1080);
}
void NVPBasicTextSampleApp::setup()
{
	initializeNVPR("");
	mSetup = false;
	mFill = true;
	mStrokeWidth = .05f;
	mUnderline = true;
	mDebugFonts = true;
	gl::enableAlphaBlending();
	gl::enableDepthRead();
	gl::enableDepthWrite();
	
	//hack because nvidia path rendering won't work in setup with glew not initialized?
	timeline().add( [this] {
		mFont = NVPFont::create(std::string("Arial"));

		for(int i=60; i>5; i-=10){
			NVPTextBoxRef mText = NVPTextBox::create();
			mText->setText("Hello Cinder!");
			mText->setFont(mFont);
			mText->setDebugDraw(false);
			mText->setFontPt(float(i));
			mTexts.push_back(mText);
		}
		mFont2 = NVPFont::create(std::string("Pacifico"));
		mText2 = NVPTextBox::create();
		mText2->setText("james Bass");
		mText2->setFont(mFont2);
		mText2->setDebugDraw(true);
		mText2->setFontPt(200);

		//display Cinder textbox
		for(int i=60; i>5; i-=10){
			gl::TextureFont::Format f;
			ci::gl::TextureFontRef mFontRef = cinder::gl::TextureFont::create( Font( "Arial", float(i) ), f );
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

void NVPBasicTextSampleApp::update()
{
	if(mSetup){
		mFont2->setStrokeWidth(mStrokeWidth);
		mText2->setKerning(mKerning);
		mText2->setUnderline(mUnderline);
		mText2->setFilling(mFill);
		mText2->setKerning(mKerning);
		mText2->setDebugDraw(mDebugFonts);
	}
}
void NVPBasicTextSampleApp::draw()
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

CINDER_APP_BASIC( NVPBasicTextSampleApp, RendererGl(RendererGl::AA_MSAA_32 ))