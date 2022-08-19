#pragma once
#include "Obj.h"
class CPower :
	public CObj
{
public:
	CPower();
	virtual ~CPower();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	int		MovePower = 0;
	DWORD	fPowerGTC = GetTickCount();
	float	m_fAngle2;

};

