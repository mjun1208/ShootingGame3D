#pragma once
class cBullet;
enum WeaponKind {
	Pistol, BigGun, None
};
class cPlayer
{
private:
	vector<cBullet *>& m_Bullet;
private:
	cFrame * m_IdleFrame;
	cFrame * m_PistolMoveFrame;
	cFrame * m_PistolShootFrame;
	cFrame * m_BigGunMoveFrame;
	cFrame * m_BigGunShootFrame;
	cFrame * m_DeadFrame;

	D3DXQUATERNION prevQ;

	float RotX;
	float RotY;
	float RotZ;

	float fSpeed;

	float OldAngle;
	float CurAngle;
	float Angle;

	float ShootAngle;
	float AimAngle;

	Vec3 vOriginDir;
	Vec3 vDir;

	Vec3 vPos;
	Vec3 vCameraPos;

	bool IsAttack;
	bool IsAiming;
	bool IsMove;
	bool IsBackMove;

	bool IsSnipe;

	bool IsFixedCamera;

	WeaponKind WeaponState;

	void Move();
	void SnipeMove();
	void ShootBullet();
public:
	cPlayer(vector<cBullet *>& Bullet);
	~cPlayer();

	void Init();
	void Update();
	void Render();
	void Release();
};

