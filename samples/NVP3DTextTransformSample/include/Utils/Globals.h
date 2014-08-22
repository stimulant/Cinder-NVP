#pragma once

#include "cinder/Area.h"
#include "cinder/Matrix.h"

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





