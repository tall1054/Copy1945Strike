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


	//�Ѿ� ��� Ƚ�� ������ ����
	

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
	(hDC,				//	���� ����, ���������� �׸��� �׸� DC
		int(m_tRect.left),	//	2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		int(m_tRect.top),
		(int)m_tInfo.fCX,				//	4, 5���� ���� ���� X,Y�� ���̸� ����	
		(int)m_tInfo.fCY,
		hMemDC,							// ��Ʈ�� ������ ������ �ִ� DC
		0,								// 7,8���� ��Ʈ���� ����� ������ǥ
		0,
		12,								// 9, 10���� ��Ʈ���� X,Y�� ���̸� ����
		12,
		RGB(255, 255, 255));
}

void CMonsterBullet::Release(void)
{
}
