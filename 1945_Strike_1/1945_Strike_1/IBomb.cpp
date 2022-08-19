#include "stdafx.h"
#include "IBomb.h"

#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "BmpMgr.h"


CIBomb::CIBomb()
{
}


CIBomb::~CIBomb()
{
}

void CIBomb::Initialize(void)
{
	m_tInfo.fX = 300.f;
	m_tInfo.fY = 250.f;

	m_tInfo.fCX = 56.f;
	m_tInfo.fCY = 32.f;

	m_fSpeed = 0.5f;

	m_fAngle = 5;
	m_fAngle3 = 5;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Item_Eagle.bmp", L"Bomb2");

	m_eRenderGroup = RENDER_OBJ;
}

int CIBomb::Update(void)
{
	if (true == m_bDead)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"ItemGain.mp3", CSoundMgr::EFFECT, 1.f);
		return OBJ_DEAD;
	}
		

	m_tInfo.fX += (m_fAngle)* m_fSpeed;
	m_tInfo.fY -= (m_fAngle3)* m_fSpeed;

	Update_Rect();

	if ((0 >= m_tRect.left) || (WINCX <= m_tRect.right))
	{
		if (0 >= m_fAngle)
		{
			m_fAngle = ((rand() % 3) + 3.f);
		}
		else if (0 <= m_fAngle)
		{
			m_fAngle = -((rand() % 3) + 3.f);

		}
	}
	if ((0 >= m_tRect.top) || (WINCY <= m_tRect.bottom))
	{
		if (0 >= m_fAngle3)
		{
			m_fAngle3 = ((rand() % 3) + 3.f);

		}
		else if (0 <= m_fAngle3)
		{
			m_fAngle3 = -((rand() % 3) + 3.f);

		}

	}
	return OBJ_NOEVENT;
}

void CIBomb::Late_Update(void)
{
	if (fBombGTC + 1000 < GetTickCount())
	{
		MoveBomb = 1;
		fBombGTC = GetTickCount();
	}
}

void CIBomb::Render(HDC hDC)
{
	HDC hBombDC = CBmpMgr::Get_Instance()->Find_Image(L"Bomb2");

	GdiTransparentBlt(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hBombDC,
		56,
		0,
		56,
		32,
		RGB(255, 255, 255));
}

void CIBomb::Release(void)
{
}
