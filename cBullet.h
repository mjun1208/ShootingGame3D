#pragma once
class cBullet
{
private:
	
	Vec3 m_vPos;
	Vec3 m_vDir;
	float m_fSpeed;

public:
	cBullet();
	virtual ~cBullet();

	void Init();
	void Update();
	void Render();
	void Release();
};

