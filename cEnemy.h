#pragma once
enum EnemyKind{
	Wolf, Zombie
};
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
public:
	cEnemy(Vec3 pos ,EnemyKind Kind);
	virtual ~cEnemy();
	
	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

	void SetTarget(Vec3 Target) { m_vTarget = Target; }
};

