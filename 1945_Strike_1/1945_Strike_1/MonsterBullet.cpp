#include "stdafx.h"
#include "MonsterBullet.h"

#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ObjMgr.h"


CMonsterBullet::CMonsterBullet()
{
}


CMonsterBullet::~CMonsterBullet()
{
}

void CMonsterBullet::Initialize(void)
{
	m_tInfo.fCX = 12.f;
	m_tInfo.fCY = 12.f;

	m_fSpeed = 5.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MonBullet/Bullet_Mob_A.bmp", L"MonBullet1");


	//총알 쏘는 횟수 변수를 선언
	

	m_eRenderGroup = RENDER_OBJ;
}

int CMonsterBullet::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	m_tInfo.fY += m_fSpeed;

	
	Late_Update();
	Update_Rect();
	return 0;
}

void CMonsterBullet::Late_Update(void)
{
	if ((0 >= m_tInfo.fY) || (WINCY <= m_tInfo.fY))
	{
		m_bDead = true;
	}
}

void CMonsterBullet::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MonBullet1");

	GdiTransparentBlt
	(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),	//	2, 3인자 복사 받을 위치의 좌표를 전달
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		(int)m_tInfo.fCY,
		hMemDC,							// 비트맵 정보를 가지고 있는 DC
		0,								// 7,8인자 비트맵을 출력할 시작좌표
		0,
		12,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		12,
		RGB(255, 255, 255));
}

void CMonsterBullet::Release(void)
{
}
