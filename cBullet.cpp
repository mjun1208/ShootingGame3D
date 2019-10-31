#include "DXUT.h"
#include "cBullet.h"


cBullet::cBullet()
{
}


cBullet::~cBullet()
{
}

void cBullet::Init()
{
}

void cBullet::Update()
{
	m_vPos += m_vDir * m_fSpeed;
}

void cBullet::Render()
{
}

void cBullet::Release()
{
}
