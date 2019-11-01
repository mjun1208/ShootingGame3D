#pragma once
#include "cScene.h"

class cBulletAdmin;
class cPlayer;
class cTitleScene : public cScene
{
private:
	cBulletAdmin * m_Bullet;
	cPlayer * m_Player;
public:
	cTitleScene();
	virtual ~cTitleScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

