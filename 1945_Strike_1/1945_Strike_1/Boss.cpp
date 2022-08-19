#include "stdafx.h"
#include "Boss.h"
#include "BossBullet.h"

#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ObjMgr.h"


CBoss::CBoss()
	: CountBullet(0)
{
}


CBoss::~CBoss()
{
}

void CBoss::Initialize(void)
{
	m_tInfo.fX = 450.f;
	m_tInfo.fY = -700.f;

	m_tInfo.fCX = 450.f;
	m_tInfo.fCY = 600.f;

	m_fSpeed = 3.f;                 
	m_iHp = 50;
	m_iScore = 1000;
	m_dwObjTime = 0;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/Boss2.bmp", L"Boss");
}

int CBoss::Update(void)
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

	if (CountBullet < 3)
	{
		if (m_dwObjTime + 1500 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CBossBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 270));
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CBossBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 225));
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CBossBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 315));
			m_dwObjTime = GetTickCount();
			CountBullet += 1;
		}
	}

	else if (CountBullet < 13)
	{
		if (m_dwObjTime + 2300 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CBossBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle));
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CBossBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 45));
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CBossBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 90));
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CBossBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 135));
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CBossBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 180));
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CBossBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 225));
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CBossBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 270));
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOSSBULLET, CAbstractFactory<CBossBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 315));
			m_dwObjTime = GetTickCount();
			CountBullet += 1;
		}
	}
	else 
	{
		CountBullet = 0;
	}

	Late_Update();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBoss::Late_Update(void)
{
	if (fMonsterGTC + 3800 < GetTickCount())
	{
		m_fSpeed = 0;
		fMonsterGTC = GetTickCount();
	}
}

void CBoss::Render(HDC hDC)
{
	HDC hMonADC = CBmpMgr::Get_Instance()->Find_Image(L"Boss");

	GdiTransparentBlt(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMonADC,
		0,
		0,
		450,
		600,
		RGB(255, 255, 255));
}

void CBoss::Release(void)
{
}
