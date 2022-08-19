#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
  : m_fSpeed(0.f), m_bDead(false), m_fAngle(0.f)
  , m_fDistance(0.f), m_iDrawID(0), m_pFrameKey(nullptr)
  , m_iHp(0), m_iPowUp(0), m_iBombUp(0), m_iScore(0)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
	ZeroMemory(&m_tFrame, sizeof(FRAME));
}


CObj::~CObj()
{
}

void CObj::Set_Pos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;
}

void CObj::Set_Direction(BULLET::DIR _eDir)
{
	m_eDir = _eDir;
}

void CObj::Set_Dead(void)
{
	m_bDead = true;
}

void CObj::Set_Angle(float _fAngle)
{
	m_fAngle = _fAngle;
}

void CObj::Set_Target(CObj * _pTarget)
{
	m_pTarget = _pTarget;
}

void CObj::Set_PosX(float _fX)
{
	m_tInfo.fX += _fX;
}

void CObj::Set_PosY(float _fY)
{
	m_tInfo.fY += _fY;
}

void CObj::Set_FrameKey(TCHAR * pFrameKey)
{
	m_pFrameKey = pFrameKey;
}

void CObj::Set_DrawID(int _iDrawID)
{
	m_iDrawID = _iDrawID;
}

void CObj::Set_PowUp(int _iPowUp)
{
	m_iPowUp = _iPowUp;
}

void CObj::Set_BombUp(int _iBombUp)
{
	m_iBombUp = _iBombUp;
}

void CObj::Move_Frame(void)
{
	if (m_tFrame.dwFrameTime + m_tFrame.dwFrameSpeed < GetTickCount())
	{
		++m_tFrame.iFrameStart;
		m_tFrame.dwFrameTime = GetTickCount();

		if (m_tFrame.iFrameStart > m_tFrame.iFrameEnd)
			m_tFrame.iFrameStart = 0;
	}
}

void CObj::Update_Rect(void)
{
	m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));
}
