#pragma once
class cBullet
{
private:
	Vec3 m_vPos;
	Vec3 m_vDir;
	float m_fSpeed;

	ObjTag m_tag;

	bool b_Del;
	float m_fLifeTime;
	float m_fDelTime;

	cBoundingSphere * m_BoundingSphere;

	void CheckColl();

	cFrame * m_DarkBallFrame;
public:
	cBullet(Vec3 pos, Vec3 Dir, ObjTag tag, float speed, float lifetime);
	~cBullet();

	void Init();
	void Update();
	void Render();
	void Release();

	bool GetDel() { return b_Del; }
	void SetDel(bool Del) { b_Del = Del; }
};

