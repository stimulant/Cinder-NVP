#include "Utils/Globals.h"

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
}

Globals::~Globals()
{
}

