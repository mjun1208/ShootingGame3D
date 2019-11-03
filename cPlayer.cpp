#include "DXUT.h"
#include "cPlayer.h"

#include "cBullet.h"

cPlayer::cPlayer(vector<cBullet *>& Bullet)
	: m_Bullet(Bullet)
{
	m_IdleFrame = new cFrame();
	m_IdleFrame->SetFrame(0, 231, 1.f);
	m_PistolMoveFrame = new cFrame();
	m_PistolMoveFrame->SetFrame(0, 24, 1.f);
	m_PistolShootFrame = new cFrame();
	m_PistolShootFrame->SetFrame(0, 35, 1.f);
	m_BigGunMoveFrame = new cFrame();
	m_BigGunMoveFrame->SetFrame(0, 30, 1.f);
	m_BigGunShootFrame = new cFrame();
	m_BigGunShootFrame->SetFrame(0, 17, 1.f);
	m_DeadFrame = new cFrame();
	m_DeadFrame->SetFrame(0, 99, 1.f);
	Init();
}


cPlayer::~cPlayer()
{
	Release();
}

void cPlayer::Init()
{
	RotX = RotY = RotZ = 0;
	vPos = { 0,0,0 };
	fSpeed = 1.f;
	vOriginDir = vDir = { 0, 0, 1.f };
	Angle = 0;
	ShootAngle = 0;
	CurAngle = 0;
	AimAngle = 0;
	prevQ = { 0,0,0,1 };

	IsAttack = false;
	IsAiming = false;
	IsMove = false;
	IsFixedCamera = false;
	IsBackMove = false;

	WeaponState = Pistol;
}

void cPlayer::Update()
{
	if (INPUT->MouseLDown()) {
		ShootBullet();
	}
	if (INPUT->KeyDown('1')) {
		WeaponState = Pistol;
	}
	if (INPUT->KeyDown('2')) {
		WeaponState = BigGun;
	}

	fSpeed = 0;

	if (!INPUT->KeyPress(VK_MENU)) {
		if (!IsSnipe)
			Angle = CAMERA->GetAngle();
		else {
			Angle = CAMERA->GetAngle();
		}
		IsFixedCamera = false;
	}
	else if (!IsSnipe)
		IsFixedCamera = true;
	else {
		if (!IsSnipe)
			Angle = CAMERA->GetAngle();
		else {
			Angle = CAMERA->GetAngle();
		}
		IsFixedCamera = false;
	}

	m_IdleFrame->Frame();

	if (INPUT->MouseRPress()) {
		AimAngle = Angle;
		IsSnipe = true;
	}
	else
		IsSnipe = false;


	if (IsSnipe)
		SnipeMove();
	else
		Move();

	if (IsAttack) {
		IsAiming = true;
		Angle = ShootAngle;
		fSpeed = 0.f;
		switch (WeaponState)
		{
		case Pistol:
			m_PistolShootFrame->Frame();
			if (m_PistolShootFrame->NowFrame == m_PistolShootFrame->EndFrame)
				IsAttack = false;
			break;
		case BigGun:
			m_BigGunShootFrame->Frame();
			if (m_BigGunShootFrame->NowFrame == m_BigGunShootFrame->EndFrame)
				IsAttack = false;
			break;
		case None:
			break;
		default:
			break;
		}
	}
	else {
		m_PistolShootFrame->NowFrame = m_PistolShootFrame->StartFrame;
		m_BigGunShootFrame->NowFrame = m_BigGunShootFrame->StartFrame;
	}

	if (fSpeed == 0) {
		IsMove = false;
	}
	else {
		IsMove = true;
		IsAiming = false;
		m_PistolMoveFrame->Frame();
		m_BigGunMoveFrame->Frame();
	}

	if (IsSnipe) {
		D3DXMATRIX matX, matY, matZ, matR;

		Vec3 CameraDir;
		D3DXMatrixRotationX(&matX, D3DXToRadian(0));
		D3DXMatrixRotationY(&matY, D3DXToRadian(CAMERA->GetAngle() - 90));
		D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
		matR = matX * matY * matZ;
		D3DXVec3TransformNormal(&CameraDir, &Vec3(-1,0,-1), &matR);

		vCameraPos = Vec3(vPos.x, vPos.y + 15, vPos.z);
		vCameraPos += CameraDir * 7.f;
		CAMERA->SetPos(vCameraPos);
		///////////////////////////////
		
		D3DXMatrixRotationX(&matX, D3DXToRadian(0));
		D3DXMatrixRotationY(&matY, D3DXToRadian(AimAngle));
		D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
		matR = matX * matY * matZ;
		D3DXVec3TransformNormal(&CameraDir, &vOriginDir, &matR);

		Vec3 TargetPos;
		TargetPos = Vec3(vPos.x, vPos.y + 15, vPos.z);
		TargetPos += CameraDir * 60.f;
		CAMERA->SetTarget(TargetPos);
	}
	else
		CAMERA->SetTarget(Vec3(vPos.x, vPos.y + 15, vPos.z));
}

