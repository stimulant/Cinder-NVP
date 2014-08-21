#pragma once

#include "cinder/Vector.h"
#include "cinder/gl/gl.h"

#include "UI/Node/Node.h"
#include "NVPTextBox.h"
#include "NVPFont.h"

namespace ui {

//! For convenience, create a new type for the shared pointer and node list
typedef boost::shared_ptr<class NodeText3D>	NodeText3DRef;
typedef std::deque<NodeText3DRef>			NodeText3DList;

//! Our class extends a simple 3D node
class NodeText3D
	: public node::Node3D {
  public:
	static NodeText3DRef create ( ci::NVPFontRef pFont, std::string pTxt, bool pDebug, float pPointSize )
	{
		return ( NodeText3DRef ) ( new NodeText3D ( pFont, pTxt, pDebug, pPointSize ) );
	}

	NodeText3D ( ci::NVPFontRef pFont, std::string pTxt, bool pDebug, float pPointSize );
	virtual ~NodeText3D ( void );

	void setup();
	void update ( double elapsed = 0.0 );
	void draw();

  protected:
	ci::NVPTextBoxRef					mTextBox;
};

}