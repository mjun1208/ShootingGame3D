#pragma once
class cEnemy;
class cPlayer;
class cBullet;
class cEnemyAdmin
{
private:
	vector<cBullet *>& m_Bullet;
	vector<cEnemy *> m_Enemy;
	cPlayer * m_Player;
public:
	cEnemyAdmin(cPlayer * player, vector<cBullet *>& Bullet);
	~cEnemyAdmin();

	void Init();
	void Update();
	void Render();
	void Release();

	vector<cEnemy *>& GetEnemy() { return m_Enemy; }
};

