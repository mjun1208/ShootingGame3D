#include "DXUT.h"
#include "cMonster.h"


cMonster::cMonster(Vec3 pos, EnemyKind Kind)
	: cEnemy(pos, Kind)
{
}


cMonster::~cMonster()
{
}

void cMonster::Init()
{
}

void cMonster::Update()
{
	vDir = m_vTarget - m_vPos;
	D3DXVec3Normalize(&vDir, &vDir);
	m_vPos += vDir * 0.2f;
	f_Angle = atan2f(vDir.x, vDir.z);
	f_Angle = D3DXToDegree(f_Angle);


	switch (m_EnemyState)
	{
	case Wolf:
		m_Obj = OBJ->FindMultidOBJ("Wolf_Idle", m_IdleFrame->NowFrame);
		break;
	case Zombie:
		m_Obj = OBJ->FindMultidOBJ("Zombie_Idle", m_IdleFrame->NowFrame);
		break;
	default:
		break;
	}
}

void cMonster::Render()
{
	D3DXMATRIX matX, matY, matZ;

	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, D3DXToRadian(f_Angle));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));

	D3DXMATRIX matR;
	matR = matX * matY * matZ;
	D3DXQUATERNION currQ;
	D3DXQuaternionRotationMatrix(&currQ, &matR);
	D3DXQuaternionSlerp(&prevQ, &prevQ, &currQ, 0.1f);
	D3DXMATRIX mRQ;
	D3DXMatrixRotationQuaternion(&mRQ, &prevQ);

	OBJ->Render(m_Obj, m_vPos, matR, f_Scale);
}

void cMonster::Release()
{
}
