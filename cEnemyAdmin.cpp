#include "DXUT.h"
#include "cEnemyAdmin.h"

#include "cEnemy.h"

#include "cMonster.h"
#include "cPlayer.h"
cEnemyAdmin::cEnemyAdmin(cPlayer * player, vector<cBullet *>& Bullet)
	: m_Player(player), m_Bullet(Bullet)
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
		iter->Update(m_Bullet);
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
		m_Enemy.push_back(new cMonster(Vec3(0, 0, 0),  EnemyKind(rand() % 5)));
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
