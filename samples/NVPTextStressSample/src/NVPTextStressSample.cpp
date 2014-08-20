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
#include "Globals.h"

#include "../include/Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#define NUM_TEXT 7000
//! this stress test app generates thousands of text fields which change value constantly and are resized to arbitrary scales
class NVPTextStressSampleApp : public AppBasic {
  public:
	void prepareSettings ( Settings* settings );
	void setup();
	void draw();
	void update();
	string getRandNum();
	void startTimeline();

	std::vector<NVPTextBoxTestRef>		mTexts;

	ci::params::InterfaceGl			mParams;

	ci::Anim<Vec2f>		mPos;
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
	float xWrap;

	ci::Anim<float> mScaleVal;
	float			mScaleParam;
	Vec3f			mPosParam;

	ci::Anim<int> mRandSpeed;

	Globals*							mGlobals;

};
void NVPTextStressSampleApp::prepareSettings ( Settings* settings )
{
	settings->setFullScreen ( true );
	settings->setWindowPos ( 0, 0 );
	settings->setBorderless ( true );
	settings->setWindowSize ( 1920, 1080 );
	//hideCursor();
}
void NVPTextStressSampleApp::setup()
{
	//initializeNVPR("");
	mGlobals = new Globals();
	mFill = true;
	mStrokeWidth = .05f;
	mUnderline = true;
	mDebugFonts = true;
	gl::enableAlphaBlending();
	gl::enableDepthRead();
	gl::enableDepthWrite();
	//load font outlines
	std::string fontPath = getAssetPath ( "Lato-Hairline.ttf" ).generic_string();
	mFont = NVPFont::create ( fontPath, false );
	fontPath = getAssetPath ( "Lato-Heavy.ttf" ).generic_string();
	mFont2 = NVPFont::create ( fontPath, false );

	//create text boxes
	for ( int i = 0; i < NUM_TEXT; i++ ) {
		NVPTextBoxTestRef mText = NVPTextBoxTest::create();
		mText->setText ( getRandNum() );
		mText->setFont ( mFont );
		mText->setDebugDraw ( false );
		mText->setFontPt ( float ( 34 ) );
		mTexts.push_back ( mText );
	}

	startTimeline();
	xWidth = 15;
	yWidth = 20;
	scalespeed = .5f;
	mPos = Vec2f ( 0.f, 303.f );
	mPosParam = Vec3f ( 0, 303.f, 0 );
	mScaleParam = 70.f;
	mScaleVal = 90.f;
	mParams = ci::params::InterfaceGl ( "Parameters", Vec2i ( 250, 500 ) );
	mKerning = 1.00f;
	mRandSpeed = 5;
	xWrap = 2190;
	mParams.addParam ( "mMaxLife", &Globals::get()->maxLife ).min ( 0 ).max ( 100 ).step ( 1 );
	mParams.addParam ( "lifeColor r", &Globals::get()->lifeColor.r ).step ( .01 );
	mParams.addParam ( "lifeColor g", &Globals::get()->lifeColor.g ).step ( .01 );
	mParams.addParam ( "lifeColor b", &Globals::get()->lifeColor.b ).step ( .01 );
	mParams.addParam ( "lifetime", &Globals::get()->maxLife ).step ( .01 );
	mParams.addParam ( "hueSpread", &Globals::get()->hueSpread ).step ( .01 );
	mParams.addParam ( "satSpread", &Globals::get()->satSpread ).step ( .01 );
	mParams.addParam ( "valSpread", &Globals::get()->valSpread ).step ( .01 );
}
void NVPTextStressSampleApp::startTimeline()
{
	timeline().apply ( &mPos, Vec2f ( 0, 0 ), 25, ci::EaseInOutQuad() );
	timeline().apply ( &mScaleVal, 1.2f, 11.f, ci::EaseInOutQuint() ).delay ( 3 );
	timeline().apply ( &mRandSpeed, 2, 8.f, ci::EaseOutQuint() ).delay ( 15 );
	timeline().appendTo ( &mRandSpeed, 8, 4.f, ci::EaseInQuad() );
	timeline().appendTo ( &mRandSpeed, 2, 8.f, ci::EaseInQuad() ).delay ( 5 );
	timeline().appendTo ( &mScaleVal, 45.f, 14.f, ci::EaseInOutQuint() ).delay ( 13 );
	timeline().appendTo ( &mPos, Vec2f ( ci::randFloat ( 300, 900 ), ci::randFloat ( 300, 700 ) ), 28, ci::EaseInOutQuad() ).finishFn ( [&] {
		startTimeline();
	} );
}
void NVPTextStressSampleApp::update()
{
}
string NVPTextStressSampleApp::getRandNum()
{
	string txt;
	int index = randInt ( 0, 4 );

	switch ( index ) {
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
	}

	return txt;
}
void NVPTextStressSampleApp::draw()
{
	gl::clear ( Color ( 0, 0.0f, 0.0f ) );
	gl::setViewport ( getWindowBounds() );
	gl::setMatricesWindow ( getWindowWidth(), getWindowHeight() );
	gl::pushMatrices();
	int i = 0;
	int yOffset = 0;
	int xOffset = 0;
	gl::translate ( mPos.value().x, mPos.value().y );
	gl::scale ( mScaleVal, mScaleVal, mScaleVal );
	gl::translate ( -mPos.value().x, -mPos.value().y );
	int twidth = floor ( xWrap / xWidth ) * xWidth;
	char c[256];
	string txt;
	int textInd = 0;

	for ( int i = 0; i < NUM_TEXT; i += 1 ) {
		NVPTextBoxTestRef tText = mTexts[i];

		if ( tText->getLife() == 0 ) {
			tText->setFont ( mFont );

			if ( tText->getProcessing() == true ) {
				if ( tText->getText() == "0" ) {
					if ( xOffset % twidth != 0 ) {
						NVPTextBoxTestRef tLast = mTexts[i - 1];

						if ( tLast->getLife() == 0 && tLast->getProcessing() == true ) {
							string tl = tLast->getText();

							if ( tl != "0" && ( tl == "9" || tl == "8" || tl == "3" ) ) {
								if ( xOffset % twidth < twidth && i != NUM_TEXT - 1 ) {
									NVPTextBoxTestRef tNext = mTexts[i + 1];

									if ( tNext->getLife() == 0 && tNext->getProcessing() == true ) {
										if ( tNext->getText() == tLast->getText() ) {
											tText->setLife ( Globals::get()->maxLife );
											tLast->setLife ( Globals::get()->maxLife );
											tNext->setLife ( Globals::get()->maxLife );
											tText->setFont ( mFont2 );
											tLast->setFont ( mFont2 );
											tNext->setFont ( mFont2 );
										}
									}
								}
							}
						}
					}
				}
			}
		}

		tText->draw ( Vec2f ( xOffset % twidth, floor ( float ( xOffset ) / twidth ) *yWidth ) );
		xOffset += xWidth;
		yOffset += yWidth;
	}

	for ( int i = 0; i < NUM_TEXT; i += 1 ) {
		NVPTextBoxTestRef tText = mTexts[i];

		if ( ci::randInt ( 0, mRandSpeed ) == 0 ) {
			tText->setProcessing ( true );

			if ( tText->getLife() == 0 )
				tText->setText ( getRandNum() );
		}
		else
			tText->setProcessing ( false );
	}

	gl::popMatrices();
	//mParams.draw();
}

CINDER_APP_BASIC ( NVPTextStressSampleApp, RendererGl ( RendererGl::AA_MSAA_16 ) )