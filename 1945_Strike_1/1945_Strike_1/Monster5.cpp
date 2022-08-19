#include "stdafx.h"
#include "Monster5.h"
#include "MonsterBullet5.h"

#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ObjMgr.h"


CMonster5::CMonster5()
	:CountBullet(0)
{
}


CMonster5::~CMonster5()
{
}

void CMonster5::Initialize(void)
{
	m_tInfo.fX = 600.f;
	m_tInfo.fY = -150.f;

	m_tInfo.fCX = 360.f;
	m_tInfo.fCY = 180.f;

	m_fSpeed = 1.5f;
	m_iScore = 350 + rand() % 120;
	m_iHp = 20.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster4.bmp", L"Monster5");
}

int CMonster5::Update(void)
{
	if (true == m_bDead)
	{
		if (m_iHp > 0)
		{
			m_iHp -= 1;
			g_iScore += m_iScore;
			
			m_bDead = false;
		}
		else
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Explosion.mp3", CSoundMgr::EFFECT, 0.5f);
			return OBJ_DEAD;
		}
			
		//Dead_Render(h_DC);
	}

	if (MoveMonster == 0)
	{
		m_tInfo.fY += m_fSpeed;
	}

	else if (MoveMonster == 1)
	{
		m_tInfo.fY -= m_fSpeed;
	}

	if (CountBullet < 8)
	{
		if (m_dwObjTime + 700 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTERBULLET5, CAbstractFactory<CMonsterBullet5>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 225));
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTERBULLET5, CAbstractFactory<CMonsterBullet5>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 270));
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTERBULLET5, CAbstractFactory<CMonsterBullet5>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 315));

			m_dwObjTime = GetTickCount();
			CountBullet += 1;
		}
	}

	Late_Update();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster5::Late_Update(void)
{
	if (fMonsterGTC + 2500 < GetTickCount())
	{
		MoveMonster = 1;
		fMonsterGTC = GetTickCount();
	}
}

void CMonster5::Render(HDC hDC)
{
	HDC hMonADC = CBmpMgr::Get_Instance()->Find_Image(L"Monster5");

	GdiTransparentBlt(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMonADC,
		0,
		0,
		360,
		180,
		RGB(255, 255, 255));
}

void CMonster5::Release(void)
{
}
