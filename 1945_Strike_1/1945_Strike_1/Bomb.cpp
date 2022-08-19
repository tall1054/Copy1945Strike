#include "stdafx.h"
#include "Bomb.h"

#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

//비행기 출현으로 모든 몬스터와 그 총알을 제거하는 방법입니다. 
CBomb::CBomb()
{
}

CBomb::~CBomb()
{
}

void CBomb::Initialize(void)
{
	m_tInfo.fCX = 450.f;
	m_tInfo.fCY = 450.f;

	m_fSpeed = 10.f;

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bomb/Special_Attack_1.bmp", L"Bomb");

	m_eRenderGroup = RENDER_OBJ;
}

int CBomb::Update(void)
{
	m_tInfo.fY -= m_fSpeed;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CBomb::Late_Update(void)
{
	if (0 >= m_tRect.left ||
		WINCX <= m_tRect.right ||
		0 >= m_tRect.top ||
		WINCY <= m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CBomb::Render(HDC hDC)
{
	HDC	hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Bomb");

	GdiTransparentBlt
	(hDC,								//	복사 받을, 최종적으로 그림을 그릴 DC
		int(m_tRect.left),				//	2, 3인자 복사 받을 위치의 좌표를 전달
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5인자 복사 받을 X,Y의 길이를 전달	
		(int)m_tInfo.fCY,
		hMemDC,							// 비트맵 정보를 가지고 있는 DC
		0,								// 7,8인자 비트맵을 출력할 시작좌표
		0,
		450,							// 9, 10인자 비트맵의 X,Y의 길이를 전달
		450,
		RGB(255, 255, 255));
}

void CBomb::Release(void)
{
}
