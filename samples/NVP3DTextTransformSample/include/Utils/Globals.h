#pragma once

#include "cinder/Utilities.h"
#include "cinder/app/App.h"

class Globals
{
        static Globals* sInstance;

    public:
        static Globals* get();
        Globals( );
        ~Globals();

        ci::Area		viewPortCached;
        ci::Matrix44f	projMatrixCached;
       
};





