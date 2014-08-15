#pragma once

#include "NVPTextBox.h"

namespace cinder {

class NVPTextBoxTest;
typedef boost::shared_ptr<class NVPTextBoxTest>	NVPTextBoxTestRef; 

class NVPTextBoxTest : public NVPTextBox {

public:
	static NVPTextBoxTestRef create()
	{
		return ( NVPTextBoxTestRef )( new NVPTextBoxTest() );
	}
	NVPTextBoxTest::NVPTextBoxTest();
	int		getLife(){ return mLife; }
	void	setLife(float pLife){ mLife = pLife; }
	bool	getProcessing(){ return mProcessing; }
	void	setProcessing(bool pProc){ mProcessing = pProc; }
	void	NVPTextBoxTest::draw( Vec2f offset );
private:
	int mLife;
	Color mMixedColor;
	bool mProcessing;
};
}