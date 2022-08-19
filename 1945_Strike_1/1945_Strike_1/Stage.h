#pragma once
#include "Scene.h"
#include "Monster.h"
#include "Monster2.h"
#include "Monster3.h"
#include "Monster4.h"
#include "Monster5.h"
#include "Boss.h"
#include "Bullet.h"

class CStage :
	public CScene
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

	void		Monster_Creat01();
	void		Monster_Create2();
	void		Monster_Create3();
	void		Monster_Create4();
	void		Monster_Create5();
	void		Boss_Create();

private:
	DWORD		m_dwStageTime = GetTickCount();
	int			iMonster1Counter;
	int			iMonster2Counter;
	int			iMonster3Counter;
	int			iMonster4Counter;
	int			iMonster5Counter;
	int			iBossCounter;
};

