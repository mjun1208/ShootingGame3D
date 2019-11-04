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

	for (auto iter = m_Enemy.begin(); iter != m_Enemy.end();) {
		if ((*iter)->GetDel()) {
			SAFE_DELETE(*iter);
			iter = m_Enemy.erase(iter);
		}
		else
			++iter;
	}

	if (m_Enemy.size() == 0) {
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 0), Wolf));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 10), Wolf));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 20), Wolf));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 30), Wolf));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 40), Wolf));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 50), Wolf));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 60), Wolf));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 70), Wolf));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 80), Wolf));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 90), Wolf));
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
