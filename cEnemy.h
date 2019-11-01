#pragma once
class cEnemy abstract
{
protected:

	bool b_Del;
	int i_Hp;
public:
	cEnemy();
	virtual ~cEnemy();
	
	virtual void Init() PURE;
	virtual void Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
};

