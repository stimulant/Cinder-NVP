#pragma once

#include "Cinder-NVP\NVPTextBoxTest.h"
#include "cinder/app/App.h"
using namespace std;
using namespace cinder;
using namespace app;

namespace cinder {

static const float DPI = 72.f;
// : mAlign( LEFT ), mSize( GROW, GROW ), mInvalid( true ),mDebugDraw(false),mUnderline(false), mFontPt(12),sRGB_capable(0),hasFramebufferSRGB(1),emScale(2048),mFilling(1),mRegularAspect(1),mFillGradient(1),mFillColor( 1, 1, 1, 1 ),mStrokeColor( 0.f, 0.f, 0.f, 1 ), mKerningFactor(1.f), mDrawBoundingBox(false),mDrawGlyphBounds(false),mBackgroundColor( 0, 0, 0, 0 ), mPremultiplied( false ), mLigate( true )
NVPTextBoxTest::NVPTextBoxTest() : mLife(0) {
	NVPTextBox::NVPTextBox();
}
void	NVPTextBoxTest::draw( Vec2f offset )
{
	if(mInvalid)
		render();

	if(mFont){
		float pixelSize = mFontPt;
		float resolution = DPI;
		float fScale = mFontPt * resolution / ( DPI * emScale);
		//not sure why this scale is needed to match point size?
		float fscal = fScale *.75f;

		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_NOTEQUAL, 0, ~0);
		glStencilOp(GL_KEEP, GL_KEEP, GL_ZERO);

		// glClearStencil(0);
		//glClearColor(0,0,0,0);
		//glClearColor(0.2f,0.2f,0.8f,0);
		glStencilMask(0xFFFFFFFF);
		gl::pushMatrices();
		gl::translate(offset);
		gl::scale(fscal,-fscal,fscal);

		NVPFont::FontMetrics metrics = mFont->getFontMetrics();
		if (mUnderline) {
			/* Draw an underline with conventional OpenGL rendering. */
			float	position = metrics.mUnderlinePosition,
				half_thickness = metrics.mUnderlineThickness/2;
			glDisable(GL_STENCIL_TEST);
			

			glBegin(GL_QUAD_STRIP); {
				glVertex2f(0, position+half_thickness);
				glVertex2f(0, position-half_thickness);
				glVertex2f(mTotalAdvance, position+half_thickness);
				glVertex2f(mTotalAdvance, position-half_thickness);
			} glEnd();

			glEnable(GL_STENCIL_TEST);
		}

		gl::translate(-mInitialOffset,0.f);	
		if (mFont->getStrokeWidth()>0.f) {

			/* Add stroking "behind" the filled characters. */
			glStencilStrokePathInstancedNV((GLsizei)mMessageLen,
				GL_UNSIGNED_BYTE, mText.c_str(), mFont->getGlyphs(),
				1, ~0,  /* Use all stencil bits */
				GL_TRANSLATE_X_NV, xtranslate);

			gl::color(mStrokeColor);
			glCoverStrokePathInstancedNV((GLsizei)mMessageLen,
				GL_UNSIGNED_BYTE, mText.c_str(), mFont->getGlyphs(),
				GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV,
				GL_TRANSLATE_X_NV, xtranslate);
		}
		
		if (mFilling) {
			/* STEP 1: stencil message into stencil buffer.  Results in samples
			within the message's glyphs to have a non-zero stencil value. */
			glStencilFillPathInstancedNV((GLsizei)mMessageLen,
				GL_UNSIGNED_BYTE, mText.c_str(), mFont->getGlyphs(),
				GL_PATH_FILL_MODE_NV, ~0,  /* Use all stencil bits */
				GL_TRANSLATE_X_NV, xtranslate);

			Color fill = Color(mFillColor.r,mFillColor.g,mFillColor.b)*(mLife/10.f);
			
			if(mLife>0){
				mLife-=1;
				//console()<<"mLife "<<mLife<< endl;
			}
			gl::color(fill);

			glCoverFillPathInstancedNV((GLsizei)mMessageLen,
				GL_UNSIGNED_BYTE, mText.c_str(), mFont->getGlyphs(),
				GL_BOUNDING_BOX_OF_BOUNDING_BOXES_NV,
				GL_TRANSLATE_X_NV, xtranslate);
		}
	
		gl::popMatrices();
		glDisable(GL_STENCIL_TEST);
	}
}

}