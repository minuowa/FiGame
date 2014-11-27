#ifndef StdAfx_h__
#define StdAfx_h__
//--------------------------------------------------------------------------------------------------
//Windows所需头文件及库文件
#include <stdio.h>
#include <stdlib.h>

#include <list>
#include <Windows.h>
#include <WinBase.h>
#include <tchar.h>
#include <MMSystem.h>
#include <process.h>
#include <shlwapi.h>
#include <vector>
#include <D3D9Types.h>

#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"shlwapi.lib")
#pragma comment(lib,"Imm32.lib")
#pragma comment(lib,"Kernel32.lib")


#include <assert.h>

//Direct9所需头文件及库文件
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <d3d9.h>
#include <d3dx9math.h>
#include <d3d9types.h>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#ifdef _DEBUG
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif

#include "XBase.h"
typedef CXDynaArray<GString> CharStringArr;

//////////////////////////引擎文件需要的宏////////////////////////////////////

//定义常量

#define NORMALMATRIX D3DXMATRIX(1.0f,0.0f,0.0f,0.0f, 0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f)//单位矩阵

#define ZEROVECTOR3 D3DXVECTOR3(0.0f,0.0f,0.0f)		//零向量

#define ZEROFLOAT 0.0f								//float型零值

#define ERR_INT -1						//返回值为整形的函数，出错时返回的值
#define TRUE_INT 1						//返回值为整形的函数，正确时的返回值

#define ERR_DEBUG   0xffffffff			//调试用的，相当于一个错误值hr

//常用带的函数宏

#define RAND rand()

#define SAFERELEASE(p) if(p!=NULL) { p->Release(); p=NULL;}

#define SAFED_ELETE(p) if(p!=NULL) { delete p; p=NULL;}

#define SAFE_DELETE_ARRAY(p) { if(p!=NULL) { delete[] (p);   (p)=NULL; } }

//inline void dToggle ( bool b )
//{
//    b = !b;
//}

#define STATIC_MESH_MAX_NUM_ON_MAP 10					//地图上静态模型最大数量

//#define STATICMESHCOUNT							//资源中模型数量

//为了使物体跳跃时增加在空中停留的时长，跳跃方法中不使用重力加速度

#define JUMP_HEIGHT	60.0f							//物体跳起后能达到的高度
#define JUMP_TIME	1.0f							//物体跳起后在空中停留时间的1/2

#define GRAVITY (2*JUMP_HEIGHT/JUMP_TIME/JUMP_TIME)	//重力加速度

#define LOD_MAX_LEVEL 5							//最高LOD等级

#define WINDOW_WIDTH 1024						//窗口宽度
#define WINDOW_HEIGHT 700						//窗口高度





//结构体和枚举类型

enum TextPos
{
    tpCenter,
    tpLeft,
    tpRight,
};

//模型的类型，决定模型的创建方式
enum eMeshType
{
    mtMap,	//地图类型的，如地图、海面

    mtXFile,	//从X文件中加载的模型

};

struct MapObjInfo
{
    int nObjId;		//对象ID
    float x;		//坐标的X值
    float z;		//坐标的Z值

    float fBlockHeight;
    D3DXVECTOR3 vMin;
    D3DXVECTOR3 vMax;
};

enum eForceType
{
    ftUpAlways,			//上方向总是（0,1,0）
    ftUpWithMap,		//上方向与地面垂直，随地图而改变
};
//////////////////////////引擎文件常用的函数////////////////////////////////////

D3DVECTOR Vector ( float x, float y, float z );

//输出错误时Debug信息
void DebugMsgBox ( HRESULT hr, const char *StrDebug );

//给Mesh设置法线
ID3DXMesh *dSetMeshNormal ( ID3DXMesh *pMesh, IDirect3DDevice9 *DVC );

//获取子字符串个数
int GetSubCharCount ( const char* Sourc, const char* Dev );

//从文件名字中获取路径
void  GetFilePath ( char* sFileName, char* path );

//连接路径和文件名，获取文件全名
void GetFileName ( char *sPathName, char* sFileName );

//判断字符串是否存在，是否是空值
bool IsStrEmpty ( const char * str );

//生成指定范围的整数随机数
int RandIntEx ( int nMin, int nMax );

