#include "GGameDemoHeader.h"
#include "GRenderObject.h"


GRenderObject::GRenderObject ( void )
{
    mVisible = true;

    mChangeWhenPicked = false;
}


GRenderObject::~GRenderObject ( void )
{
    mForceMap = NULL;
}

bool GRenderObject::render()
{
    if ( !mVisible )
        return false;
    getTrans().set();
    return true;
}
