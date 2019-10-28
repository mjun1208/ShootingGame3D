#include "DXUT.h"
#include "cOBJManager.h"

cOBJManager::cOBJManager()
{
}


cOBJManager::~cOBJManager()
{
	Release();
}

Mesh * cOBJManager::AddOBJ(const string& key, const string& path, const string& mappath, const string& MtlPath)
{
	auto find = m_Mesh.find(key);
	if (find == m_Mesh.end()) {
		Mesh * temp = new Mesh;
		loader.OBJLOAD(temp, path, mappath , MtlPath);

		m_Mesh.insert(make_pair(key, temp));
		return temp;
	}
	else {
		return find->second;
	}
}

vector<Mesh*> cOBJManager::AddMultiOBJ(const string & key, const string & path, const string& mappath, int count, const string& MtlPath)
{
	vector<Mesh *> * m_VecOBJ = new vector<Mesh *>;

	char sz[128] = "";
	for (int i = 0; i <= count; i++) {
		sprintf(sz, path.c_str(), i);
		Mesh * temp = new Mesh;
		loader.OBJLOAD(temp, sz, mappath, MtlPath);

		(*m_VecOBJ).push_back(temp);
	}
	m_MultiMesh.insert(make_pair(key, m_VecOBJ));
	return (*m_VecOBJ);
}

Mesh * cOBJManager::FindOBJ(const string& key)
{
	auto find = m_Mesh.find(key);
	if (find != m_Mesh.end()) {
		return find->second;
	}
	return nullptr;
}

Mesh * cOBJManager::FindMultidOBJ(const string & key, int count)
{
	auto find = m_MultiMesh.find(key);
	if (find != m_MultiMesh.end()) {
		return (*find->second)[count];
	}
	return nullptr;
}

void cOBJManager::Render(Mesh * mesh, Vec3 Pos, D3DXMATRIX matR, float scale , D3DXCOLOR color)
{
	D3DXMATRIX matW, matS, matT;
	D3DXMatrixScaling(&matS, scale, scale, scale);
	D3DXMatrixTranslation(&matT, Pos.x, Pos.y, Pos.z);

	matW = matS * matR * matT;

	HRESULT hr;

	FX->SetMatrix((D3DXHANDLE)"m_World", &matW);
	FX->SetMatrix((D3DXHANDLE)"m_View", &CAMERA->view);
	FX->SetMatrix((D3DXHANDLE)"m_Proj", &CAMERA->proj);
	FX->SetFloat((D3DXHANDLE)"OutLineWidth", 10.f);

	FX->SetTechnique((D3DXHANDLE)"BoSoo");

	UINT cPass;
	FX->Begin(&cPass, 0); //Pass�� ����� �޾ƿ�

	//for (UINT p = 0; p < cPass; ++p)
	//{
	//	FX->BeginPass(p);

		g_Device->SetTransform(D3DTS_WORLD, &matW); //fx�Ҷ� ���ص���
		for (int i = 0; i < mesh->Material.size(); ++i)
		{
			if (mesh->Material[i]->map) {
				g_Device->SetTexture(0, mesh->Material[i]->map->texturePtr);
			}
			else
				g_Device->SetTexture(0, nullptr);
			g_Device->SetMaterial(&mesh->Material[i]->material);

			mesh->mesh->DrawSubset(i);
		}

	//	FX->EndPass();
  	//
	//}
    // FX->End();
}

void cOBJManager::RenderShadow(Mesh * mesh, Vec3 Pos)
{
	g_Device->SetRenderState(D3DRS_STENCILENABLE, true);
	g_Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	g_Device->SetRenderState(D3DRS_STENCILREF, 0x0);
	g_Device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	g_Device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
	g_Device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	g_Device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	g_Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);
	
	D3DXVECTOR4 lightDirection(0.f, -0.5f, 0.f, 0.0f);
	D3DXPLANE groundPlane(0.0f, -1.0f, 0.0f, 0.0f);

	D3DXMATRIX S;
	D3DXMatrixShadow(&S, &lightDirection, &groundPlane);

	D3DXMATRIX T;
	D3DXMatrixTranslation(&T, Pos.x, Pos.y, Pos.z);
	D3DXMATRIX W = T * S;
	g_Device->SetTransform(D3DTS_WORLD, &W);

	g_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVDESTALPHA);

	Material * mtrl = new Material();
	mtrl->material.Diffuse.r = 0.f;
	mtrl->material.Diffuse.g = 0.f;
	mtrl->material.Diffuse.b = 0.f;
	mtrl->material.Power = 0.f;

	mtrl->material.Diffuse.a = 0.5f;

	g_Device->SetRenderState(D3DRS_ZENABLE, false);

	g_Device->SetMaterial(&mtrl->material);
	g_Device->SetTexture(0, 0);
	mesh->mesh->DrawSubset(0);

	g_Device->SetRenderState(D3DRS_ZENABLE, true);

	g_Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_Device->SetRenderState(D3DRS_STENCILENABLE, false);
	SAFE_DELETE(mtrl);
}

void cOBJManager::Release()
{
	for (auto iter : m_Mesh)
		SAFE_DELETE(iter.second);

	m_Mesh.clear();

	for (auto iter : m_MultiMesh) {
		for (auto _iter : (*iter.second)) {
			SAFE_DELETE(_iter);
		}
		SAFE_DELETE(iter.second);
	}

	m_Mesh.clear();
}
