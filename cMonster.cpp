#include "DXUT.h"
#include "cMonster.h"

cMonster::cMonster(Vec3 pos, EnemyKind Kind)
	: cEnemy(pos, Kind)
{
	m_Obj = OBJ->FindMultidOBJ("Wolf_Idle", 0);
}


cMonster::~cMonster()
{
	Release();
}

void cMonster::Init()
{
}

void cMonster::Update()
{
	vDir = m_vTarget - m_vPos;
	if (i_Hp <= 0)
		State = Dead;
	else {
		if (D3DXVec3Length(&vDir) < 15.f) {
			State = Attack;
		}
		else if (D3DXVec3Length(&vDir) < 100.f)
			State = Walk;
		else
			State = Idle;
	}
	StateUpdate();	
	if (!m_BoundingSphere->GetDel() && m_BoundingSphere) {
		m_BoundingSphere->SetPos(m_vPos + Vec3(0, 10, 0));
		CheckColl();
	}
	ObjUpdate();
}

void cMonster::Render()
{
	D3DXMATRIX matX, matY, matZ;

	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, D3DXToRadian(f_Angle));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));

	D3DXMATRIX matR;
	matR = matX * matY * matZ;
	D3DXQUATERNION currQ;
	D3DXQuaternionRotationMatrix(&currQ, &matR);
	D3DXQuaternionSlerp(&prevQ, &prevQ, &currQ, 0.1f);
	D3DXMATRIX mRQ;
	D3DXMatrixRotationQuaternion(&mRQ, &prevQ);

	OBJ->Render(m_Obj, m_vPos, matR, f_Scale);
}

void cMonster::Release()
{
	if (m_BoundingSphere)
		m_BoundingSphere->SetDel(true);
}

void cMonster::ObjUpdate()
{
	switch (State)
	{
	case Idle:
		switch (m_EnemyState)
		{
		case Wolf:
			m_Obj = OBJ->FindMultidOBJ("Wolf_Idle", m_IdleFrame->NowFrame);
			break;
		case Zombie:
			m_Obj = OBJ->FindMultidOBJ("Zombie_Idle", m_IdleFrame->NowFrame);
			break;
		default:
			break;
		}
		break;
	case Walk:
		switch (m_EnemyState)
		{
		case Wolf:
			m_Obj = OBJ->FindMultidOBJ("Wolf_Walk", m_WalkFrame->NowFrame);
			break;
		case Zombie:
			m_Obj = OBJ->FindMultidOBJ("Zombie_Walk", m_WalkFrame->NowFrame);
			break;
		default:
			break;
		}
		break;
	case Attack:
		switch (m_EnemyState)
		{
		case Wolf:
			m_Obj = OBJ->FindMultidOBJ("Wolf_Attack", m_AttackFrame->NowFrame);
			break;
		case Zombie:
			m_Obj = OBJ->FindMultidOBJ("Zombie_Attack", m_AttackFrame->NowFrame);
			break;
		default:
			break;
		}
		break;
	case Dead:
		switch (m_EnemyState)
		{
		case Wolf:
			m_Obj = OBJ->FindMultidOBJ("Wolf_Dead", m_DeadFrame->NowFrame);
			break;
		case Zombie:
			m_Obj = OBJ->FindMultidOBJ("Zombie_Dead", m_DeadFrame->NowFrame);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void cMonster::StateUpdate()
{
	switch (State)
	{
	case Idle:
		m_IdleFrame->Frame();
		break;
	case Walk:
		m_WalkFrame->Frame();
		vDir = m_vTarget - m_vPos;
		D3DXVec3Normalize(&vDir, &vDir);
		m_vPos += vDir * 0.2f;
		f_Angle = atan2f(vDir.x, vDir.z);
		f_Angle = D3DXToDegree(f_Angle);
		break;
	case Attack:
		m_AttackFrame->Frame();
		break;
	case Dead:
		if (m_BoundingSphere)
			m_BoundingSphere->SetActive(false);
		m_DeadFrame->Frame();

		if (!IsDebug)
			b_Del = true;

		if (m_DeadFrame->NowFrame == m_DeadFrame->EndFrame)
			b_IsDead = true;
		if (m_DeadFrame->NowFrame == m_DeadFrame->StartFrame && b_IsDead)
			b_Del = true;
		break;
	default:
		break;
	}
}

void cMonster::CheckColl()
{
	if (!m_BoundingSphere->GetDel() && m_BoundingSphere) {
		for (auto iter : m_BoundingSphere->GetCollinfo()) {
			if (iter->Tag == BULLET) {
				g_Effect.GetEffect().push_back(new cEffect(IMAGE->FindImage("BloodEffect"), iter->Pos, 1.f, 0.05f));
				--i_Hp;
			}
		}
	}
}