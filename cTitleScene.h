#pragma once
#include "cScene.h"

class cBulletAdmin;
class cEnemyAdmin;
class cEffectAdmin;
class cPlayer;
class cTitleScene : public cScene
{
private:
	cBulletAdmin * m_Bullet;
	cEnemyAdmin * m_Enemy;
	cPlayer * m_Player;
public:
	cTitleScene();
	virtual ~cTitleScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

