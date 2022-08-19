#include "stdafx.h"
#include "Stage.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "CollisionMgr.h"
#include "AbstractFactory.h"
#include "Player.h"
#include "Bullet.h"
#include "Power.h"
#include "IBomb.h"


CStage::CStage()
{
}


CStage::~CStage()
{
	Release();
}

void CStage::Initialize(void)
{
	m_dwStageTime =0;
	iMonster1Counter = 0;
	iMonster2Counter = 0;
	iMonster3Counter = 0;
	iMonster4Counter = 0;
	iMonster5Counter = 0;
	iBossCounter = 0;
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Stage_B.bmp", L"Stage");
	CSoundMgr::Get_Instance()->PlayBGM(L"08 - Battle of Extreme north.mp3", 0.5f);

	CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJID::POWER, CAbstractFactory<CPower>::Create());
	CObjMgr::Get_Instance()->Add_Object(OBJID::IBOMB, CAbstractFactory<CIBomb>::Create());
}

int CStage::Update(void)
{
	Monster_Creat01();
	Monster_Create2();
	Monster_Create3();
	Monster_Create4();
	Monster_Create5();
	Boss_Create();
	
	//생존용
	if (CKeyMgr::Get_Instance()->Key_Down('T'))
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::PLAYER, CAbstractFactory<CPlayer>::Create());
	}

	//추가무기
	if (CKeyMgr::Get_Instance()->Key_Down('H'))
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::POWER, CAbstractFactory<CPower>::Create());
	}
	//추가폭탄
	if (CKeyMgr::Get_Instance()->Key_Down('Y'))
	{
		CObjMgr::Get_Instance()->Add_Object(OBJID::IBOMB, CAbstractFactory<CIBomb>::Create());
	}

	CObjMgr::Get_Instance()->Update();
	return 0;
}

void CStage::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();

}

void CStage::Render(HDC hDC)
{
	CObjMgr::Get_Instance()->Render(hDC);
}

void CStage::Release(void)
{
}

void CStage::Monster_Creat01()
{
	if (iMonster1Counter < 4)
	{
		if (m_dwStageTime + 2500 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, CAbstractFactory<CMonster>::Create());
			m_dwStageTime = GetTickCount();
			iMonster1Counter += 1;
		}
	}
}

void CStage::Monster_Create2()
{
	if (iMonster2Counter < 7)
	{
		if (m_dwStageTime + 2500 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, CAbstractFactory<CMonster2>::Create());
			m_dwStageTime = GetTickCount();
			iMonster2Counter += 1;
		}
	}
}

void CStage::Monster_Create3()
{
	if (iMonster3Counter < 2)
	{
		if (m_dwStageTime + 2500 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, CAbstractFactory<CMonster3>::Create());
			m_dwStageTime = GetTickCount();
			iMonster3Counter += 1;
		}
	}

	if (iMonster3Counter < 2)
	{
		if (m_dwStageTime + 2500 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, CAbstractFactory<CMonster3>::Create());
			m_dwStageTime = GetTickCount();
			iMonster3Counter += 1;
		}
	}
}

void CStage::Monster_Create4()
{
	if (iMonster4Counter < 4)
	{
		if (m_dwStageTime + 2500 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, CAbstractFactory<CMonster4>::Create());
			m_dwStageTime = GetTickCount();
			iMonster4Counter += 1;
		}
	}
}

void CStage::Monster_Create5()
{
	if (iMonster5Counter < 3)
	{
		if (m_dwStageTime + 2500 < GetTickCount())
		{
			CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER, CAbstractFactory<CMonster5>::Create());
			m_dwStageTime = GetTickCount();
			iMonster5Counter += 1;
		}
	}
}

void CStage::Boss_Create()
{
	if (iBossCounter < 1)
	{
		if (m_dwStageTime + 2500 < GetTickCount())
		{
		CObjMgr::Get_Instance()->Add_Object(OBJID::BOSS, CAbstractFactory<CBoss>::Create());
		m_dwStageTime = GetTickCount();
		iBossCounter += 1;
		}
	}
	
}
