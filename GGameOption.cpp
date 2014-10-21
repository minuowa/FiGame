#include "GGameDemoHeader.h"
#include "GGameOption.h"
#include "GEnumTypesStrings.h"
#include "GD9Device.h"

GGameOption::GGameOption ( void )
    : RenderBloom ( false )
{
    FillMode = FillSolid;
    D9DEVICE->mOnResetDevice += this;
    updateRenderState();
}


GGameOption::~GGameOption ( void )
{
}

void GGameOption::registerAllProperty()
{
    //__super::registerAllProperty();
    __RegisterPropertyEnum ( FillMode );
    __RegisterProperty ( RenderBloom );
}

void GGameOption::onPropertyChangeEnd ( void* cur )
{
    __super::onPropertyChangeEnd ( cur );

    if ( &FillMode == cur )
    {
        updateRenderState();
    }
}

void GGameOption::updateRenderState()
{
    switch ( FillMode )
    {
    case FillPoint:
        D9DEVICE->GetDvc()->SetRenderState ( D3DRS_FILLMODE, D3DFILL_POINT );
        break;
    case FillSolid:
        D9DEVICE->GetDvc()->SetRenderState ( D3DRS_FILLMODE, D3DFILL_SOLID );
        break;
    case FillWire:
        D9DEVICE->GetDvc()->SetRenderState ( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
        break;
    default:
        break;
    }
}

void GGameOption::onCallBack ( const CXDelegate& delegate )
{
    if ( delegate == D9DEVICE->mOnResetDevice )
    {
        updateRenderState();
    }
}