#pragma once

#include "GameStaticObj.h"

#include "GNode.h"
#include "GMeshBuffer.h"
#include "GCamera.h"
#include "GD9Device.h"
#include "GFactory.h"
#include "GInputEntityManager.h"

#define SCENENUM 5		//��������	


enum eGameScene
{
	gsNull,

	gsLoading,

	gsGame,

	gslogin,			//��¼
};

class CSceneMachine
{
public:
	CSceneMachine();

	~CSceneMachine();
public:

	eGameScene GetNowScene();

	void ChangeToScene ( eGameScene gs );

public:

	eGameScene mgsNowScene;

	eGameScene mgsContainer[SCENENUM];

};

class GSceneManager: public CXCallBack
{
	DeclareFilmObj(GSceneManager);
public:
	GSceneManager ( void );
	~GSceneManager ( void );
public:

	void cull();
	bool init ();
	void* getInput ( float fPass );
	void setView();
	void setProj();
	void update ( float fPass );
	bool saveScene ( CChar* xmlFile );
	bool loadScene ( const char* xmlFile );
	void addStaticObj ( GNode* node );
	DeclareFilmTool void addDynaObj ( GNode* node );
	void addObj ( GNode* node, GNode* parent = nullptr );
	void addObj ( const char* parentName, const char* typeName );
	void deleteObj(const char* name);

	void selectObjByName ( const char* name );
	DeclareFilmTool GNode* getObj ( const char* name );

	void setOperatorObj ( int objID );
	GNode* getSceneRoot() const;
	GNode* createObjByTypeName ( const char* typeName );
	GCamera* findFirstCameraInScene(GNode* n);
	GCamera* changeToNextCamera();
	GCamera* getCurCamera()const;
	void moveToNextCamera();
	DeclareFilmTool void moveCameraToObj(const char* name,u32 timeMS);
public:
	bool setInnerNode(GNode* rootNode);

	virtual void onCallBack ( const CXDelegate& , CXEventArgs*  )override;
public:
	CXDelegate mDelegateReloadScene;

	GCamera* mCurCamera;
	uString mUsingCamera;
	CSceneMachine mSceneMachine;

	GNode* mSceneRootNode;
	GNode* mSceneStaticRootNode;
	GNode* mSceneDynamicRootNode;

	CXIndex mOperatoredObj;

};
