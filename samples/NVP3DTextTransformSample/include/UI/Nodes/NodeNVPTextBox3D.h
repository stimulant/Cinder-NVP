#pragma once

#include "cinder/Vector.h"
#include "cinder/gl/gl.h"
#include "cinder/Timeline.h"

#include "UI/Node/Node.h"
#include "NVPTextBox.h"
#include "NVPFont.h"

namespace ui {

//! For convenience, create a new type for the shared pointer and node list
typedef boost::shared_ptr<class NodeNVPTextBox3D>	NodeNVPTextBox3DRef;
typedef std::deque<NodeNVPTextBox3DRef>			NodeNVPTextBox3DList;

//! Our class extends a simple 3D node
class NodeNVPTextBox3D
	: public node::Node3D, public ci::NVPTextBox {
  public:
	static NodeNVPTextBox3DRef create ( ci::NVPFontRef pFont, std::string pTxt, bool pDebug, float pPointSize )
	{
		return ( NodeNVPTextBox3DRef ) ( new NodeNVPTextBox3D ( pFont, pTxt, pDebug, pPointSize ) );
	}

	NodeNVPTextBox3D ( ci::NVPFontRef pFont, std::string pTxt, bool pDebug, float pPointSize );
	virtual ~NodeNVPTextBox3D ( void );

	void setup();
	void update ( double elapsed = 0.0 );
	void draw();
	void render();
	void setLife ( float val ) { mLife = val; };
	ci::Anim<float> getLife() { return mLife;};
	void setTargetRot ( float init, float val ) { mInitRot = init; mTargetRot = val; };
	float getTargetRot() { return mTargetRot;};
	
	ci::Anim<float>		mLife;
  protected:
	ci::NVPTextBoxRef					mTextBox;
	float				mTargetRot;
	float				mInitRot;
};

}