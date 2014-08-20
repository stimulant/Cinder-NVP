#include "Globals.h"

using namespace ci;

// singleton instance
Globals* Globals::sInstance = NULL;
Globals* Globals::get()
{
	return sInstance;
}

Globals::Globals( )
{
	sInstance = this;
	hueSpread = 2.28;
	satSpread = .68;
	valSpread = .73;
	lifeColor = Color ( CM_HSV, .43, .41, .25 );
	maxLife = 20;
}

Globals::~Globals()
{
}

