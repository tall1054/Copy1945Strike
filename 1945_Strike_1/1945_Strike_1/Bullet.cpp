#include "stdafx.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ObjMgr.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 26.f;
	m_tInfo.fCY = 26.f;

	m_fSpeed = 15.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Bullet_Eg_b.bmp", L"Bullet1");
	
	m_tFrame.iFrameStart = 0;
	m_tFrame.iFrameEnd = 0;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 26;
	m_tFrame.dwFrameTime = GetTickCount();

	m_eRenderGroup = RENDER_OBJ;
}

int CBullet::Update(void)
{
	if (true == m_bDead)
	{
		--m_iHp;
		return OBJ_DEAD;
	}
		

	m_tInfo.fY -= m_fSpeed;


	Update_Rect();
	return 0;
}

void CBullet::Late_Update(void)
{
	if (0 >= m_tRect.left ||
		WINCX <= m_tRect.right ||
		0 >= m_tRect.top ||
		WINCY <= m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CBullet::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Bullet1");

	GdiTransparentBlt
	(hDC,				//	복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),	//	2, 3인자 복사 받을 위치의 좌표를 전달
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		(int)m_tInfo.fCY,
		hMemDC,							// 비트맵 정보를 가지고 있는 DC
		0,								// 7,8인자 비트맵을 출력할 시작좌표
		0,
		26,								// 9, 10인자 비트맵의 X,Y의 길이를 전달
		26,
		RGB(255, 255, 255));
}

void CBullet::Release(void)
{
}
