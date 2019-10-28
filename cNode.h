#pragma once
class cNode
{
private:
	LPD3DXMESH m_pSphereMesh;

	Vec2 m_vPos;
	vector<cNode *> m_ConnectNode;
public:
	cNode(Vec2 vPos);
	~cNode();

	void Init();
	void Update();
	void Render();
	void Release();
};

