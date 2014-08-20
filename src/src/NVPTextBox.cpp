#pragma once

#include "NVPTextBox.h"
#include "cinder\gl\gl.h"
#include "cinder/app/App.h"

using namespace std;
using namespace cinder;

namespace cinder {

static const float DPI = 72.f;

NVPTextBox::NVPTextBox() : mInvalid ( true ), mDebugDraw ( false ), mUnderline ( false ), mFontPt ( 12 ), sRGB_capable ( 0 ), hasFramebufferSRGB ( 1 ), emScale ( 2048 ), mFilling ( 1 ), mRegularAspect ( 1 ), mFillGradient ( 1 ), mFillColor ( 1, 1, 1, 1 ), mStrokeColor ( 0.f, 0.f, 0.f, 1 ), mKerningFactor ( 1.f ), mDrawBoundingBox ( false ), mDrawGlyphBounds ( false )
{
	if ( hasFramebufferSRGB ) {
		glGetIntegerv ( GL_FRAMEBUFFER_SRGB_CAPABLE_EXT, &sRGB_capable );

		if ( sRGB_capable ) {
			glEnable ( GL_FRAMEBUFFER_SRGB_EXT );
		}
	}

	//nvidia path specific depth testing params
	GLfloat slope = -0.05f;
	GLfloat bias = -1.0f;
	glPathStencilDepthOffsetNV ( slope, bias );
	glPathCoverDepthFuncNV ( GL_ALWAYS );
	xtranslate = NULL;
}
void NVPTextBox::render()
{
	/* Query spacing information for example's message. */
	mMessageLen = strlen ( mText.c_str() );

	if ( xtranslate != NULL ) {
		free ( xtranslate );
		xtranslate = NULL;
	}

	xtranslate = ( GLfloat* ) malloc ( sizeof ( GLfloat ) * mMessageLen );

	if ( !xtranslate ) {
		ci::app::console() << " malloc of xtranslate failed" << endl;
		exit ( 1 );
	}

	xtranslate[0] = 0.0;  /* Initial xtranslate is zero. */
	GLfloat advanceScale = 1.0f * mKerningFactor,
	        kerningScale = 1.0f * mKerningFactor; /* Set this to zero to ignore kerning. */
	glGetPathSpacingNV ( GL_ACCUM_ADJACENT_PAIRS_NV,
	                     ( GLsizei ) mMessageLen, GL_UNSIGNED_BYTE, mText.c_str(),
	                     mFont->getGlyphs(),
	                     advanceScale, kerningScale,
	                     GL_TRANSLATE_X_NV,
	                     &xtranslate[1] ); /* messageLen-1 accumulated translates are written here. */
	/* Total advance is accumulated spacing plus horizontal advance of
	the last glyph */
	float lastX = xtranslate[mMessageLen - 1];
	const unsigned char* message_ub = ( const unsigned char* ) mText.c_str();
	int charIndex = message_ub[mMessageLen - 1];
	float totalLen = mFont->getGlyphMetrics()->mHorizontalAdvance[charIndex];
	mTotalAdvance = lastX + totalLen;
	mXBorder = mTotalAdvance / mMessageLen;
	mInitialOffset = mFont->getGlyphMetrics()->mHorizontalBearingX[mText.c_str() [0]];
	mInvalid = false;
}
void	NVPTextBox::draw ( Vec2f offset )
{
	if ( mInvalid )
		render();

	if ( mFont ) {
		float pixelSize = mFontPt;
		float resolution = DPI;
		float fScale = mFontPt * resolution / ( DPI * emScale );
		//not sure why this scale is needed to match point size?
		float fscal = fScale * .75f;
		glEnable ( GL_STENCIL_TEST );
		glStencilFunc ( GL_NOTEQUAL, 0, ~0 );
		glStencilOp ( GL_KEEP, GL_KEEP, GL_ZERO );
		glStencilMask ( 0xFFFFFFFF );
		gl::pushMatrices();
		gl::translate ( offset );
		gl::scale ( fscal, -fscal, fscal );
		NVPFont::FontMetrics metrics = mFont->getFontMetrics();

		if ( mUnderline ) {
			/* Draw an underline with conventional OpenGL rendering. */
			float	position = metrics.mUnderlinePosition,
			        half_thickness = metrics.mUnderlineThickness / 2;
			glDisable ( GL_STENCIL_TEST );
			gl::color ( mFillColor );
			glBegin ( GL_QUAD_STRIP ); {
				glVertex2f ( 0, position + half_thickness );
				glVertex2f ( 0, position - half_thickness );
				glVertex2f ( mTotalAdvance, position + half_thickness );
				glVertex2f ( mTotalAdvance, position - half_thickness );
			} glEnd();
			glEnable ( GL_STENCIL_TEST );
		}

		gl::translate ( -mInitialOffset, 0.f );

		if ( mFont->getStrokeWidth() > 0.f ) {
			/* Add stroking "behind" the filled characters. */
			glStencilStrokePathInstancedNV ( ( GLsizei ) mMessageLen,
			                                 GL_UNSIGNED_BYTE, mText.c_str(), mFont->getGlyphs(),
			                                 1, ~0,  /* Use all stencil bits */
			                                 GL_TRANSLATE_X_NV, xtranslate );
			gl::color ( mStrokeColor );
			glCoverStrokePathInstancedNV ( ( GLsizei ) mMessageLen,
			                               GL_UNSIGNED_BYTE, mText.c_str(), mFont->getGlyphs(),
			                               GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV,
			                               GL_TRANSLATE_X_NV, xtranslate );
		}

		if ( mFilling ) {
			/* STEP 1: stencil message into stencil buffer.  Results in samples
			within the message's glyphs to have a non-zero stencil value. */
			glStencilFillPathInstancedNV ( ( GLsizei ) mMessageLen,
			                               GL_UNSIGNED_BYTE, mText.c_str(), mFont->getGlyphs(),
			                               GL_PATH_FILL_MODE_NV, ~0,  /* Use all stencil bits */
			                               GL_TRANSLATE_X_NV, xtranslate );
			gl::color ( mFillColor );
			glCoverFillPathInstancedNV ( ( GLsizei ) mMessageLen,
			                             GL_UNSIGNED_BYTE, mText.c_str(), mFont->getGlyphs(),
			                             GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV,
			                             GL_TRANSLATE_X_NV, xtranslate );
		}

		gl::translate ( mInitialOffset, 0.f );

		if ( mDebugDraw ) {
			gl::translate ( -mInitialOffset, 0.f );
			glDisable ( GL_STENCIL_TEST );

			for ( int i = 0; i < int ( mMessageLen ); i++ ) {
				int charInd = mText.c_str() [i];
				float glyphWidth = mFont->getGlyphMetrics()->mGlyphWidth[charInd];
				float glyphHeight = mFont->getGlyphMetrics()->mGlyphHeight[charInd];
				float horizontalBearingX = mFont->getGlyphMetrics()->mHorizontalBearingX[charInd];
				float horizontalBearingY = mFont->getGlyphMetrics()->mHorizontalBearingY[charInd];
				float verticalBearingX = mFont->getGlyphMetrics()->mVerticalBearingX[charInd];
				float verticalBearingY = mFont->getGlyphMetrics()->mVerticalBearingY[charInd];
				float nextXBearing = mFont->getGlyphMetrics()->mHorizontalBearingX[mText.c_str() [i + 1]];
				float lastXBearing;

				if ( i > 0 )
					lastXBearing = mFont->getGlyphMetrics()->mHorizontalBearingX[mText.c_str() [i - 1]];

				float startX = xtranslate[i];
				//draw glyph bounds
				gl::color ( Color ( 0.f, 1.f, 0.f ) );
				gl::drawStrokedRect ( Rectf ( startX + horizontalBearingX, horizontalBearingY - glyphHeight, startX + horizontalBearingX + glyphWidth, horizontalBearingY ) );
			}

			gl::translate ( mInitialOffset, 0.f );
			gl::color ( Color ( 0.f, 0.f, 1.f ) );
			gl::drawStrokedRect ( Rectf ( 0, metrics.mDescender, mTotalAdvance, metrics.mAscender + metrics.mDescender ) );
			gl::color ( Color ( 1.f, 0.f, 0.f ) );
			gl::drawSolidCircle ( Vec2f ( 0.f, 0.f ), 100 );
			glEnable ( GL_STENCIL_TEST );
		}

		gl::popMatrices();
		glDisable ( GL_STENCIL_TEST );
	}
}


} // namespace cinder