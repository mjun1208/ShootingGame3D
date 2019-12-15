#include "DXUT.h"
#include "cTitleScene.h"

#include "cBulletAdmin.h"
#include "cEnemyAdmin.h"
#include "cPlayer.h"

cTitleScene::cTitleScene()
{
}


cTitleScene::~cTitleScene()
{
}

void cTitleScene::Init()
{
	m_Bullet = new cBulletAdmin();
	m_Player = new cPlayer(m_Bullet->GetBullet());
	m_Enemy = new cEnemyAdmin(m_Player , m_Bullet->GetBullet());
}

void cTitleScene::Update()
{
	m_Bullet->Update();
	m_Enemy->Update();
	m_Player->Update();
}

void cTitleScene::Render()
{
	m_Player->Render();
	m_Enemy->Render();
	m_Bullet->Render();

	D3DXMATRIX matX, matY, matZ , matR;

	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, D3DXToRadian(0));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
	
	matR = matX * matY * matZ;
	OBJ->Render(OBJ->FindOBJ("Map"), Vec3(0, 64, 0), matR, 0.2f);
	OBJ->Render(OBJ->FindOBJ("Tree"), Vec3(0, 0, 0), matR, 0.1f);
}

void cTitleScene::Release()
{
	SAFE_DELETE(m_Player);
	SAFE_DELETE(m_Bullet);
	SAFE_DELETE(m_Enemy);
}
