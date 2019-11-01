#include "DXUT.h"
#include "cEnemy.h"


cEnemy::cEnemy(Vec3 pos, EnemyKind Kind)
	: m_vPos(pos), m_EnemyState(Kind)
{
	prevQ = { 0,0,0,1 };
	vOriginDir = vDir = { 0, 0, 1.f };
	f_Angle = 0;

	m_IdleFrame = new cFrame();
	m_WalkFrame = new cFrame();
	m_AttackFrame = new cFrame();
	m_DeadFrame = new cFrame();

	switch (m_EnemyState)
	{
	case Wolf:
		m_IdleFrame->SetFrame(0, 140 , 0.5f);
		m_WalkFrame->SetFrame(0, 42, 0.5f);
		m_AttackFrame->SetFrame(0, 115, 0.5f);
		m_DeadFrame->SetFrame(0, 110, 0.5f);
		f_Scale = 0.15f;
		break;
	case Zombie:
		m_IdleFrame->SetFrame(0, 120, 0.5f);
		m_WalkFrame->SetFrame(0, 24, 0.5f);
		m_AttackFrame->SetFrame(0, 139, 0.5f);
		m_DeadFrame->SetFrame(0, 89, 0.5f);
		f_Scale = 0.1f;
		break;
	default:
		break;
	}

	//Init();
}


cEnemy::~cEnemy()
{
	//Release();
	if (m_IdleFrame) 
		SAFE_DELETE(m_IdleFrame);
	if (m_WalkFrame)
		SAFE_DELETE(m_WalkFrame);
	if (m_AttackFrame)
		SAFE_DELETE(m_AttackFrame);
	if (m_DeadFrame)
		SAFE_DELETE(m_DeadFrame);
}
