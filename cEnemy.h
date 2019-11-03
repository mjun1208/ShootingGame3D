#pragma once
#include "cBoundingSphere.h"

enum EnemyKind{
	Wolf, Zombie
};
class cBoundingSphere;
class cEnemy abstract
{
protected:
	Mesh * m_Obj;

	Vec3 m_vPos;
	Vec3 m_vTarget;
	bool b_Del;
	int i_Hp;
	float f_Scale;
	float f_Angle;
	D3DXQUATERNION prevQ;
	
	Vec3 vOriginDir;
	Vec3 vDir;

	bool b_IsDead;
	bool b_Attack;

	EnemyKind m_EnemyState;

	cFrame * m_IdleFrame;
	cFrame * m_WalkFrame;
	cFrame * m_AttackFrame;
	cFrame * m_DeadFrame;

	cBoundingSphere * m_BoundingSphere;
public:
	cEnemy(Vec3 pos ,EnemyKind Kind);
	virtual ~cEnemy();
	
	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

	virtual void ObjUpdate() PURE;
	virtual void StateUpdate() PURE;
 
	void SetTarget(Vec3 Target) { m_vTarget = Target; }
	int GetHp() { return i_Hp; }
	void SetHp(int hp) { i_Hp = hp; }

	bool GetDel() { return b_Del; }
};

