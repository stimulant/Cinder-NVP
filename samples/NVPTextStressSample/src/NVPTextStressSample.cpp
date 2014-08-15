#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "Cinder-NVP\NVPTextBoxTest.h"
#include "NVPFont.h"
#include "cinder/params/Params.h"
#include "cinder/Timeline.h"
#include "cinder/Rand.h"
#include "cinder/gl/TextureFont.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/Text.h"
#include "cinder/Utilities.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#define NUM_TEXT 15000

class NVPTextStressSampleApp : public AppBasic {
public:	
	void prepareSettings( Settings* settings );
	void setup();
	void draw();
	void update();
	int getRandNum();

	std::vector<NVPTextBoxTestRef>		mTexts;

	bool		mSetup;
	ci::params::InterfaceGl			mParams;

	Vec2f		mPos;
	float		mScale;
	float		mKerning;
	float		mStrokeWidth;
	bool		mFill;
	bool		mUnderline;
	
	bool		mDebugFonts;
	NVPFontRef	mFont;
	float mFps;

	float xWidth;
	float yWidth;
	float scalemin;
	float scalemax;
	float scalespeed;

	float mScaleVal;
};
void NVPTextStressSampleApp::prepareSettings( Settings* settings )
{
	//settings->setFullScreen( true );
	settings->setWindowPos(0,0);
	settings->setBorderless(true);
	settings->setWindowSize(1920,1080);
}
void NVPTextStressSampleApp::setup()
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
		mFont = NVPFont::create(std::string("Futura Lt BT"));

		for(int i=0; i<NUM_TEXT; i++){
			NVPTextBoxTestRef mText = NVPTextBoxTest::create();
			mText->setText(randInt(0,2) == 0 ? "0" : "1");
			mText->setFont(mFont);
			mText->setDebugDraw(false);
			mText->setFontPt(float(20));
			mTexts.push_back(mText);
		}
		
		mSetup = true;
	},timeline().getCurrentTime()+.01f);
	xWidth = 8;
	yWidth = 12;
	scalemin = 1;
	scalemax = 120;
	scalespeed = .5f;
	mPos = Vec2f(645.f,-228.f);
	mScaleVal = 3.f;

	mParams = ci::params::InterfaceGl( "Parameters", Vec2i( 250, 500 ) );
	mKerning = 1.00f;
	mParams.addParam( "fps", &mFps);
	mParams.addParam( "posx", &mPos.x );
	mParams.addParam( "posy", &mPos.y );
	mParams.addParam( "kerning", &mKerning,"min=0.0000 max=2.000 step=.0001" );
	mParams.addParam( "fill", &mFill);
	mParams.addParam( "underline", &mUnderline);
	mParams.addParam( "debug fonts", &mDebugFonts);
	mParams.addParam( "stroke width", &mStrokeWidth,"min=0.0000 max=2.000 step=.001" );
	mParams.addParam( "xwidth", &xWidth );
	mParams.addParam( "ywidth", &yWidth );
	mParams.addParam( "scale", &mScaleVal ).step(.01);
	mParams.addParam("scalespeed", &scalespeed).step(.01);
}

void NVPTextStressSampleApp::update()
{
	mFps = getFrameRate();
	if(mSetup){
		
	}
}
int NVPTextStressSampleApp::getRandNum(){
	int txt;
	int index = randInt(0,4);
	switch(index) {
		case 0:
			txt = 9;
			break;
		case 1:
			txt = 0;
			break;
		
		case 3:
			txt = 8;
			break;
		case 4:
			txt = 3;
			break;
		
	}
	return txt;
}
void NVPTextStressSampleApp::draw()
{
	gl::clear( Color( 0, 0.1f, 0.2f ) );

	if(mSetup){
		gl::setViewport( getWindowBounds() );
		gl::setMatricesWindow( getWindowWidth(), getWindowHeight() );

		gl::pushMatrices();
		int i = 0;
		int yOffset = 0;
		int xOffset = 0;
		gl::translate(mPos.x,mPos.y);
		gl::scale(mScaleVal,mScaleVal,mScaleVal);
		gl::translate(-mPos.x,-mPos.y);
		int twidth = 1920;
		char c[256];
		string txt;
		int textInd = 0;
		vector<NVPTextBoxTestRef> lastSix;
		//for(int j=0; j<6;j++){
		//		lastSix.push_back(mTexts[i-j]);
		//	}
		lastSix[0]
		for(int i=0;i < NUM_TEXT; i+=1){
			
			
			if(lastSix[0]->getLife()==0){
				if(randInt(0,10) == 0){
					int txt = getRandNum();
					
					->setText(toString(txt));
					lastSix[0]->setLife(100);
				}
			}
			
			lastSix[0]->draw(Vec2f(xOffset%twidth,floor(float(xOffset)/twidth)*yWidth));
			xOffset+=xWidth;
			yOffset+=yWidth;
		}
		
		gl::popMatrices();
		
		mParams.draw();
	}
}

CINDER_APP_BASIC( NVPTextStressSampleApp, RendererGl(RendererGl::AA_MSAA_4 ))