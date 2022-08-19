#include "stdafx.h"
#include "Bomb.h"

#include "AbstractFactory.h"
#include "BmpMgr.h"
#include "ObjMgr.h"

//����� �������� ��� ���Ϳ� �� �Ѿ��� �����ϴ� ����Դϴ�. 
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
	(hDC,								//	���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),				//	2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5���� ���� ���� X,Y�� ���̸� ����	
		(int)m_tInfo.fCY,
		hMemDC,							// ��Ʈ�� ������ ������ �ִ� DC
		0,								// 7,8���� ��Ʈ���� ����� ������ǥ
		0,
		450,							// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		450,
		RGB(255, 255, 255));
}

void CBomb::Release(void)
{
}
