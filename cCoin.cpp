#include "DXUT.h"
#include "cCoin.h"


void cCoin::CheckColl()
{
	if (!b_Del && !m_Bounding->GetDel() && m_Bounding) {
		for (auto iter : m_Bounding->GetCollinfo()) {
			if (iter->Tag == PLAYER) {
				b_Del = true;
				m_Bounding->SetActive(false);
				CoinCount++;
			}
		}
	}
}

cCoin::cCoin(Vec3 vPos)
	: m_vPos(vPos)
{
	Init();
}

cCoin::~cCoin()
{
	Release();
}

void cCoin::Init()
{
	m_Bounding = new cBoundingSphere;
	m_Bounding->ComputeBoundingSphere(COIN, 5.f);
	g_Bounding.GetBounding().push_back(m_Bounding);
	Rot = 0;
	b_Del = false;
}

void cCoin::Update()
{
	m_Bounding->SetPos(m_vPos + Vec3(0, 10, 0));
	if (Rot > 360)
		Rot -= 360;
	Rot+= 4;

	CheckColl();
}

void cCoin::Render()
{
	D3DXMATRIX matX, matY, matZ;

	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, D3DXToRadian(Rot));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));

	D3DXMATRIX matR;
	matR = matX * matY * matZ;

	OBJ->Render(OBJ->FindOBJ("Coin"),m_vPos + Vec3(0, 10, 0), matR ,0.1f);
}

void cCoin::Release()
{
	if (m_Bounding)
		m_Bounding->SetDel(true);
}
