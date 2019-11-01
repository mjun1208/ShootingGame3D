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
	OBJLoad("Map", "./resorce/Map.obj", "./resorce/");
	OBJLoad("Coll", "./resorce/Coll.obj", "./resorce/");
	//OBJLoad("Player_Idle", "./resorce/Idle/idle(%d).obj", "./resorce/Idle/", 40, "idle.mtl");
	//OBJLoad("Player_Run", "./resorce/Run/Run(%d).obj", "./resorce/Run/", 24, "Run.mtl");
	//OBJLoad("Player_Dash", "./resorce/Dash/Dash(%d).obj", "./resorce/Dash/", 22, "Dash.mtl");
	//OBJLoad("Player_Attack", "./resorce/Attack/Attack(%d).obj", "./resorce/Attack/", 100, "Attack.mtl");
	//OBJLoad("Player_Sword", "./resorce/Attack/Sword/Sword(%d).obj", "./resorce/Attack/Sword/", 100, "Sword.mtl");
	//OBJLoad("Elucidator", "./resorce/Attack/Elucidator/Elucidator(%d).obj", "./resorce/Attack/Elucidator/", 100, "Elucidator.mtl");

	//OBJLoad("Player_Dead", "./resorce/Player/Dead/PlayerDead(%d).obj", "./resorce/Player/Dead/", 99, "PlayerDead.mtl");
	//
	//OBJLoad("Player_Pistol_Idle", "./resorce/Player/Pistol/Idle/PlayerIdle(%d).obj", "./resorce/Player/Pistol/Idle/", 231, "PlayerIdle.mtl");
	//OBJLoad("Player_Pistol_Walk", "./resorce/Player/Pistol/Walk/PlayerWalk(%d).obj", "./resorce/Player/Pistol/Walk/", 24, "PlayerWalk.mtl");
	//OBJLoad("Player_Pistol_Shoot", "./resorce/Player/Pistol/Shoot/PlayerShoot(%d).obj", "./resorce/Player/Pistol/Shoot/", 35, "PlayerShoot.mtl");
	//
	//OBJLoad("Player_BigGun_Idle", "./resorce/Player/BigGun/Idle/PlayerIdle(%d).obj", "./resorce/Player/BigGun/Idle/", 231, "PlayerIdle.mtl");
    //OBJLoad("Player_BigGun_Walk", "./resorce/Player/BigGun/Walk/PlayerWalk(%d).obj", "./resorce/Player/BigGun/Walk/", 30 , "PlayerWalk.mtl");
	//OBJLoad("Player_BigGun_Shoot", "./resorce/Player/BigGun/Shoot/PlayerShoot(%d).obj", "./resorce/Player/BigGun/Shoot/", 17, "PlayerShoot.mtl");
	//
	OBJLoad("Player_Bullet", "./resorce/Player/Bullet.obj", "./resorce/Player/");

	OBJLoad("Player_Dead", "./resorce/Player/Dead/PlayerDead(%d).obj", "./resorce/Player/Dead/", 1, "PlayerDead.mtl");

	OBJLoad("Player_Pistol_Idle", "./resorce/Player/Pistol/Idle/PlayerIdle(%d).obj", "./resorce/Player/Pistol/Idle/", 1, "PlayerIdle.mtl");
	OBJLoad("Player_Pistol_Walk", "./resorce/Player/Pistol/Walk/PlayerWalk(%d).obj", "./resorce/Player/Pistol/Walk/", 1, "PlayerWalk.mtl");
	OBJLoad("Player_Pistol_Shoot", "./resorce/Player/Pistol/Shoot/PlayerShoot(%d).obj", "./resorce/Player/Pistol/Shoot/", 1, "PlayerShoot.mtl");

	OBJLoad("Player_BigGun_Idle", "./resorce/Player/BigGun/Idle/PlayerIdle(%d).obj", "./resorce/Player/BigGun/Idle/", 1, "PlayerIdle.mtl");
	OBJLoad("Player_BigGun_Walk", "./resorce/Player/BigGun/Walk/PlayerWalk(%d).obj", "./resorce/Player/BigGun/Walk/", 1, "PlayerWalk.mtl");
	OBJLoad("Player_BigGun_Shoot", "./resorce/Player/BigGun/Shoot/PlayerShoot(%d).obj", "./resorce/Player/BigGun/Shoot/", 1, "PlayerShoot.mtl");

	//Wolf
	//OBJLoad("Wolf_Idle", "./resorce/Enemy/Wolf/Idle/WolfIdle_(%d).obj", "./resorce/Enemy/Wolf/Idle/", 140, "WolfIdle.mtl");
	//OBJLoad("Wolf_Walk", "./resorce/Enemy/Wolf/Walk/WolfWalk(%d).obj", "./resorce/Enemy/Wolf/Walk/", 42, "WolfWalk.mtl");
	//OBJLoad("Wolf_Attack", "./resorce/Enemy/Wolf/Attack/WolfAttack(%d).obj", "./resorce/Enemy/Wolf/Attack/", 115, "WolfAttack.mtl");
	//OBJLoad("Wolf_Dead", "./resorce/Enemy/Wolf/Dead/WolfDead(%d).obj", "./resorce/Enemy/Wolf/Dead/", 110, "WolfDead.mtl");
	//
	////Zombie
	//OBJLoad("Zombie_Idle", "./resorce/Enemy/Zombie/Idle/ZombieIdle(%d).obj", "./resorce/Enemy/Zombie/Idle/", 120, "ZombieIdle.mtl");
	//OBJLoad("Zombie_Walk", "./resorce/Enemy/Zombie/Walk/ZombieWalk(%d).obj", "./resorce/Enemy/Zombie/Walk/", 24, "ZombieWalk.mtl");
	//OBJLoad("Zombie_Attack", "./resorce/Enemy/Zombie/Attack/ZombieAttack(%d).obj", "./resorce/Enemy/Zombie/Attack/", 139, "ZombieAttack.mtl");
	//OBJLoad("Zombie_Dead", "./resorce/Enemy/Zombie/Dead/ZombieDead(%d).obj", "./resorce/Enemy/Zombie/Dead/", 89, "ZombieDead.mtl");

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

	//

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
