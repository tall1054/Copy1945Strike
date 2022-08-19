#pragma once
#include "Obj.h"
class CMonsterBullet5 :
	public CObj
{
public:
	CMonsterBullet5();
	virtual ~CMonsterBullet5();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

