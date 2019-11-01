#include "DXUT.h"
#include "cBullet.h"


cBullet::cBullet(Vec3 pos, Vec3 Dir)
	: m_vPos(pos) , m_vDir(Dir)
{
	m_fSpeed = 3.f;
	b_Del = false;
	m_fLifeTime = 0;
}


cBullet::~cBullet()
{
}

void cBullet::Init()
{
}

void cBullet::Update()
{
	m_fLifeTime += DeltaTime;
	m_vPos += m_vDir * m_fSpeed;

	if (m_fLifeTime > 5.f)
		b_Del = true;
}

void cBullet::Render()
{
	D3DXMATRIX matX, matY, matZ, matR;
	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, D3DXToRadian(0));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
	matR = matX * matY * matZ;
	OBJ->Render(OBJ->FindOBJ("Player_Bullet"), m_vPos, matR , 0.1f);
}

void cBullet::Release()
{
}
