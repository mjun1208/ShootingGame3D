#include "DXUT.h"
#include "cMonster.h"

#include "cBullet.h"
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

void cMonster::Update(vector<cBullet *>& Bullet)
{
	vDir = m_vTarget - m_vPos;
	if (i_Hp <= 0)
		State = Dead;
	else {
		if (D3DXVec3Length(&vDir) < f_AttackDistance && !b_Attack) {
			State = Attack;
			b_Attack = true;
			b_IsAttackEnd = true;
		}
		else if (D3DXVec3Length(&vDir) < f_Distance && !b_Attack) {
			State = Walk;
			m_AttackFrame->NowFrame = 0;
		}
		else if (!b_Attack){
			State = Idle;
			m_AttackFrame->NowFrame = 0;
		}
	}
	StateUpdate(Bullet);	
	b_CantMove = false;
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
		case Zombie2:
			m_Obj = OBJ->FindMultidOBJ("Zombie2_Idle", m_IdleFrame->NowFrame);
			break;
		case Reaper:
			m_Obj = OBJ->FindMultidOBJ("Reaper_Idle", m_IdleFrame->NowFrame);
			break;
		case Vampire:
			m_Obj = OBJ->FindMultidOBJ("Vampire_Idle", m_IdleFrame->NowFrame);
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
		case Zombie2:
			m_Obj = OBJ->FindMultidOBJ("Zombie2_Walk", m_WalkFrame->NowFrame);
			break;
		case Reaper:
			m_Obj = OBJ->FindMultidOBJ("Reaper_Walk", m_WalkFrame->NowFrame);
			break;
		case Vampire:
			m_Obj = OBJ->FindMultidOBJ("Vampire_Walk", m_WalkFrame->NowFrame);
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
		case Zombie2:
			m_Obj = OBJ->FindMultidOBJ("Zombie2_Attack", m_AttackFrame->NowFrame);
			break;
		case Reaper:
			m_Obj = OBJ->FindMultidOBJ("Reaper_Attack", m_AttackFrame->NowFrame);
			break;
		case Vampire:
			m_Obj = OBJ->FindMultidOBJ("Vampire_Attack", m_AttackFrame->NowFrame);
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
		case Zombie2:
			m_Obj = OBJ->FindMultidOBJ("Zombie2_Dead", m_DeadFrame->NowFrame);
			break;
		case Reaper:
			m_Obj = OBJ->FindMultidOBJ("Reaper_Dead", m_DeadFrame->NowFrame);
			break;
		case Vampire:
			m_Obj = OBJ->FindMultidOBJ("Vampire_Dead", m_DeadFrame->NowFrame);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void cMonster::StateUpdate(vector<cBullet *>& Bullet)
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
		if (!b_CantMove)
			m_vPos += vDir * f_Speed;
		f_Angle = atan2f(vDir.x, vDir.z);
		f_Angle = D3DXToDegree(f_Angle);
		break;
	case Attack:
		m_AttackFrame->Frame();
		vDir = m_vTarget - m_vPos;
		D3DXVec3Normalize(&vDir, &vDir);
		f_Angle = atan2f(vDir.x, vDir.z);
		f_Angle = D3DXToDegree(f_Angle);

		if ((m_AttackFrame->NowFrame == m_AttackFrame->EndFrame / 2) && m_EnemyState == Reaper)
			Bullet.push_back(new cBullet(m_vPos + Vec3(0, 10, 0), vDir, DARKBALL, 3.f, 2.f));

		if ((m_AttackFrame->NowFrame == m_AttackFrame->EndFrame / 2) && m_EnemyState == Vampire)
			Bullet.push_back(new cBullet(m_vPos + Vec3(0, 10, 0), vDir, BAT, 3.f, 2.f));

		if (m_AttackFrame->NowFrame == m_AttackFrame->EndFrame) {
			b_IsAttackEnd = false;
		}
		if (m_AttackFrame->NowFrame == m_AttackFrame->StartFrame && !b_IsAttackEnd) {
			b_Attack = false;
			State = Idle;
		}
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
			if (iter->Tag == PLAYERBULLET) {
				g_Effect.GetEffect().push_back(new cEffect(IMAGE->FindImage("BloodEffect"), iter->Pos, 1.f, 0.05f));
				--i_Hp;
			}
			else if (iter->Tag == ENEMY) {
				b_CantMove = true;
				Vec3 CollDis = iter->Pos - m_vPos;
				float fCollDis = (m_BoundingSphere->GetSize() + iter->Size) - D3DXVec3Length(&CollDis);
				D3DXVec3Normalize(&CollDis, &CollDis);
				m_vPos -= Vec3(CollDis.x , 0 , CollDis.z) * 0.2f;
			}
		}
	}
}