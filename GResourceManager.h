#pragma once
#include "XMap.h"
//warning C4150: 删除指向不完整“GAnimationResource”类型的指针；没有调用析构函数
template<typename T>
class GResourceManager
{
public:
    typedef CXMap<uString, T*> ResourceMap;
public:
    virtual ~GResourceManager ( void );
public:
    T* getResource ( const char* name );
    void destoryResource ( const char* name );
protected:
    ResourceMap	mResourceMap;
};

template<typename T>
void GResourceManager<T>::destoryResource ( const char* name )
{
    T* r = 0;
    if ( mResourceMap.Get ( name, r ) )
        dSafeDelete ( r );
    mResourceMap.erase ( name );
}

template<typename T>
T* GResourceManager<T>::getResource ( const char* name )
{
    T* res = 0;
    if ( !mResourceMap.Get ( name, res ) )
    {
        res = new T();
        if ( !res->createFromFile ( name ) )
        {
            CXASSERT ( 0 );
            dSafeDelete ( res );
        }
        else
        {
            mResourceMap.Insert ( name, res );
        }
    }
    return res;
}

template<typename T>
GResourceManager<T>::~GResourceManager ( void )
{
for ( auto p: mResourceMap )
    {
        p.second->destory();
    }
	mResourceMap.clear();
    //mResourceMap.destroySecond();
    //dSafeDeleteMap2 ( mResourceMap );
}

