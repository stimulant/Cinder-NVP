#pragma once
#include "cinder/Cinder.h"
#include <string>
#include "cinder\gl\gl.h"


namespace cinder {

//! freetype 2 per glyph metrics
class GlyphMetrics;
typedef boost::shared_ptr<class GlyphMetrics>	GlyphMetricsRef;
class GlyphMetrics {
  public:

	static GlyphMetricsRef create()
	{
		return ( GlyphMetricsRef ) ( new GlyphMetrics() );
	}
	GlyphMetrics() {};
	std::vector<float> mHorizontalAdvance;
	std::vector<float> mVerticalAdvance;
	std::vector<float> mHorizontalBearingX;
	std::vector<float> mHorizontalBearingY;
	std::vector<float> mVerticalBearingX;
	std::vector<float> mVerticalBearingY;
	std::vector<float> mGlyphWidth;
	std::vector<float> mGlyphHeight;
};

//! Holds all the paths for a particular font from a ttf/otf file or as a system font
class NVPFont;
typedef boost::shared_ptr<class NVPFont>	NVPFontRef;

class NVPFont {
  public:

	//! freetype 2 per font metrics
	struct FontMetrics {
		float mXMin, mXMax, mYMin, mYMax, mEmUnits, mDescender, mAscender, mFontHeight, mMaxAdvanceWidth, mInitialOffset, mMaxAdvanceHeight, mFontHasKerning, mUnderlinePosition, mUnderlineThickness;
	};
	//! create a font from either a file or from the system fonts
	static NVPFontRef create ( std::string fontName = "Arial", bool pSystemFont = false )
	{
		return ( NVPFontRef ) ( new NVPFont ( fontName, pSystemFont ) );
	}

	NVPFont ( std::string fontName = "Arial", bool pSystemFont = false );
	~NVPFont ( );
	//! get a pointer to the first glyph of the font
	GLuint			getGlyphs() const { return mGlyphBase;}
	FontMetrics		getFontMetrics() const {return mFontMetrics;}
	GlyphMetricsRef getGlyphMetrics() const { return mGlyphMetrics;}
	float			getStrokeWidth() const {return mStrokeWidth;}
	void			setStrokeWidth ( float pWidth )
	{
		mStrokeWidth = pWidth;
		createGlyphs();
	}

  protected:
	void			createGlyphs();
	std::string		mFontName;
	GLuint			mGlyphBase;
	GLuint			mPathTemplate;
	int				numChars;
	int				mEmScale;
	FontMetrics		mFontMetrics;
	GlyphMetricsRef mGlyphMetrics;
	float			mStrokeWidth;
	bool			mSystemFont;
};

}