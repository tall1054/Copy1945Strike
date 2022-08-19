#include "stdafx.h"
#include "Monster3.h"
#include "MonsterBullet3.h"

#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ObjMgr.h"


CMonster3::CMonster3()
	: CountBullet(0)
{
}


CMonster3::~CMonster3()
{
}

void CMonster3::Initialize(void)
{
	m_tInfo.fX = 300.f;
	m_tInfo.fY = -150.f;

	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;

	m_fSpeed = 0.8f;
	m_iScore = 150 + rand() % 50;
	m_iHp = 10.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Monster3_1.bmp", L"Monster3");
}

int CMonster3::Update(void)
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
	else if(MoveMonster == 1)
	{
		m_tInfo.fY -= m_fSpeed;
	}

	if (CountBullet < 20)
	{
		if(m_dwObjTime + 300 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTERBULLET3, CAbstractFactory<CMonsterBullet3>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle));
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTERBULLET3, CAbstractFactory<CMonsterBullet3>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 45));
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTERBULLET3, CAbstractFactory<CMonsterBullet3>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 90));
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTERBULLET3, CAbstractFactory<CMonsterBullet3>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 135));
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTERBULLET3, CAbstractFactory<CMonsterBullet3>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 180));
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTERBULLET3, CAbstractFactory<CMonsterBullet3>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 225));
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTERBULLET3, CAbstractFactory<CMonsterBullet3>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 270));
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTERBULLET3, CAbstractFactory<CMonsterBullet3>::Create((float)m_tInfo.fX, (float)m_tInfo.fY, (float)m_fAngle + 315));

			m_dwObjTime = GetTickCount();
			CountBullet += 1;
		}
	}

	Late_Update();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonster3::Late_Update(void)
{
	if (fMonsterGTC + 5000 < GetTickCount())
	{
		MoveMonster = 1;
		fMonsterGTC = GetTickCount();
	}
}

void CMonster3::Render(HDC hDC)
{
	HDC hMonADC = CBmpMgr::Get_Instance()->Find_Image(L"Monster3");

	GdiTransparentBlt(hDC,
		int(m_tRect.left),
		int(m_tRect.top),
		(int)m_tInfo.fCX,
		(int)m_tInfo.fCY,
		hMonADC,
		0,
		0,
		150,
		150,
		RGB(255, 255, 255));
}

void CMonster3::Release(void)
{
}
