#include "stdafx.h"
#include "Monster2.h"
#include "MonsterBullet2.h"

#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ObjMgr.h"


CMonster2::CMonster2()
	: CountBullet(0)
{
}


CMonster2::~CMonster2()
{
}

void CMonster2::Initialize(void)
{
	m_tInfo.fX = -100.f;
	m_tInfo.fY = 450.f;

	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 80.f;

	m_fSpeed = 3.f;
	m_iScore = 120 + rand() % 30;
		
	m_iHp = 5;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster2_1.bmp", L"Monster2");

	/*
	m_pFrameKey = L"MonsterA";

	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 32;
	m_tFrame.dwFrameTime = GetTickCount();
	*/
	m_eRenderGroup = RENDER_OBJ;
}

int CMonster2::Update(void)
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
		m_tInfo.fX += m_fSpeed;
	}
	else if (MoveMonster == 1)
	{
		m_tInfo.fX -= m_fSpeed;
	}

	if (CountBullet < 10)
	{
		if (m_dwObjTime + 100 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTERBULLET2, CAbstractFactory<CMonsterBullet2>::Create((float)m_tInfo.fX, (float)m_tInfo.fY));
			m_dwObjTime = GetTickCount();
			CountBullet += 1;
		}
	}

	Late_Update();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster2::Late_Update(void)
{
	if (fMonsterGTC + 1500 < GetTickCount())
	{
		MoveMonster = 1;
		fMonsterGTC = GetTickCount();
	}
}

void CMonster2::Render(HDC hDC)
{
	HDC hMonADC = CBmpMgr::Get_Instance()->Find_Image(L"Monster2");

	GdiTransparentBlt(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMonADC,
		0,
		0,
		80,
		80,
		RGB(255, 255, 255));
}

void CMonster2::Release(void)
{
}
