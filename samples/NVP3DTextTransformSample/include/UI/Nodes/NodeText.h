#pragma once

#include "cinder/gl/gl.h"

namespace ui
{

    typedef boost::shared_ptr<class NodeText>	NodeTextRef;
    typedef std::deque<NodeTextRef>			NodeTextList;

    class NodeText
        : public ui::Node2D
    {
        public:
            NodeText( std::string pTxt, ci::gl::TextureFontRef pTextRef, ci::ColorA pColor );
            static NodeTextRef create( std::string pTxt, ci::gl::TextureFontRef pTextRef, ci::ColorA pColor )
            {
                return ( NodeTextRef )( new NodeText( pTxt, pTextRef, pColor ) );
            }
            void update( double elapsed = 0.0 );
            void draw();
            void setText( std::string pTxt );
            std::string getText( )
            {
                return mTxt;
            }
            void setLineSpacing( float pSpace )
            {
                mLineSpacing = pSpace;
				createFontTex();
            }
            void setJustify( TEXT_JUSTIFY pJust );
            TEXT_JUSTIFY getJustify( )
            {
                return mJustify;
            }
            void setColor( ci::ColorA pCol )
            {
                if( mTxtColor != pCol )
                {
                    mTxtColor = pCol;
                    createFontTex();
                }

            }
            void setPositionAtBaseLine( bool pVal )
            {
                mPositionatBaseLine = pVal;
            }
            void setFont( ci::gl::TextureFontRef pFontRef )
            {
                mTexRef = pFontRef;
                createFontTex();
            }

            bool                PREMULT;
        protected:
            ci::gl::TextureFontRef mTexRef;
            std::map<ci::gl::TextureFontRef, std::string>	mTexStringMap;
            std::string			mTxt;
            int					txtSize;
            ci::ColorA			mTxtColor;
            void				createFontTex();
            float				mLineSpacing;
            float				mFontSize;
            std::vector<std::string> strs;
            bool				mPositionatBaseLine;
            TEXT_JUSTIFY		mJustify;
            ci::gl::Texture		mTex;
    };

}