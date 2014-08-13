#pragma once

#include "NVPFont.h"
#include "cinder/app/App.h"
using namespace std;

namespace cinder {


	NVPFont::NVPFont(std::string fontName):numChars(256),mStrokeWidth(0.0f),mEmScale(2048),mIsOTF(false){
		mFontName = fontName;
		glyphBase = 0;
		createGlyphs();
	}
	void NVPFont::createGlyphs(){
		if(glyphBase!=0)
			glDeletePathsNV(glyphBase, numChars);
		glyphBase = 0;
		pathTemplate = 0;
		/* Create a range of path objects corresponding to Latin-1 character codes. */
		glyphBase = glGenPathsNV(numChars);
		/* Use the path object at the end of the range as a template. */
		pathTemplate = glyphBase+numChars;
		//set stroke width of path as percentage of emscale
		glPathCommandsNV(pathTemplate, 0, NULL, 0, GL_FLOAT, NULL);
		glPathParameteriNV(pathTemplate, GL_PATH_STROKE_WIDTH_NV, GLint(mStrokeWidth * mEmScale));
		glPathParameteriNV(pathTemplate, GL_PATH_JOIN_STYLE_NV, GL_ROUND_NV);

		//attempt to load glyphs from mFontname system font. If mFontName can't be found then load Arial. if Arial can't be found
		//then load the default sans system font
		glPathGlyphRangeNV(glyphBase, GL_SYSTEM_FONT_NAME_NV, mFontName.c_str(), GL_NONE,
			0, numChars,
			GL_SKIP_MISSING_GLYPH_NV, pathTemplate, GLfloat(mEmScale));
		glPathGlyphRangeNV(glyphBase, GL_SYSTEM_FONT_NAME_NV,"Arial", GL_NONE,
			0, numChars,
			GL_SKIP_MISSING_GLYPH_NV, pathTemplate, GLfloat(mEmScale));
		glPathGlyphRangeNV(glyphBase, GL_STANDARD_FONT_NAME_NV,"Sans", GL_NONE,
			0, numChars,GL_USE_MISSING_GLYPH_NV, pathTemplate, GLfloat(mEmScale));

		float font_data[4];
		glGetPathMetricRangeNV(GL_FONT_Y_MIN_BOUNDS_BIT_NV|GL_FONT_Y_MAX_BOUNDS_BIT_NV|
			GL_FONT_UNDERLINE_POSITION_BIT_NV|GL_FONT_UNDERLINE_THICKNESS_BIT_NV,
			glyphBase+' ', /*count*/1,
			4*sizeof(GLfloat),
			font_data);
		mFontMetrics.mYMin = font_data[0];
		mFontMetrics.mYMax = font_data[1];
		mFontMetrics.mUnderlinePosition = font_data[2];
		mFontMetrics.mUnderlineThickness = font_data[3];

		glGetPathMetricRangeNV(GL_FONT_X_MIN_BOUNDS_BIT_NV|GL_FONT_X_MAX_BOUNDS_BIT_NV|
			GL_FONT_UNITS_PER_EM_BIT_NV|GL_FONT_ASCENDER_BIT_NV,
			glyphBase+' ', /*count*/1,
			4*sizeof(GLfloat),
			font_data);
		mFontMetrics.mXMin = font_data[0];
		mFontMetrics.mXMax = font_data[1];
		mFontMetrics.mEmUnits = font_data[2];
		mFontMetrics.mAscender = font_data[3];

		glGetPathMetricRangeNV(GL_FONT_DESCENDER_BIT_NV|GL_FONT_HEIGHT_BIT_NV|GL_FONT_MAX_ADVANCE_WIDTH_BIT_NV|GL_FONT_MAX_ADVANCE_HEIGHT_BIT_NV,
			glyphBase+' ', /*count*/1,
			4*sizeof(GLfloat),
			font_data);
		mFontMetrics.mDescender = font_data[0];
		mFontMetrics.mFontHeight = font_data[1];
		mFontMetrics.mMaxAdvanceWidth = font_data[2];
		mFontMetrics.mMaxAdvanceHeight = font_data[3];
		GLfloat glyphMetrics[256];
		mGlyphMetrics = GlyphMetrics::create();
		//collect glyph metrics
		glGetPathMetricRangeNV(GL_GLYPH_HORIZONTAL_BEARING_ADVANCE_BIT_NV,
			glyphBase, numChars,
			0, /* stride of zero means sizeof(GLfloat) since 1 bit in mask */
			glyphMetrics);
		mGlyphMetrics->mHorizontalAdvance = std::vector<float> (glyphMetrics, glyphMetrics + sizeof glyphMetrics / sizeof glyphMetrics[0]);

		glGetPathMetricRangeNV(GL_GLYPH_VERTICAL_BEARING_ADVANCE_BIT_NV,
			glyphBase, numChars,
			0, /* stride of zero means sizeof(GLfloat) since 1 bit in mask */
			glyphMetrics);
		mGlyphMetrics->mVerticalAdvance = std::vector<float> (glyphMetrics, glyphMetrics + sizeof glyphMetrics / sizeof glyphMetrics[0]);

		glGetPathMetricRangeNV(GL_GLYPH_WIDTH_BIT_NV,
			glyphBase, numChars,
			0, /* stride of zero means sizeof(GLfloat) since 1 bit in mask */
			glyphMetrics);
		mGlyphMetrics->mGlyphWidth = std::vector<float> (glyphMetrics, glyphMetrics + sizeof glyphMetrics / sizeof glyphMetrics[0]);

		glGetPathMetricRangeNV(GL_GLYPH_HEIGHT_BIT_NV,
			glyphBase, numChars,
			0, /* stride of zero means sizeof(GLfloat) since 1 bit in mask */
			glyphMetrics);
		mGlyphMetrics->mGlyphHeight = std::vector<float> (glyphMetrics, glyphMetrics + sizeof glyphMetrics / sizeof glyphMetrics[0]);

		glGetPathMetricRangeNV(GL_GLYPH_HORIZONTAL_BEARING_X_BIT_NV,
			glyphBase, numChars,
			0, /* stride of zero means sizeof(GLfloat) since 1 bit in mask */
			glyphMetrics);
		mGlyphMetrics->mHorizontalBearingX = std::vector<float> (glyphMetrics, glyphMetrics + sizeof glyphMetrics / sizeof glyphMetrics[0]);

		glGetPathMetricRangeNV(GL_GLYPH_HORIZONTAL_BEARING_Y_BIT_NV,
			glyphBase, numChars,
			0, /* stride of zero means sizeof(GLfloat) since 1 bit in mask */
			glyphMetrics);
		mGlyphMetrics->mHorizontalBearingY = std::vector<float> (glyphMetrics, glyphMetrics + sizeof glyphMetrics / sizeof glyphMetrics[0]);

		glGetPathMetricRangeNV(GL_GLYPH_VERTICAL_BEARING_X_BIT_NV,
			glyphBase, numChars,
			0, /* stride of zero means sizeof(GLfloat) since 1 bit in mask */
			glyphMetrics);
		mGlyphMetrics->mVerticalBearingX = std::vector<float> (glyphMetrics, glyphMetrics + sizeof glyphMetrics / sizeof glyphMetrics[0]);

		glGetPathMetricRangeNV(GL_GLYPH_VERTICAL_BEARING_Y_BIT_NV,
			glyphBase, numChars,
			0, /* stride of zero means sizeof(GLfloat) since 1 bit in mask */
			glyphMetrics);
		mGlyphMetrics->mVerticalBearingY = std::vector<float> (glyphMetrics, glyphMetrics + sizeof glyphMetrics / sizeof glyphMetrics[0]);
	}
}