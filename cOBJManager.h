#pragma once
#include "singleton.h"
#include "OBJLoader.h"

class cOBJManager : public singleton<cOBJManager>
{
private:
	OBJLoader loader;
	map<string, Mesh *> m_Mesh;
	map<string, vector<Mesh *> *> m_MultiMesh;
public:
	cOBJManager();

	virtual ~cOBJManager();
	
	Mesh * AddOBJ(const string& key, const string& path, const string& mappath = "None", const string& MtlPath = "None");
	vector<Mesh*> AddMultiOBJ(const string& key, const string& path, const string& mappath, int count = 0, const string& MtlPath = "None");
    Mesh * FindOBJ(const string& key);
	Mesh * FindMultidOBJ(const string& key , int count = 0);
	void Render(Mesh * mesh, Vec3 Pos, D3DXMATRIX matR, float scale = 1.f, D3DXCOLOR color = { 1.f,1.f,1.f,1.f });

	void RenderShadow(Mesh * mesh, Vec3 Pos);

	void Release();
};
#define OBJ cOBJManager::GetInstance()
