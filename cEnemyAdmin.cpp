#include "DXUT.h"
#include "cEnemyAdmin.h"

#include "cEnemy.h"

#include "cMonster.h"
#include "cPlayer.h"
cEnemyAdmin::cEnemyAdmin(cPlayer * player)
	: m_Player(player)
{
	Init();
}


cEnemyAdmin::~cEnemyAdmin()
{
	Release();
}

void cEnemyAdmin::Init()
{
	m_Enemy.push_back(new cMonster(Vec3(0, 0, 0), Wolf));
}

void cEnemyAdmin::Update()
{
	for (auto iter : m_Enemy) {
		iter->SetTarget(m_Player->GetPos());
		iter->Update();
	}
}

void cEnemyAdmin::Render()
{
	for (auto iter : m_Enemy)
		iter->Render();
}

void cEnemyAdmin::Release()
{
	for (auto iter : m_Enemy)
		SAFE_DELETE(iter);

	m_Enemy.clear();
}
