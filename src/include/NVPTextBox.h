#pragma once

#include "cinder/Cinder.h"
#include "cinder/Surface.h"
#include "cinder/Font.h"
#include "cinder/Vector.h"
#include "cinder/gl/gl.h"

#include <vector>
#include <deque>
#include <string>

#include "NVPFont.h"

namespace cinder {

//! Resolution independent textbox drawn using Nvidia Path Rendering SDK
class NVPTextBox;
typedef boost::shared_ptr<class NVPTextBox>	NVPTextBoxRef;

class NVPTextBox {
  public:

	static NVPTextBoxRef create()
	{
		return ( NVPTextBoxRef ) ( new NVPTextBox() );
	}

	NVPTextBox();

	NVPTextBox					&text ( const std::string &t ) { setText ( t ); return *this; }
	const std::string			&getText() const { return mText; }
	virtual void				setText ( const std::string &t ) { mText = t; mInvalid = true; }
	void						appendText ( const std::string &t ) { mText += t; mInvalid = true; }

	void						draw ( Vec2f offset = Vec2f::zero() );
	void						render();
	ColorA						getFillColor() const { return mFillColor; }
	void						setFillColor ( ColorA pCol ) { mFillColor = pCol; }
	ColorA						getStrokeColor() const { return mStrokeColor; }
	void						setStrokeColor ( ColorA pCol ) { mStrokeColor = pCol; }
	//! Kerning is expressed as a factor of the glyph set's default spacing. 1.0 = no change from default
	void						setKerning ( float pKern ) { mKerningFactor = pKern; mInvalid = true;}
	float						getKerning() const { return mKerningFactor; }
	void						setFilling ( bool pFill ) { mFilling = pFill; }
	void						setUnderline ( bool pUnder ) { mUnderline = pUnder; }

	void						setFont ( const NVPFontRef &pFont ) { mFont = pFont; mInvalid = true;}
	void						setFontPt ( float pSize ) { mFontPt = pSize;}
	float						getFontPt() const { return mFontPt; }
	//! draws the bounding boxes of each glyph and the bounds of the font's ascender and descender range
	virtual void				setDebugDraw ( bool pDraw ) { mDebugDraw = pDraw; }

  protected:
	std::string		mText;
	ColorA			mFillColor, mStrokeColor;
	float			mKerningFactor;

	int				mFilling;
	int				mUnderline;

	mutable bool	mInvalid;

	size_t			mMessageLen;
	GLfloat*		xtranslate;
	uint32_t		mPathDefMode;
	GLfloat			mTotalAdvance, mXBorder;
	GLuint			mPathObj;
	GLint			sRGB_capable;
	int				hasFramebufferSRGB;

	int				mRegularAspect;
	int				mFillGradient;
	int				emScale;

	GLuint			mPathTemplate;

	NVPFontRef		mFont;

	bool			mDrawBoundingBox;
	bool			mDrawGlyphBounds;

	float			mFontPt;
	bool			mDebugDraw;
	//horizontal offset between the x position and the first glyph
	float			mInitialOffset;

};

}
