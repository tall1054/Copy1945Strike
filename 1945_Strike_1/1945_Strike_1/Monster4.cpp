#include "stdafx.h"
#include "Monster4.h"
#include "MonsterBullet4.h"

#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ObjMgr.h"


CMonster4::CMonster4()
	: CountBullet(0)
{
}


CMonster4::~CMonster4()
{
}

void CMonster4::Initialize(void)
{
	m_tInfo.fX = 1000.f;
	m_tInfo.fY = 450.f;

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_fSpeed = 1.f;
	m_iScore = 240 + rand() % 10;
	m_iHp = 3.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Mob_C_1.bmp", L"Monster4");
}

int CMonster4::Update(void)
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
		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fY -= m_fSpeed;
	}
	if (MoveMonster == 1)
	{
		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fY += m_fSpeed;
	}

	if (CountBullet < 15)
	{
		if (m_dwObjTime + 700 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTERBULLET4, CAbstractFactory<CMonsterBullet4>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 225));
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTERBULLET4, CAbstractFactory<CMonsterBullet4>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 270));
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTERBULLET4, CAbstractFactory<CMonsterBullet4>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 315));

			m_dwObjTime = GetTickCount();
			CountBullet += 1;
		}
	}

	Late_Update();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster4::Late_Update(void)
{
	if (fMonsterGTC + 1300 < GetTickCount())
	{
		MoveMonster = 1;
		fMonsterGTC = GetTickCount();
	}
}

void CMonster4::Render(HDC hDC)
{
	HDC hMonADC = CBmpMgr::Get_Instance()->Find_Image(L"Monster4");

	GdiTransparentBlt(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMonADC,
		0,
		0,
		100,
		100,
		RGB(255, 255, 255));
}

void CMonster4::Release(void)
{
}
