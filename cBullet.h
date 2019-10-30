#pragma once
class cBullet
{
public:
	cBullet();
	virtual ~cBullet();

	void Init();
	void Update();
	void Render();
	void Release();
};

