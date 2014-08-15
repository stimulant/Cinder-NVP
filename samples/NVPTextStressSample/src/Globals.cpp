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
	hueSpread = .6;
	satSpread = .84;
	valSpread = .34;
	lifeColor = Color(CM_HSV,.59,.18,.08);
	maxLife = 10;
}

Globals::~Globals()
{

}

