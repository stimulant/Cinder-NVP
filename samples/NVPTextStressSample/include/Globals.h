#pragma once

#include "cinder/app/App.h"

class Globals
{
    static Globals* sInstance;

    public:
        static Globals* get();
        Globals( );
        ~Globals();

		float	hueSpread;
		float	satSpread;
		float	valSpread;

		float	maxLife;
		ci::Color lifeColor;
};





