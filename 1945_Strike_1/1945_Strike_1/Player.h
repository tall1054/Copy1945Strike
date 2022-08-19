#pragma once
#include "Obj.h"
#include "Include.h"

class CPlayer final :
	public CObj
{
public:
	enum PLAYERSTATE { IDLE, HIT, DEAD, END };

public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

private:
	void		Key_Input(void);
	void		State_Change();

private:
	DWORD					m_dwTime;
	float					m_fTime;
	PLAYERSTATE				m_ePreState;
	PLAYERSTATE				m_eCurState;
	bool					m_bStretch = true;


};

