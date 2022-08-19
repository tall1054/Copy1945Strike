#pragma once
#include "Obj.h"
class CIBomb :
	public CObj
{
public:
	CIBomb();
	virtual ~CIBomb();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int		MoveBomb = 0;
	DWORD	fBombGTC = GetTickCount();
	float	m_fAngle3;
};

