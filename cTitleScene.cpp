#include "DXUT.h"
#include "cTitleScene.h"

#include "cTerrain.h"
#include "cPlayer.h"

cTitleScene::cTitleScene()
{
}


cTitleScene::~cTitleScene()
{
}

void cTitleScene::Init()
{
	m_Player = new cPlayer();
}

void cTitleScene::Update()
{
	m_Player->Update();
}

void cTitleScene::Render()
{
	m_Player->Render();

	D3DXMATRIX matX, matY, matZ , matR;

	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, D3DXToRadian(0));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
	
	matR = matX * matY * matZ;
	OBJ->Render(OBJ->FindOBJ("Map"), Vec3(0,0,0), matR, 1.f);
}

void cTitleScene::Release()
{
	SAFE_DELETE(m_Player);
}
