#include "UI/Nodes/NodeText.h"
#include "cinder/app/AppNative.h"
#include <boost/algorithm/string.hpp>
#include "cinder/Utilities.h"

using namespace ci;
using namespace ci::app;
using namespace ui::node;
using namespace std;
using namespace ui;

NodeText::NodeText( string pTxt, gl::TextureFontRef pTextRef,  ColorA pColor ) : PREMULT( false ), mJustify( LEFT )
{
    mPositionatBaseLine = false;
    mTxt = pTxt;
    mTexRef = pTextRef;
    mTxtColor = pColor;
    mLineSpacing = 0;
    // mFontSize = pTextRef->getFont().getSize();
    // createFontTex();
    int uid = getUuid();
    id = "NodeText " + ci::toString( uid );
    createFontTex();
}

void NodeText::createFontTex( )
{
    iter_split( strs, mTxt, boost::algorithm::first_finder( "\\n" ) );
    TextLayout layout;
    layout.setFont( mTexRef->getFont() );
    layout.setColor( mTxtColor );
    layout.setLeadingOffset( mLineSpacing );

    for( auto line : strs )
    {
        switch( mJustify )
        {
            case LEFT:
                layout.addLine( line );
                break;

            case RIGHT:
                layout.addRightLine( line );
                break;

            case CENTER:
                layout.addCenteredLine( line );
                break;
        }
    }

    mTex = gl::Texture( layout.render( true, PREMULT ) );
    setSize( mTex.getSize() );
}

void NodeText::setText( string pTxt )
{
    mTxt = pTxt;
    createFontTex();
}

void NodeText::setJustify( TEXT_JUSTIFY pJust )
{
    mJustify = pJust;
    createFontTex();
}

void NodeText::update( double elapsed )
{
    NodeGesture::update( elapsed );
}

void NodeText::draw()
{
    Rectf bounds = getBounds();

    // draw background
    gl::enable( GL_TEXTURE_2D );

    //calculate total alpha up the chain
    ColorA col = mTxtColor;
    col.a = mAlpha * mTreeAlpha;
    gl::color( col );
    //gl::enableAlphaBlending( PREMULT );

    if( mTex )
    {
        gl::draw( mTex, bounds );
    }

    // gl::disableAlphaBlending();
    //gl::disable( GL_TEXTURE_2D );
}