//生成指定范围的浮点随机数
float RandFloatEx ( float fMin, float fMax );

//给生成随机数赋予种子
void PreRandom();

//判断文件是否存在
bool IsFileExist ( const char * sFileName );

//将一个字符串转换成D3DXVECTOR3
void StrToVector3 ( const char *str , D3DXVECTOR3& v );	//将一个含三维向量的字符串的值取出来

//判断点是否在一个矩形区域中
bool IsPointInRect ( POINT pt, RECT *rc );

//获取包围球半径
bool GetBoundRadius ( ID3DXMesh *pMesh, float *pfRadiusOut );
#define dDegreeToAngle(d) ((d)*D3DX_PI/180.0f)
#define dAgngleToDegree(a) ((a)*180/D3DX_PI)
inline void getVector3Ease ( D3DXVECTOR3& out, D3DXVECTOR3* start, D3DXVECTOR3* end, DWORD elpaseTime, DWORD totalTime )
{
    float e = elpaseTime * 0.001f;
    float t = totalTime * 0.001f;
    out.x = gEaser.getEase ( start->x, end->x, e, t );
    out.y = gEaser.getEase ( start->y, end->y, e, t );
    out.z = gEaser.getEase ( start->z, end->z, e, t );
}
inline void dGetYawPitchRollFromMatrix ( const D3DXMATRIX& mat, float& roll, float& pitch, float& yaw )
{
    // Assuming the angles are in radians.
    float sp = -mat._23;
    if ( sp <=-1.0f )
    {
        pitch = -D3DX_PI / 2;
    }
    else if ( sp > 1.0f )
    {
        pitch = D3DX_PI / 2;
    }
    else
    {
        pitch = -asin ( sp );
    }
    if ( sp > 0.99998 ) // singularity at north pole
    {
        roll = 0.0f;
        yaw = atan2 ( -mat._31, mat._11 );
    }
    else
    {
        yaw = atan2 ( mat._13, mat._33 );
        roll = atan2 ( mat._21, mat._22 );
    }
}
inline void dGetTranslateFromMatrix ( D3DXVECTOR3& out, const D3DXMATRIX* mat )
{
    out.x = mat->_41;
    out.y = mat->_42;
    out.z = mat->_43;
}
#define Color_Max 255
inline void dMakeColor ( D3DCOLORVALUE& out, byte a, byte r, byte g, byte b )
{
    out.a = ( float ) a / 255;
    out.r = ( float ) r / 255;
    out.g = ( float ) g / 255;
    out.b = ( float ) b / 255;
}
//inline void dMakeColor ( D3DCOLORVALUE& out, float a, float r, float g, float b )
//{
//    out.a = a;
//    out.r = r;
//    out.g = g;
//    out.b = b;
//}
inline void dVector3Cross ( D3DXVECTOR3& out, const D3DXVECTOR3& v1, const D3DXVECTOR3& v2 )
{
    D3DXVec3Cross ( &out, &v1, &v2 );
}
inline void dVector3Normalize ( D3DXVECTOR3& v )
{
    D3DXVec3Normalize ( &v, &v );
}
inline D3DXVECTOR3 dVector3NormalizeSlow ( const D3DXVECTOR3& v )
{
    D3DXVECTOR3 out;
    D3DXVec3Normalize ( &out, &v );
    return out;
}
inline void dMatrixInverse ( D3DXMATRIX& mat )
{
    D3DXMatrixInverse ( &mat, 0, &mat );
}
inline void dMatrixTranslateVec3 ( D3DXVECTOR3& outin, const D3DXMATRIX& mat )
{
    D3DXVec3TransformCoord ( &outin, &outin, &mat );
}
inline float dVector3Length ( const D3DXVECTOR3& v )
{
    return sqrt ( dSequare ( v.x ) + dSequare ( v.y ) + dSequare ( v.z ) );
}
inline float dVector3Dot ( const D3DXVECTOR3& v1, const D3DXVECTOR3& v2 )
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
inline void dGetMatixFromQuation ( D3DXMATRIX&out, D3DXQUATERNION& in )
{
    float x2 = in.x * in.x;
    float y2 = in.y * in.y;
    float z2 = in.z * in.z;
    float xy = in.x * in.y;
    float xz = in.x * in.z;
    float yz = in.y * in.z;
    float wx = in.w * in.x;
    float wy = in.w * in.y;
    float wz = in.w * in.z;

    out._11 = 1.0f - 2.0f * ( y2 + z2 );
    out._12 = 2.0f * ( xy + wz );
    out._13 = 2.0f * ( xz - wy );
    out._14 = 0.0f;

    out._21 = 2.0f * ( xy - wz );
    out._22 = 1.0f - 2.0f * ( x2 - z2 );
    out._23 = 2.0f * ( yz + wx );
    out._24 = 0.0f;

    out._31 = 2.0f * ( xz + wy );
    out._32 = 2.0f * ( yz - wx );
    out._33 = 1.0f - 2.0f * ( x2 + y2 );
    out._34 = 0.0f;

    out._41 = 0.0f;
    out._42 = 0.0f;
    out._43 = 0.0f;
    out._44 = 1.0f;
}
#define FiDeclareSingleton( ClassName ) \
	private:\
	static ClassName* mInstance;\
	public:\
	static ClassName& getSingleton()  { if( mInstance == 0 ) { static ClassName scn; mInstance = &scn; } return *mInstance; }\
	static ClassName* getInstance(){ if( mInstance == 0 ) { static ClassName scn; mInstance = &scn;} return mInstance;}