void cPlayer::Render()
{
	// 각도 바꾸는거
	D3DXMATRIX matX, matY, matZ;

	D3DXMatrixRotationX(&matX, D3DXToRadian(0));
	D3DXMatrixRotationY(&matY, D3DXToRadian(Angle));
	D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));

	D3DXMATRIX matR;
	matR = matX * matY * matZ;
	D3DXQUATERNION currQ;
	D3DXQuaternionRotationMatrix(&currQ, &matR);
	D3DXQuaternionSlerp(&prevQ, &prevQ, &currQ, 0.1f);
	D3DXMATRIX mRQ;
	D3DXMatrixRotationQuaternion(&mRQ, &prevQ);
	// 방향 바꾸는거

	if (IsSnipe) {
		D3DXMatrixRotationX(&matX, D3DXToRadian(0));
		D3DXMatrixRotationY(&matY, D3DXToRadian(CAMERA->GetAngle()));
		D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
		mRQ = matX * matY * matZ;
		D3DXVec3TransformNormal(&vDir, &vOriginDir, &matR);
	}
	else
		D3DXVec3TransformNormal(&vDir, &vOriginDir, &mRQ);

	if (IsAiming) {
		switch (WeaponState)
		{
		case Pistol:
			OBJ->Render(OBJ->FindMultidOBJ("Player_Pistol_Shoot", m_PistolShootFrame->NowFrame), vPos, mRQ, 0.01f);
			break;
		case BigGun:
			OBJ->Render(OBJ->FindMultidOBJ("Player_BigGun_Shoot", m_BigGunShootFrame->NowFrame), vPos, mRQ, 0.01f);
			break;
		case None:
			break;
		default:
			break;
		}
	}
	else {
		if (!IsMove) {
			switch (WeaponState)
			{
			case Pistol:
				OBJ->Render(OBJ->FindMultidOBJ("Player_Pistol_Idle", m_IdleFrame->NowFrame), vPos, mRQ, 0.01f);
				break;
			case BigGun:
				OBJ->Render(OBJ->FindMultidOBJ("Player_BigGun_Idle", m_IdleFrame->NowFrame), vPos, mRQ, 0.01f);
				break;
			case None:
				break;
			default:
				break;
			}
		}
		else {
			switch (WeaponState)
			{
			case Pistol:
				if (IsBackMove)
					OBJ->Render(OBJ->FindMultidOBJ("Player_Pistol_Walk", m_PistolMoveFrame->EndFrame - m_PistolMoveFrame->NowFrame), vPos, mRQ, 0.01f);
				else
					OBJ->Render(OBJ->FindMultidOBJ("Player_Pistol_Walk", m_PistolMoveFrame->NowFrame), vPos, mRQ, 0.01f);
				break;
			case BigGun:
				if (IsBackMove)
					OBJ->Render(OBJ->FindMultidOBJ("Player_BigGun_Walk", m_BigGunMoveFrame->EndFrame - m_BigGunMoveFrame->NowFrame), vPos, mRQ, 0.01f);
				else
					OBJ->Render(OBJ->FindMultidOBJ("Player_BigGun_Walk", m_BigGunMoveFrame->NowFrame), vPos, mRQ, 0.01f);
				break;
			case None:
				break;
			default:
				break;
			}
		}
	}
}

void cPlayer::Release()
{
	SAFE_DELETE(m_IdleFrame);
	SAFE_DELETE(m_PistolMoveFrame);
	SAFE_DELETE(m_PistolShootFrame);
	SAFE_DELETE(m_BigGunMoveFrame);
	SAFE_DELETE(m_BigGunShootFrame);
	SAFE_DELETE(m_DeadFrame);
}

