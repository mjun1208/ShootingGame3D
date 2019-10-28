#include "DXUT.h"
#include "cMapEditerScene.h"

#include "cNode.h"

cMapEditerScene::cMapEditerScene()
{
}


cMapEditerScene::~cMapEditerScene()
{
}

void cMapEditerScene::Init()
{
	CAMERA->SetMouseClip(false);
	m_vCameraPos = Vec2(0, 0);
	CAMERA->SetPos(Vec3(m_vCameraPos.x, 50, m_vCameraPos.y));
	CAMERA->SetTarget(Vec3(0, 0, 0));
}

void cMapEditerScene::Update()
{
	if (INPUT->KeyPress('W')) 
		m_vCameraPos.y--;
	if (INPUT->KeyPress('S'))
		m_vCameraPos.y++;
	if (INPUT->KeyPress('A'))
		m_vCameraPos.x--;
	if (INPUT->KeyPress('D'))
		m_vCameraPos.x++;

	if (INPUT->MouseLDown())
		m_Node.push_back(new cNode(m_vCameraPos));

	for (auto iter : m_Node)
		iter->Update();

	CAMERA->SetPos(Vec3(m_vCameraPos.x, 50, m_vCameraPos.y));
	CAMERA->SetTarget(Vec3(m_vCameraPos.x, 0, m_vCameraPos.y));

	DEBUG_LOG(CAMERA->GetPos().x << " " << CAMERA->GetPos().y << " " << CAMERA->GetPos().z);
}

void cMapEditerScene::Render()
{
	for (auto iter : m_Node)
		iter->Render();
}

void cMapEditerScene::Release()
{
	for (auto iter : m_Node)
		SAFE_DELETE(iter);
}
