#include "DXUT.h"
#include "cNode.h"


cNode::cNode(Vec2 vPos)
	: m_vPos(vPos)
{
	Init();
}


cNode::~cNode()
{
	Release();
}

void cNode::Init()
{
	D3DXCreateSphere(g_Device, 10.0f, 10, 10, &m_pSphereMesh, NULL);
}

void cNode::Update()
{
}

void cNode::Render()
{
	D3DXMATRIX matW, matS, matR, matT;
	D3DXMATRIX matX, matY, matZ;

	D3DXMatrixScaling(&matS, 1.f, 1.f, 1.f);

	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, D3DXToRadian(0));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
	matR = matX * matY * matZ;

	D3DXMatrixTranslation(&matT, m_vPos.x, 0, m_vPos.y);

	matW = matS * matR * matT;

	g_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	D3DMATERIAL9 mtrl;
	ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));

	mtrl.Diffuse.r = mtrl.Ambient.r = 1.f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 1.f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.f;

	g_Device->SetMaterial(&mtrl);
	g_Device->SetTransform(D3DTS_WORLD, &matW);
	//WireFrame으로 출력
	m_pSphereMesh->DrawSubset(0);
	//출력
	g_Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	//Solid로 변경
}

void cNode::Release()
{
	SAFE_RELEASE(m_pSphereMesh);
}
