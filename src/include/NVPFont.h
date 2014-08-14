#pragma once
#include "cinder/Cinder.h"
#include <string>
#include "cinder\gl\gl.h"
#include "NVPInit.h"

namespace cinder {

	class GlyphMetrics;
	typedef boost::shared_ptr<class GlyphMetrics>	GlyphMetricsRef; 
	class GlyphMetrics{

	public:
		static GlyphMetricsRef create()
		{
			return ( GlyphMetricsRef )( new GlyphMetrics() );
		}
		GlyphMetrics(){};
		std::vector<float> mHorizontalAdvance;
		std::vector<float> mVerticalAdvance;
		std::vector<float> mHorizontalBearingX;
		std::vector<float> mHorizontalBearingY;
		std::vector<float> mVerticalBearingX;
		std::vector<float> mVerticalBearingY;
		std::vector<float> mGlyphWidth;
		std::vector<float> mGlyphHeight;
	};

	class NVPFont;
	typedef boost::shared_ptr<class NVPFont>	NVPFontRef; 

	class NVPFont {

	public:
		struct FontMetrics {
			float mXMin, mXMax, mYMin, mYMax, mEmUnits, mDescender, mAscender, mFontHeight, mMaxAdvanceWidth, mInitialOffset, mMaxAdvanceHeight, mFontHasKerning, mUnderlinePosition, mUnderlineThickness;
		};

		static NVPFontRef create(std::string fontName = "Arial")
		{
			return ( NVPFontRef )( new NVPFont(fontName) );
		}

		NVPFont(std::string fontName = "Arial");
		GLuint	getGlyphs(){ return glyphBase; }
		FontMetrics getFontMetrics(){ return mFontMetrics; }
		GlyphMetricsRef getGlyphMetrics(){ return mGlyphMetrics; }
		void			setStrokeWidth(float pWidth){ mStrokeWidth = pWidth; createGlyphs(); }
		float			getStrokeWidth(){return mStrokeWidth; }
		void			setIsOTF(bool pOTF){ mIsOTF = pOTF; }
		bool			isOTF(){ return mIsOTF; }
	protected:
		void createGlyphs();
		std::string mFontName;
		GLuint glyphBase;
		GLuint pathTemplate;
		int numChars;
		int mEmScale;
		FontMetrics mFontMetrics;
		GlyphMetricsRef mGlyphMetrics;
		float	mStrokeWidth;
		bool	mIsOTF;
	};

}