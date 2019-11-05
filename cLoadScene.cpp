#include "DXUT.h"
#include "cLoadScene.h"



cLoadScene::cLoadScene()
{
}


cLoadScene::~cLoadScene()
{
}

void cLoadScene::Init()
{
	NowLoad = 0;
	NowOBJLoad = 0;

	Load("BloodEffect", "./resorce/Effect/Blood/(%d).png", 5);

	OBJLoad("Map", "./resorce/Map.obj", "./resorce/");
	OBJLoad("Tree", "./resorce/Tree/Tree.obj", "./resorce/Tree/");
	if (IsDebug) {

		OBJLoad("Player_Dead", "./resorce/Player/Dead/PlayerDead(%d).obj", "./resorce/Player/Dead/", 99, "PlayerDead.mtl");

		OBJLoad("Player_Pistol_Idle", "./resorce/Player/Pistol/Idle/PlayerIdle(%d).obj", "./resorce/Player/Pistol/Idle/", 231, "PlayerIdle.mtl");
		OBJLoad("Player_Pistol_Walk", "./resorce/Player/Pistol/Walk/PlayerWalk(%d).obj", "./resorce/Player/Pistol/Walk/", 24, "PlayerWalk.mtl");
		OBJLoad("Player_Pistol_Shoot", "./resorce/Player/Pistol/Shoot/PlayerShoot(%d).obj", "./resorce/Player/Pistol/Shoot/", 35, "PlayerShoot.mtl");

		OBJLoad("Player_BigGun_Idle", "./resorce/Player/BigGun/Idle/PlayerIdle(%d).obj", "./resorce/Player/BigGun/Idle/", 231, "PlayerIdle.mtl");
		OBJLoad("Player_BigGun_Walk", "./resorce/Player/BigGun/Walk/PlayerWalk(%d).obj", "./resorce/Player/BigGun/Walk/", 30, "PlayerWalk.mtl");
		OBJLoad("Player_BigGun_Shoot", "./resorce/Player/BigGun/Shoot/PlayerShoot(%d).obj", "./resorce/Player/BigGun/Shoot/", 17, "PlayerShoot.mtl");

		OBJLoad("Player_Bullet", "./resorce/Player/Bullet.obj", "./resorce/Player/");

		//Wolf
		OBJLoad("Wolf_Idle", "./resorce/Enemy/Wolf/Idle/WolfIdle_(%d).obj", "./resorce/Enemy/Wolf/Idle/", 140, "WolfIdle.mtl");
		OBJLoad("Wolf_Walk", "./resorce/Enemy/Wolf/Walk/WolfWalk(%d).obj", "./resorce/Enemy/Wolf/Walk/", 42, "WolfWalk.mtl");
		OBJLoad("Wolf_Attack", "./resorce/Enemy/Wolf/Attack/WolfAttack(%d).obj", "./resorce/Enemy/Wolf/Attack/", 115, "WolfAttack.mtl");
		OBJLoad("Wolf_Dead", "./resorce/Enemy/Wolf/Dead/WolfDead(%d).obj", "./resorce/Enemy/Wolf/Dead/", 110, "WolfDead.mtl");

		//Zombie
		OBJLoad("Zombie_Idle", "./resorce/Enemy/Zombie/Idle/ZombieIdle(%d).obj", "./resorce/Enemy/Zombie/Idle/", 120, "ZombieIdle.mtl");
		OBJLoad("Zombie_Walk", "./resorce/Enemy/Zombie/Walk/ZombieWalk(%d).obj", "./resorce/Enemy/Zombie/Walk/", 24, "ZombieWalk.mtl");
		OBJLoad("Zombie_Attack", "./resorce/Enemy/Zombie/Attack/ZombieAttack(%d).obj", "./resorce/Enemy/Zombie/Attack/", 139, "ZombieAttack.mtl");
		OBJLoad("Zombie_Dead", "./resorce/Enemy/Zombie/Dead/ZombieDead(%d).obj", "./resorce/Enemy/Zombie/Dead/", 89, "ZombieDead.mtl");

		//Zombie
		OBJLoad("Zombie2_Idle", "./resorce/Enemy/Zombie2/Idle/ZombieIdle(%d).obj", "./resorce/Enemy/Zombie2/Idle/", 120, "ZombieIdle.mtl");
		OBJLoad("Zombie2_Walk", "./resorce/Enemy/Zombie2/Walk/ZombieWalk(%d).obj", "./resorce/Enemy/Zombie2/Walk/", 24, "ZombieWalk.mtl");
		OBJLoad("Zombie2_Attack", "./resorce/Enemy/Zombie2/Attack/ZombieAttack(%d).obj", "./resorce/Enemy/Zombie2/Attack/", 125, "ZombieAttack.mtl");
		OBJLoad("Zombie2_Dead", "./resorce/Enemy/Zombie2/Dead/ZombieDead(%d).obj", "./resorce/Enemy/Zombie2/Dead/", 89, "ZombieDead.mtl");

		//Reaper
		OBJLoad("Reaper_Idle", "./resorce/Enemy/Reaper/Idle/ReaperIdle(%d).obj", "./resorce/Enemy/Reaper/Idle/", 55, "ReaperIdle.mtl");
		OBJLoad("Reaper_Walk", "./resorce/Enemy/Reaper/Walk/ReaperWalk(%d).obj", "./resorce/Enemy/Reaper/Walk/", 42, "ReaperWalk.mtl");
		OBJLoad("Reaper_Attack", "./resorce/Enemy/Reaper/Attack/ReaperAttack(%d).obj", "./resorce/Enemy/Reaper/Attack/", 69, "ReaperAttack.mtl");
		OBJLoad("Reaper_Dead", "./resorce/Enemy/Reaper/Dead/ReaperDead(%d).obj", "./resorce/Enemy/Reaper/Dead/", 109, "ReaperDead.mtl");
	}
	else {
		OBJLoad("Player_Dead", "./resorce/Player/Dead/PlayerDead(%d).obj", "./resorce/Player/Dead/", 1, "PlayerDead.mtl");
		
		OBJLoad("Player_Pistol_Idle", "./resorce/Player/Pistol/Idle/PlayerIdle(%d).obj", "./resorce/Player/Pistol/Idle/", 1, "PlayerIdle.mtl");
		OBJLoad("Player_Pistol_Walk", "./resorce/Player/Pistol/Walk/PlayerWalk(%d).obj", "./resorce/Player/Pistol/Walk/", 1, "PlayerWalk.mtl");
		OBJLoad("Player_Pistol_Shoot", "./resorce/Player/Pistol/Shoot/PlayerShoot(%d).obj", "./resorce/Player/Pistol/Shoot/", 1, "PlayerShoot.mtl");
		
		OBJLoad("Player_BigGun_Idle", "./resorce/Player/BigGun/Idle/PlayerIdle(%d).obj", "./resorce/Player/BigGun/Idle/", 1, "PlayerIdle.mtl");
		OBJLoad("Player_BigGun_Walk", "./resorce/Player/BigGun/Walk/PlayerWalk(%d).obj", "./resorce/Player/BigGun/Walk/", 1, "PlayerWalk.mtl");
		OBJLoad("Player_BigGun_Shoot", "./resorce/Player/BigGun/Shoot/PlayerShoot(%d).obj", "./resorce/Player/BigGun/Shoot/", 1, "PlayerShoot.mtl");

		OBJLoad("Player_Bullet", "./resorce/Player/Bullet.obj", "./resorce/Player/");

		//Wolf
		OBJLoad("Wolf_Idle", "./resorce/Enemy/Wolf/Idle/WolfIdle_(%d).obj", "./resorce/Enemy/Wolf/Idle/", 1, "WolfIdle.mtl");
		OBJLoad("Wolf_Walk", "./resorce/Enemy/Wolf/Walk/WolfWalk(%d).obj", "./resorce/Enemy/Wolf/Walk/", 1, "WolfWalk.mtl");
		OBJLoad("Wolf_Attack", "./resorce/Enemy/Wolf/Attack/WolfAttack(%d).obj", "./resorce/Enemy/Wolf/Attack/", 1, "WolfAttack.mtl");
		OBJLoad("Wolf_Dead", "./resorce/Enemy/Wolf/Dead/WolfDead(%d).obj", "./resorce/Enemy/Wolf/Dead/", 1, "WolfDead.mtl");
		
		//Zombie
		OBJLoad("Zombie_Idle", "./resorce/Enemy/Zombie/Idle/ZombieIdle(%d).obj", "./resorce/Enemy/Zombie/Idle/", 1, "ZombieIdle.mtl");
		OBJLoad("Zombie_Walk", "./resorce/Enemy/Zombie/Walk/ZombieWalk(%d).obj", "./resorce/Enemy/Zombie/Walk/", 1, "ZombieWalk.mtl");
		OBJLoad("Zombie_Attack", "./resorce/Enemy/Zombie/Attack/ZombieAttack(%d).obj", "./resorce/Enemy/Zombie/Attack/", 1, "ZombieAttack.mtl");
		OBJLoad("Zombie_Dead", "./resorce/Enemy/Zombie/Dead/ZombieDead(%d).obj", "./resorce/Enemy/Zombie/Dead/", 1, "ZombieDead.mtl");

		//Zombie2
		OBJLoad("Zombie2_Idle", "./resorce/Enemy/Zombie2/Idle/ZombieIdle(%d).obj", "./resorce/Enemy/Zombie2/Idle/", 1, "ZombieIdle.mtl");
		OBJLoad("Zombie2_Walk", "./resorce/Enemy/Zombie2/Walk/ZombieWalk(%d).obj", "./resorce/Enemy/Zombie2/Walk/", 1, "ZombieWalk.mtl");
		OBJLoad("Zombie2_Attack", "./resorce/Enemy/Zombie2/Attack/ZombieAttack(%d).obj", "./resorce/Enemy/Zombie2/Attack/", 1, "ZombieAttack.mtl");
		OBJLoad("Zombie2_Dead", "./resorce/Enemy/Zombie2/Dead/ZombieDead(%d).obj", "./resorce/Enemy/Zombie2/Dead/", 1, "ZombieDead.mtl");

		//Reaper
		OBJLoad("Reaper_Idle", "./resorce/Enemy/Reaper/Idle/ReaperIdle(%d).obj", "./resorce/Enemy/Reaper/Idle/", 1, "ReaperIdle.mtl");
		OBJLoad("Reaper_Walk", "./resorce/Enemy/Reaper/Walk/ReaperWalk(%d).obj", "./resorce/Enemy/Reaper/Walk/", 1, "ReaperWalk.mtl");
		OBJLoad("Reaper_Attack", "./resorce/Enemy/Reaper/Attack/ReaperAttack(%d).obj", "./resorce/Enemy/Reaper/Attack/", 1, "ReaperAttack.mtl");
		OBJLoad("Reaper_Dead", "./resorce/Enemy/Reaper/Dead/ReaperDead(%d).obj", "./resorce/Enemy/Reaper/Dead/", 1, "ReaperDead.mtl");
	}

	MaxLoad = m_Load.size();
	MaxOBJLoad = m_OBJLoad.size();
}

void cLoadScene::Update()
{
	if (NowLoad != MaxLoad) {
		IMAGE->AddImage(
			m_Load[NowLoad].key,
			m_Load[NowLoad].path,
			m_Load[NowLoad].count);
		NowLoad++;
	}
	else {
		if (NowOBJLoad != MaxOBJLoad) {
			if(m_OBJLoad[NowOBJLoad].count == 0)
			OBJ->AddOBJ(
				m_OBJLoad[NowOBJLoad].key,
				m_OBJLoad[NowOBJLoad].path,
				m_OBJLoad[NowOBJLoad].mappath);
			else
			OBJ->AddMultiOBJ(
				m_OBJLoad[NowOBJLoad].key,
				m_OBJLoad[NowOBJLoad].path,
				m_OBJLoad[NowOBJLoad].mappath,
				m_OBJLoad[NowOBJLoad].count,
				m_OBJLoad[NowOBJLoad].mtlpath);
			NowOBJLoad++;
		
			DEBUG_LOG(NowOBJLoad << " / " << MaxOBJLoad);
		}
		else {
			SCENE->ChangeScene("Title");
		}
		//SCENE->ChangeScene("Title");
	}
}

void cLoadScene::Render()
{
}

void cLoadScene::Release()
{
}
