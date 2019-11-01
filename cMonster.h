#pragma once
#include "cEnemy.h"
class cMonster : public cEnemy
{
public:
	cMonster(Vec3 pos, EnemyKind Kind);
	virtual ~cMonster();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

