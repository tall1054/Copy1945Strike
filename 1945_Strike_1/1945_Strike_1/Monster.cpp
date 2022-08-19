#include "stdafx.h"
#include "Monster.h"
#include "MonsterBullet.h"

#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "BmpMgr.h"


CMonster::CMonster()
	: CountBullet(0)
{
}


CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_tInfo.fX = 1000.f;
	m_tInfo.fY = -100.f;

	m_tInfo.fCX = 104.f;
	m_tInfo.fCY = 100.f;

	m_fSpeed = 3.f;
	m_iScore = 80 + rand()%20;
	m_iHp = 3;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster1_1.bmp", L"Monster1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Stretch2.bmp", L"Stretch");

	//사망처리
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Effect/Effect_Crash.bmp", L"Crash");

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

int CMonster::Update(void)
{
	//죽을떄
	if (true == m_bDead)
	{
		if (m_iHp > 0)
		{
			//체력1깍고
			m_iHp -= 1;
			//전역변수로 선언해준
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
		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fY += m_fSpeed;
	}
	else if (MoveMonster == 1)
	{
		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fY -= m_fSpeed;
	}


	if (CountBullet < 4)
	{
		if (m_dwObjTime + 500 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTERBULLET, CAbstractFactory<CMonsterBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY));
			m_dwObjTime = GetTickCount();
			CountBullet += 1;
		}
	
	}
	
	Late_Update();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster::Late_Update(void)
{
	if (fMonsterGTC + 1300 < GetTickCount())
	{
		MoveMonster = 1;
		fMonsterGTC = GetTickCount();
	}	
}

void CMonster::Render(HDC hDC)
{
	HDC hMonADC = CBmpMgr::Get_Instance()->Find_Image(L"Monster1");


	GdiTransparentBlt(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMonADC,
		0,
		0,
		104,
		100,
		RGB(255, 255, 255));
}

void CMonster::Release(void)
{
}

void CMonster::Dead_Render(HDC h_DC)
{
	HDC hCrashDC = CBmpMgr::Get_Instance()->Find_Image(L"Crash");

	GdiTransparentBlt(h_DC,
		int(m_tRect.left),
		int(m_tRect.top),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hCrashDC,
		0,
		0,
		40,
		40,
		RGB(255, 255, 255));
}
