#pragma once
#include "cScene.h"
class cNode;
class cMapEditerScene : public cScene
{
private:
	vector<cNode *> m_Node;
	Vec2 m_vCameraPos;
public:
	cMapEditerScene();
	virtual ~cMapEditerScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