void cPlayer::Move()
{
	if (!IsAttack) {
		if (INPUT->KeyPress('A') || INPUT->KeyPress('D')) {
			if (INPUT->KeyPress('A')) {
				if (INPUT->KeyPress('W')) {
					if (IsFixedCamera)
						Angle -= 3;
					else
						Angle -= 45;
				}

				else if (INPUT->KeyPress('S')) {
					if (IsFixedCamera)
						Angle += 3;
					else
						Angle += 45;
				}
				else {
					if (IsFixedCamera)
						Angle -= 2;
					else
						Angle -= 90;
				}
				//Angle = CAMERA->GetAngle() - 90;
			}
			if (INPUT->KeyPress('D')) {
				if (INPUT->KeyPress('W')) {
					if (IsFixedCamera)
						Angle += 3;
					else
						Angle += 45;
				}
				else if (INPUT->KeyPress('S')) {
					if (IsFixedCamera)
						Angle -= 3;
					else
						Angle -= 45;
					IsBackMove = true;
				}
				else {
					if (IsFixedCamera)
						Angle += 2;
					else
						Angle += 90;
				}
				//Angle = CAMERA->GetAngle() + 90;
			}
		}

		if ((INPUT->KeyPress('S') && IsFixedCamera)) {
			IsBackMove = true;
			fSpeed = -1.f;
		}
		else if (INPUT->KeyPress('W') || INPUT->KeyPress('A') || INPUT->KeyPress('D') || INPUT->KeyPress('S'))
		{
			if (INPUT->KeyPress('S'))
				Angle -= 180;

			IsBackMove = false;
			fSpeed = 1.f;
		}
		if (INPUT->MouseLPress()) {
			ShootBullet();
		}
	}

	vPos += vDir * fSpeed;
}

void cPlayer::SnipeMove()
{
	IsAiming = true;
	//if (!IsAttack) {
		if (INPUT->KeyPress('A')) {
			if (INPUT->KeyPress('W'))
				Angle = AimAngle - 45;
			else if(INPUT->KeyPress('S'))
				Angle = AimAngle + 45;
			else
				Angle = AimAngle - 90;
		}
		else if (INPUT->KeyPress('D')) {
			if (INPUT->KeyPress('W'))
				Angle = AimAngle + 45;
			else if (INPUT->KeyPress('S'))
				Angle = AimAngle - 45;
			else
				Angle = AimAngle + 90;
		}

		if ((INPUT->KeyPress('S'))) {
			fSpeed = -1.f;
		}
		else if (INPUT->KeyPress('W') || INPUT->KeyPress('A') || INPUT->KeyPress('D') || INPUT->KeyPress('S'))
			fSpeed = 1.f;
		
		if (INPUT->MouseLPress() && !IsAttack) {
			ShootBullet();
		}
	//}
	//Vec3 TargetPos = vPos + vDir * fSpeed;
	//D3DXVec3Lerp(&vPos, &vPos, &TargetPos, 0.8f);

		D3DXMATRIX matX, matY, matZ, matR;

		D3DXMatrixRotationX(&matX, D3DXToRadian(0));
		D3DXMatrixRotationY(&matY, D3DXToRadian(Angle));
		D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
		matR = matX * matY * matZ;
		D3DXVec3TransformNormal(&vDir, &vOriginDir, &matR);

	vPos += vDir * fSpeed * 0.6f;
}

void cPlayer::ShootBullet()
{
	IsAttack = true;
	ShootAngle = Angle;

	if (IsSnipe) {
		D3DXMATRIX matX, matY, matZ, matR;

		D3DXMatrixRotationX(&matX, D3DXToRadian(0));
		D3DXMatrixRotationY(&matY, D3DXToRadian(AimAngle));
		D3DXMatrixRotationZ(&matZ, D3DXToRadian(0));
		matR = matX * matY * matZ;
		D3DXVec3TransformNormal(&vDir, &vOriginDir, &matR);
	}

	switch (WeaponState)
	{
	case Pistol:
		m_Bullet.push_back(new cBullet(vPos + Vec3(0, 13, 0) + vDir * 10, vDir));
		break;
	case BigGun:
		m_Bullet.push_back(new cBullet(vPos + Vec3(0, 13, 0) + vDir * 10, vDir));
		break;
	case None:
		break;
	default:
		break;
	}
}
