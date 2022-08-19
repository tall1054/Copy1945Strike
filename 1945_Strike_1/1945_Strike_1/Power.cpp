#include "stdafx.h"
#include "Power.h"

#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "BmpMgr.h"

CPower::CPower()
{
}


CPower::~CPower()
{
}

void CPower::Initialize(void)
{
	m_tInfo.fX = 450.f;
	m_tInfo.fY = 450.f;

	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 22.f;

	m_fSpeed = 0.5f;

	m_fAngle = 5;
	m_fAngle2 = -5;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Item/Item_Power.bmp", L"Power");

	m_eRenderGroup = RENDER_OBJ;
}

int CPower::Update(void)
{
	if (true == m_bDead)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"ItemGain.mp3", CSoundMgr::EFFECT, 1.f);
		return OBJ_DEAD;
	}
		

	m_tInfo.fX += (m_fAngle) * m_fSpeed;
	m_tInfo.fY -= (m_fAngle2) * m_fSpeed;

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
		if (0 >= m_fAngle2)
		{
			m_fAngle2 = ((rand() % 3) + 3.f);

		}
		else if (0 <= m_fAngle2)
		{
			m_fAngle2 = -((rand() % 3) + 3.f);

		}

	}
	return OBJ_NOEVENT;
}

void CPower::Late_Update(void)
{
	if (fPowerGTC + 1000 < GetTickCount())
	{
		MovePower = 1;
		fPowerGTC = GetTickCount();
	}
}

void CPower::Render(HDC hDC)
{
	HDC hPowDC = CBmpMgr::Get_Instance()->Find_Image(L"Power");

	GdiTransparentBlt(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hPowDC,
		0,
		0,
		32,
		22,
		RGB(255, 255, 255));
}

void CPower::Release(void)
{
}
