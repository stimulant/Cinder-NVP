
#include "UI/Nodes/NodeNVPTextBox3D.h"

#include "cinder/app/AppBasic.h"
#include "cinder/Utilities.h"

using namespace ci;
using namespace ci::app;
using namespace ui::node;
using namespace ui;

using namespace std;

NodeNVPTextBox3D::NodeNVPTextBox3D ( NVPFontRef pFont, string pTxt, bool pDebug, float pPointSize )
{
	NVPTextBox::NVPTextBox();
	mFont = pFont;
	mText = pTxt;
	mDebugDraw = pDebug;
	mFontPt = pPointSize;
	render();
}

NodeNVPTextBox3D::~NodeNVPTextBox3D ( void )
{
}

void NodeNVPTextBox3D::setup()
{
	Node3D::setup();
}

void NodeNVPTextBox3D::update ( double elapsed )
{
	Node3D::update(elapsed);
}
void NodeNVPTextBox3D::render()
{
	NVPTextBox::render();
	float pixelSize = mFontPt;
	float resolution = NVPTextBox::DPI;
	float fScale = mFontPt * resolution / ( DPI * emScale );
	//not sure why this scale is needed to match point size?
	float fscal = fScale * .75f;
	setScale(fscal);
}
void NodeNVPTextBox3D::draw()
{
	if ( mInvalid )
		render();

	gl::translate ( getAnchor() );
	gl::color ( Color ( 1, 0, 0 ) );
	gl::drawCoordinateFrame ( .1, .01, .01 );
	gl::translate ( -getAnchor() );

	if ( mFont ) {
		glEnable ( GL_STENCIL_TEST );
		glStencilFunc ( GL_NOTEQUAL, 0, ~0 );
		glStencilOp ( GL_KEEP, GL_KEEP, GL_ZERO );
		glStencilMask ( 0xFFFFFFFF );
		gl::pushMatrices();
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
		gl::drawStrokedRect(mBounds);
	}
}
