#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	void			Set_Pos(float _fX, float _fY);
	void			Set_Direction(BULLET::DIR _eDir);
	void			Set_Dead(void);
	void			Set_Angle(float _fAngle);
	void			Set_Target(CObj* _pTarget);
	void			Set_PosX(float _fX);
	void			Set_PosY(float _fY);
	void			Set_FrameKey(TCHAR* pFrameKey);
	void			Set_DrawID(int _iDrawID);
	void			Set_PowUp(int _iPowUp);
	void			Set_BombUp(int _iBombUp);

	const INFO&		Get_Info(void) const { return m_tInfo; }
	const RECT&		Get_Rect(void) const { return m_tRect; }
	const	int&	Get_DrawID(void)  const { return m_iDrawID; }
	const RENDERID	Get_RenderID(void) const { return m_eRenderGroup; }
	const int&		Get_PowUp(void) const { return m_iPowUp; }
	const int&		Get_BombUp(void) const { return m_iBombUp; }


public:
	virtual void		Initialize(void)PURE;
	virtual int			Update(void)PURE;
	virtual void		Late_Update(void)PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release(void)PURE;

	void				Move_Frame(void);
	void				Update_Rect(void);

protected:
	RECT			m_tRect;
	INFO			m_tInfo;
	FRAME			m_tFrame;
	DWORD			m_dwObjTime;
	TCHAR*			m_pFrameKey;
	float			m_fSpeed;
	float			m_fAngle;
	float			m_fDistance;

	int				m_iHp;
	bool			m_bDead;
	int				m_iPowUp;
	int				m_iBombUp;
	int				m_iScore;

	BULLET::DIR		m_eDir;
	CObj*			m_pTarget;

	int				m_iDrawID;
	RENDERID		m_eRenderGroup;
};

