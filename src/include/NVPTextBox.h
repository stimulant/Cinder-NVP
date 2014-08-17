#pragma once

#include "cinder/Cinder.h"

#include "cinder/Surface.h"
#include "cinder/Font.h"
#include "cinder/Vector.h"

#include <vector>
#include <deque>
#include <string>

#include "cinder\gl\gl.h"
#include "NVPFont.h"

namespace cinder {
	class NVPTextBox;
	typedef boost::shared_ptr<class NVPTextBox>	NVPTextBoxRef; 

	class NVPTextBox {


	public:
		static NVPTextBoxRef create()
		{
			return ( NVPTextBoxRef )( new NVPTextBox() );
		}
		typedef enum Alignment { LEFT, CENTER, RIGHT } Alignment;
		enum { GROW = 0 };

		NVPTextBox();

		NVPTextBox&			size( Vec2i sz ) { setSize( sz ); return *this; }
		NVPTextBox&			size( int width, int height ) { setSize( Vec2i( width, height ) ); return *this; }
		Vec2i				getSize() const { return mSize; }
		void				setSize( Vec2i sz ) { mSize = sz; mInvalid = true; }

		NVPTextBox&		text( const std::string &t ) { setText( t ); return *this; }
		const std::string&	getText() const { return mText; }
		virtual void				setText( const std::string &t ) { mText = t; mInvalid = true; }
		void				appendText( const std::string &t ) { mText += t; mInvalid = true; }


		NVPTextBox&		alignment( Alignment align ) { setAlignment( align ); return *this; }
		Alignment			getAlignment() const { return mAlign; }
		void				setAlignment( Alignment align ) { mAlign = align; mInvalid = true; }

		void				draw( Vec2f offset = Vec2f::zero() );
		void				render();
		ColorA				getFillColor(){ return mFillColor; }
		void				setFillColor(ColorA pCol){ mFillColor = pCol; }
		ColorA				getStrokeColor(){ return mStrokeColor; }
		void				setStrokeColor(ColorA pCol){ mStrokeColor = pCol; }
		void				setKerning(float pKern){ mKerningFactor = pKern; mInvalid = true;}
		float				getKerning(){ return mKerningFactor; }
		void				setFilling(bool pFill){ mFilling = pFill; }
		void				setUnderline(bool pUnder){ mUnderline = pUnder; }

		void				setFont(const NVPFontRef &pFont){ mFont = pFont; mInvalid = true;}
		void				setFontPt(float pSize){ mFontPt = pSize;}
		float				getFontPt(){ return mFontPt; }
		virtual void				setDebugDraw(bool pDraw){ mDebugDraw = pDraw; }
		float mScaleVal;
	protected:
		Alignment		mAlign;
		Vec2i			mSize;
		std::string		mText;
		ColorA			mFillColor, mStrokeColor, mBackgroundColor;
		float			mKerningFactor;

		int				mFilling;
		int				mUnderline;

		bool			mPremultiplied;
		bool			mLigate;
		mutable bool	mInvalid;

		mutable Vec2f	mCalculatedSize;

		size_t mMessageLen;
		GLfloat *xtranslate;

		uint32_t mPathDefMode;


		GLfloat mTotalAdvance, mXBorder;
		/* Global variables */

		GLuint mPathObj;
		GLint sRGB_capable;
		int hasFramebufferSRGB;

		int mRegularAspect;
		int mFillGradient;
		int emScale;

		GLuint mPathTemplate;

		NVPFontRef	mFont;

		bool	mDrawBoundingBox;
		bool	mDrawGlyphBounds;

		float mFontPt;
		bool	mDebugDraw;

		float mInitialOffset;

	};

}