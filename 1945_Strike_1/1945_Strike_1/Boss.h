#pragma once
#include "Obj.h"
class CBoss :
	public CObj
{
public:
	CBoss();
	virtual ~CBoss();

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

