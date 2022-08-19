#include "stdafx.h"
#include "BossBullet.h"

#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ObjMgr.h"


CBossBullet::CBossBullet()
{
}


CBossBullet::~CBossBullet()
{
	Release();
}

void CBossBullet::Initialize(void)
{
	m_tInfo.fCX = 90.f;
	m_tInfo.fCY = 90.f;

	m_fSpeed = 10.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossBullet_1_1.bmp", L"BossBullet1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossBullet_1_2.bmp", L"BossBullet2");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Boss/BossBullet_1_3.bmp", L"BossBullet3");

	m_eRenderGroup = RENDER_OBJ;
}

int CBossBullet::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	Late_Update();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CBossBullet::Late_Update(void)
{
	if ((0 >= m_tInfo.fY) || (WINCY <= m_tInfo.fY))
	{
		m_bDead = true;
	}
}

void CBossBullet::Render(HDC hDC)
{
	HDC	hBossBullet1DC = CBmpMgr::Get_Instance()->Find_Image(L"BossBullet1");
	HDC	hBossBullet2DC = CBmpMgr::Get_Instance()->Find_Image(L"BossBullet2");
	HDC	hBossBullet3DC = CBmpMgr::Get_Instance()->Find_Image(L"BossBullet3");


	GdiTransparentBlt
	(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),	//	2, 3인자 복사 받을 위치의 좌표를 전달
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		(int)m_tInfo.fCY,
		hBossBullet1DC,							// 비트맵 정보를 가지고 있는 DC
		0,								// 7,8인자 비트맵을 출력할 시작좌표
		0,
		90,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		90,
		RGB(255, 255, 255));

	GdiTransparentBlt
	(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),	//	2, 3인자 복사 받을 위치의 좌표를 전달
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		(int)m_tInfo.fCY,
		hBossBullet2DC,							// 비트맵 정보를 가지고 있는 DC
		0,								// 7,8인자 비트맵을 출력할 시작좌표
		0,
		90,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		90,
		RGB(255, 255, 255));

	GdiTransparentBlt
	(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),	//	2, 3인자 복사 받을 위치의 좌표를 전달
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		(int)m_tInfo.fCY,
		hBossBullet3DC,							// 비트맵 정보를 가지고 있는 DC
		0,								// 7,8인자 비트맵을 출력할 시작좌표
		0,
		90,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		90,
		RGB(255, 255, 255));
}

void CBossBullet::Release(void)
{
}