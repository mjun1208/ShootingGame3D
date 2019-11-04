#include "DXUT.h"
#include "cBullet.h"


cBullet::cBullet(Vec3 pos, Vec3 Dir)
	: m_vPos(pos) , m_vDir(Dir)
{
	m_fSpeed = 33.f;
	b_Del = false;
	m_fLifeTime = 0;
	Init();
}


cBullet::~cBullet()
{
	Release();
}

void cBullet::Init()
{
	m_BoundingSphere = new cBoundingSphere;
	m_BoundingSphere->ComputeBoundingSphere(BULLET , 1.6f);
	g_Bounding.GetBounding().push_back(m_BoundingSphere);
	m_BoundingSphere->SetPos(m_vPos);
}

void cBullet::Update()
{
	m_fLifeTime += DeltaTime;
	m_vPos += m_vDir * m_fSpeed * 0.1f;


	if (m_fLifeTime > 5.f)
		b_Del = true;

	if (!b_Del && !m_BoundingSphere->GetDel() && m_BoundingSphere) {
		m_BoundingSphere->SetPos(m_vPos);
		CheckColl();
	}
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
	m_BoundingSphere->SetDel(true);
}

void cBullet::CheckColl()
{
	if (!b_Del && !m_BoundingSphere->GetDel() && m_BoundingSphere) {
		for (auto iter : m_BoundingSphere->GetCollinfo()) {
			if (iter->Tag == ENEMY) {
				b_Del = true;
				m_BoundingSphere->SetActive(false);
			}
		}
	}
}