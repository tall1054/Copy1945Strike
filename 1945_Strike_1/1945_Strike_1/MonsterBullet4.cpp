#include "stdafx.h"
#include "MonsterBullet4.h"

#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ObjMgr.h"


CMonsterBullet4::CMonsterBullet4()
{
}


CMonsterBullet4::~CMonsterBullet4()
{
}

void CMonsterBullet4::Initialize(void)
{
	m_tInfo.fCX = 16.f;
	m_tInfo.fCY = 16.f;

	m_fSpeed = 4.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/MonBullet/Bullet_Mob_C.bmp", L"MonBullet3");

	m_eRenderGroup = RENDER_OBJ;
}

int CMonsterBullet4::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	Late_Update();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CMonsterBullet4::Late_Update(void)
{
	if ((WINCY <= m_tInfo.fY))
	{
		m_bDead = true;
	}
}

void CMonsterBullet4::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"MonBullet3");

	GdiTransparentBlt
	(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),	//	2, 3인자 복사 받을 위치의 좌표를 전달
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		(int)m_tInfo.fCY,
		hMemDC,							// 비트맵 정보를 가지고 있는 DC
		0,								// 7,8인자 비트맵을 출력할 시작좌표
		0,
		16,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		16,
		RGB(255, 255, 255));
}

void CMonsterBullet4::Release(void)
{
}
