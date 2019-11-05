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
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 0),  EnemyKind(rand() % 4)));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 10), EnemyKind(rand() % 4)));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 20), EnemyKind(rand() % 4)));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 30), EnemyKind(rand() % 4)));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 40), EnemyKind(rand() % 4)));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 50), EnemyKind(rand() % 4)));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 60), EnemyKind(rand() % 4)));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 70), EnemyKind(rand() % 4)));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 80), EnemyKind(rand() % 4)));
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 90), EnemyKind(rand() % 4)));
	}
}

void cEnemyAdmin::Render()
{
	for (auto iter : m_Enemy)
		iter->Render();

	IMAGE->ReBegin(true, false);
	IMAGE->PrintText("³²Àº Àû : " + to_string(m_Enemy.size()), Vec3(0, 100, 0), 20, D3DCOLOR_XRGB(255, 255, 255), false);
	IMAGE->ReBegin(false, false);

}

void cEnemyAdmin::Release()
{
	for (auto iter : m_Enemy)
		SAFE_DELETE(iter);

	m_Enemy.clear();
}
