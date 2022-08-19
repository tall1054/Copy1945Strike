#pragma once
#include "Obj.h"
class CBossBullet :
	public CObj
{
public:
	CBossBullet();
	virtual ~CBossBullet();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	POINTFLOAT		m_tCenterPos;
	float			m_fRevolutionAngle;
	float			m_fCenterSpeed;
	bool			m_bStart;
};

