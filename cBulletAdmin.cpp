#include "DXUT.h"
#include "cBulletAdmin.h"

#include "cBullet.h"

cBulletAdmin::cBulletAdmin()
{
}


cBulletAdmin::~cBulletAdmin()
{
}

void cBulletAdmin::Init()
{
}

void cBulletAdmin::Update()
{
}

void cBulletAdmin::Render()
{
	for (auto iter : m_Bullet)
		iter->Render();

}

void cBulletAdmin::Release()
{
	for (auto iter : m_Bullet)
		SAFE_DELETE(iter);

	m_Bullet.clear();
}
