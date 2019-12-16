#include "DXUT.h"
#include "cMainGame.h"

#include "cLoadScene.h"
#include "cTitleScene.h"
#include "cMapEditerScene.h"

cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
}

void cMainGame::Init()
{
	IMAGE->Init();
	//CAMERA->Init();
	INPUT->Init();

	SCENE->AddScene("Load", new cLoadScene);
	SCENE->AddScene("Title", new cTitleScene);
	SCENE->AddScene("MapEditer", new cMapEditerScene);

	SCENE->ChangeScene("Load");
}

void cMainGame::Update()
{
	//if (CAMERA->GetMouseClip())
	CAMERA->Update();
	SCENE->Update();
	g_Bounding.Update();
	g_Effect.Update();
	INPUT->Update();

	if (INPUT->KeyDown('B')) {
		if (IsBoundingRender)
			IsBoundingRender = false;
		else
			IsBoundingRender = true;
	}
}

void cMainGame::Render()
{
	CAMERA->Render();
	IMAGE->Begin(false , false);
	SCENE->Render();
	IMAGE->End();
	g_Effect.Render();
	if(IsBoundingRender)
		g_Bounding.Render();
	
}

void cMainGame::Release()
{
	g_Effect.Release();
	cCameraManager::ResetInstance();
	cImageManager::ResetInstance();
	cInputManager::ResetInstance();
	cSceneManager::ResetInstance();
	cOBJManager::ResetInstance();
	cFxManager::ResetInstance();
	cMapManager::ResetInstance();
	cThreadPoolManager::ResetInstance();
	g_Bounding.Release();
}

void cMainGame::ResetDevice()
{
	IMAGE->LostDevice();
}

void cMainGame::LostDevice()
{
	IMAGE->ResetDevice();
}
