#pragma once
#include "Obj.h"
class CMonsterBullet2 :
	public CObj
{
public:
	CMonsterBullet2();
	virtual ~CMonsterBullet2();
public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

