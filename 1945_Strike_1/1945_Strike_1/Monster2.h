#pragma once
#include "Obj.h"
class CMonster2 :
	public CObj
{
public:
	CMonster2();
	virtual ~CMonster2();

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

