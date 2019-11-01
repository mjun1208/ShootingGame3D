#pragma once
class cEnemy;
class cPlayer;
class cEnemyAdmin
{
private:
	vector<cEnemy *> m_Enemy;
	cPlayer * m_Player;
public:
	cEnemyAdmin(cPlayer * player);
	~cEnemyAdmin();

	void Init();
	void Update();
	void Render();
	void Release();

	vector<cEnemy *>& GetEnemy() { return m_Enemy; }
};

