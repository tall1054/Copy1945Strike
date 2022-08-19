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
	(hDC,				//	���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),	//	2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5���� ���� ���� X,Y�� ���̸� ����	
		(int)m_tInfo.fCY,
		hMemDC,							// ��Ʈ�� ������ ������ �ִ� DC
		0,								// 7,8���� ��Ʈ���� ����� ������ǥ
		0,
		16,								// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		16,
		RGB(255, 255, 255));
}

void CMonsterBullet4::Release(void)
{
}
