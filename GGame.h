#pragma once

#include "GEffect.h"
#include "GAmmo.h"
#include "Particles.h"
#include "XCursor.h"
#include "GAnimEntity.h"
#include "GWater.h"
#include "GMeshBuffer.h"
#include "GWorldCorrd.h"
#include "GStillEntity.h"
#include "GFrameWork.h"
#include "GTimer.h"
#include "GNode.h"
#include "GCamera.h"
#include "GSceneMgr.h"
#include "XMultiThread.h"

extern DWORD WINAPI loadObj(LPVOID pParam);

class GGame:public GFrameWork
{
public:
	typedef GFrameWork Super;
public:
	GGame(void);
	~GGame(void);

	virtual bool init(HWND mainWnd);

	virtual bool loop();
	
	void shutDown();

	void finish();

	GSceneManager* getSceneMgr( ) const;
private:

	void getInput();

	void update();

	void render( );
public:
	CXMultiThread mMTLoadObj;

	GSceneManager *mSceneMgr;

	GStillEntity *mpSelectObj;

	GAnimEntity *mpSelectAnim;


private:

	void gameRender(float fPass);

	void renderEye(float fPass);

	bool	mFinished;
};

typedef CXSingleton<GGame> GGameSingleton;
#define TheGame GGameSingleton::getInstance()
#define TheSceneMgr TheGame->getSceneMgr()

inline GSceneManager* GGame::getSceneMgr() const
{
	return mSceneMgr;
}
DeclareFilmToolGlobal inline GSceneManager* getSceneMgr()
{
	return TheGame->getSceneMgr();
}
DeclareFilmToolGlobal inline void logInfo ( const char* s )
{
	OutputDebugStringA ( "\n" );
	OutputDebugStringA ( s );
}