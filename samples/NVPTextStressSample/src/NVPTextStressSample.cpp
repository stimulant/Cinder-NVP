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

#define NUM_TEXT 25000

class NVPTextStressSampleApp : public AppBasic {
public:	
	void prepareSettings( Settings* settings );
	void setup();
	void draw();
	void update();
	string getRandNum();

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
	NVPFontRef	mFont2;
	float mFps;

	float xWidth;
	float yWidth;
	float scalemin;
	float scalemax;
	float scalespeed;

	float mScaleVal;

	int mMaxLife;
	int mRandSpeed;
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
		mFont = NVPFont::create(std::string("Lato Hairline"));
		mFont2 = NVPFont::create(std::string("Lato Medium"));
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
	scalespeed = .5f;
	mPos = Vec2f(643,78.f);
	mScaleVal = 15.1f;
	mMaxLife = 70;
	mParams = ci::params::InterfaceGl( "Parameters", Vec2i( 250, 500 ) );
	mKerning = 1.00f;
	mRandSpeed = 8;
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
	mParams.addParam( "mMaxLife", &mMaxLife).min(0).max(100).step(1);
	mParams.addParam( "mRandSpeed", &mRandSpeed );
	mParams.addParam( "scale", &mScaleVal ).step(.1);
	mParams.addParam("scalespeed", &scalespeed).step(.01);
}

void NVPTextStressSampleApp::update()
{
	mFps = getFrameRate();
	if(mSetup){
		
	}
}
string NVPTextStressSampleApp::getRandNum(){
	string txt;
	int index = randInt(0,4);
	
	switch(index) {
		case 0:
			txt = "9";
			break;
		case 1:
			txt = "0";
			break;
		case 2:
			txt = "8";
			break;
		case 3:
			txt = "3";
			break;
		case 4:
			txt = "$";
			break;
		
		case 5:
			txt = "#";
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
		
		
		
		for(int i=0;i < NUM_TEXT; i+=1){
			NVPTextBoxTestRef tText = mTexts[i];
			
			if(tText->getLife()==0){
				tText->setFont(mFont);
				if(tText->getProcessing()==true){
					if(tText->getText()=="0"){
						if(xOffset%twidth!=0){
							NVPTextBoxTestRef tLast = mTexts[i-1];
							if(tLast->getLife()==0 && tLast->getProcessing()==true){
								string tl = tLast->getText();
								if(tl!="0" && (tl == "9" || tl == "8" || tl == "3")){
									if(xOffset%twidth<twidth && i!=NUM_TEXT-1){
										NVPTextBoxTestRef tNext = mTexts[i+1];
										if(tNext->getLife()==0 && tNext->getProcessing()==true){
											if(tNext->getText()==tLast->getText()){
												tText->setLife(mMaxLife);
												tLast->setLife(mMaxLife);
												tNext->setLife(mMaxLife);
												tText->setFont(mFont2);
												tLast->setFont(mFont2);
												tNext->setFont(mFont2);
											}
										}
									}
								}
							}
						}
					}
				}
			}
			
			tText->draw(Vec2f(xOffset%twidth,floor(float(xOffset)/twidth)*yWidth));
			xOffset+=xWidth;
			yOffset+=yWidth;
		}
		for(int i=0;i < NUM_TEXT; i+=1){
			NVPTextBoxTestRef tText = mTexts[i];
			if(ci::randInt(0,mRandSpeed)==0){
				
				tText->setProcessing(true);
				if(tText->getLife()==0)
					tText->setText(getRandNum());
			}
			else 
				tText->setProcessing(false);
		}
		gl::popMatrices();
		
		mParams.draw();
	}
}

CINDER_APP_BASIC( NVPTextStressSampleApp, RendererGl(RendererGl::AA_MSAA_4 ))