#define FiImplateSingleton( ClassName ) ClassName* ClassName::mInstance = 0 ;
#define FiMarkSingleton() \
	static bool bInit = false;\
	CXASSERT(!bInit && "not a singleton");\
	bInit = true;\
 
//enum eHitType
//{
//    htNull,							//什么都没有撞到
//    htAutoMoveHitNoMap,				//没有撞到
//    htAutoMoveHitNoObj,				//没有撞到物体
//    htAutoMoveHitMap,				//撞到地图了
//    htAutoMoveHitObj,				//撞到物体了
//    //htAutoMoveHitObjAndMap,		//都撞到了
//
//    htNotAutoMoveHitNoMap,			//没有撞到
//    htNotAutoMoveHitMap,			//撞到地图
//    htNotAutoMoveHitObj,			//撞到物体
//    htNotAutoMoveHitNoObj,			//没有撞到物体
//
//    htNotAutoMoveHitBelowMap,		//撞到下面的物体了
//    htNotAutoMoveHitNoBelowMap,		//没有撞到下面的物体
//
//};

enum eObjState
{
    eObjState_Lighting				, //是否开灯光
    eObjState_Render				, //是否渲染
    eObjState_GetInput				, //是否可以操控
    eObjState_Update				, //是否可以更新
    eObjState_Picked				, //是否被点击了
    eObjState_ChangeWhenPicked		, //点击时是否发生改变
    eObjState_CanBeSelect			, //是否可以被选择
	eObjState_BeSelect				, //是否被选择了
};












//enum eObjParentType
//{
//    optByPosition,
//    optByName,
//};

struct ForceMapPara
{
    void *pMap;

    float fForceHeight;

    eForceType ft;

    ForceMapPara ( void *Map, float fHeight, eForceType ForceType )
    {
        pMap = Map;

        fForceHeight = fHeight;

        ft = ForceType;
    }

};

enum eMeshUsage
{
    muRender,
    muInsect,
};

struct MeshPara
{
public:

    float mfCellWidth;	    //地图中格子宽度
    float mfMaxHeight;	    //地图的最大高度
    int	  LnCellCount;	    //地图中格子数量
    GString mstrFileName;     //纹理文件名字，X文件名字
    GString mstrHeightMap;    //高度图文件名字

public:
    MeshPara() {};

    MeshPara ( float CellWidth, float MaxHight, int CellCount, const char *strFileName, const  char *strHeightMap )
    {
        mfCellWidth = CellWidth;
        mfMaxHeight = MaxHight;
        LnCellCount = CellCount;
        mstrFileName = strFileName;
        mstrHeightMap = strHeightMap;
    }
};

struct VertexXYZAndColor
{
    float x, y, z;
    D3DCOLOR color;
};
typedef void* GHandle;
extern const char* GetMediaPath();

int luaRegistAll();
//--------------------------------------------------------------------------------------------------
#endif // StdAfx_h__