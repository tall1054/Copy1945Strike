#pragma once
#include "Obj.h"
class CMonsterBullet4 :
	public CObj
{
public:
	CMonsterBullet4();
	virtual ~CMonsterBullet4();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;
};

