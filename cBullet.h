#pragma once
class cBullet
{
private:
	Vec3 m_vPos;
	Vec3 m_vDir;
	float m_fSpeed;

	bool b_Del;
	float m_fLifeTime;

	cBoundingSphere * m_BoundingSphere;

	void CheckColl();
public:
	cBullet(Vec3 pos, Vec3 Dir);
	~cBullet();

	void Init();
	void Update();
	void Render();
	void Release();

	bool GetDel() { return b_Del; }
	void SetDel(bool Del) { b_Del = Del; }
};

