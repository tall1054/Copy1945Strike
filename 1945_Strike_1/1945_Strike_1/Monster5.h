#pragma once
#include "Obj.h"
class CMonster5 :
	public CObj
{
public:
	CMonster5();
	virtual ~CMonster5();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int		CountBullet;
	DWORD	fMonsterGTC = GetTickCount();
	int		MoveMonster = 0;
};

