#include "stdafx.h"
#include "Include.h"
#include "Player.h"
#include "Bullet.h"
#include "Bomb.h"
//==
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "KeyMgr.h"
#include "BmpMgr.h"


CPlayer::CPlayer()
{
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
	}
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_SPACE))
	{
		if (m_dwTime + 128 < GetTickCount())
		{
			if (m_iPowUp == 1)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, CAbstractFactory<CBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY));
				if (m_dwTime + 10 < GetTickCount())
				{
					CSoundMgr::Get_Instance()->PlaySound(L"Laser_Sound.wav", CSoundMgr::BULLETSOUND, 0.4f);
				}
				
			}
			else if (m_iPowUp == 2)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, CAbstractFactory<CBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY));
				CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, CAbstractFactory<CBullet>::Create((float)m_tInfo.fX - 10, (float)m_tInfo.fY));
				if (m_dwTime + 10 < GetTickCount())
				{
					CSoundMgr::Get_Instance()->PlaySound(L"Laser_Sound.wav", CSoundMgr::BULLETSOUND, 0.4f);
				}
			}
			else if (m_iPowUp == 3)
			{
				CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, CAbstractFactory<CBullet>::Create((float)m_tInfo.fX, (float)m_tInfo.fY));
				CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, CAbstractFactory<CBullet>::Create((float)m_tInfo.fX - 10, (float)m_tInfo.fY));
				CObjMgr::Get_Instance()->Add_Object(OBJID::BULLET, CAbstractFactory<CBullet>::Create((float)m_tInfo.fX - 20, (float)m_tInfo.fY));
				CSoundMgr::Get_Instance()->PlaySound(L"Laser_Sound.wav", CSoundMgr::BULLETSOUND, 0.4f);
			}
			m_dwTime = GetTickCount();
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing('B'))
	{
		if (m_dwTime + 1024 < GetTickCount())
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Explosion.mp3", CSoundMgr::EFFECT, 0.5f);
			CObjMgr::Get_Instance()->Add_Object(OBJID::BOMB, CAbstractFactory<CBomb>::Create((float)m_tInfo.fX, (float)m_tInfo.fY));
			CObjMgr::Get_Instance()->Delete_ID(OBJID::MONSTER);
			CObjMgr::Get_Instance()->Delete_ID(OBJID::MONSTERBULLET);
			CObjMgr::Get_Instance()->Delete_ID(OBJID::MONSTERBULLET2);
			CObjMgr::Get_Instance()->Delete_ID(OBJID::MONSTERBULLET3);
			CObjMgr::Get_Instance()->Delete_ID(OBJID::MONSTERBULLET4);
			m_dwTime = GetTickCount();
		}
	}
}

void CPlayer::State_Change()
{
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 450.f;
	m_tInfo.fY = 800.f;
	m_tInfo.fCX = 75.f;
	m_tInfo.fCY = 75.f;

	m_fSpeed = 10.f;
	m_iPowUp = 1;
	m_iHp = 5;
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player.bmp", L"Player");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Stretch2.bmp", L"Stretch");

	/*m_ePreState = IDLE;
	m_eCurState = IDLE;*/

	m_tFrame.iFrameStart = 3;
	m_tFrame.iFrameEnd = 3;
	m_tFrame.iFrameScene = 0;
	m_tFrame.dwFrameSpeed = 75;
	m_tFrame.dwFrameTime = GetTickCount();
}

int CPlayer::Update(void)
{
	if (true == m_bDead)
	{
		if (m_iHp > 0)
		{
			//체력1깍고
			m_iHp -= 1;
			m_bDead = false;
		}
		else
		{
			CSoundMgr::Get_Instance()->PlaySound(L"Explosion.mp3", CSoundMgr::EFFECT, 0.5f);
			return OBJ_DEAD;
		}
	}
		

	Key_Input();
	Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update(void)
{
}

void CPlayer::Render(HDC hDC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(L"Player");
	HDC	hStretchDC = CBmpMgr::Get_Instance()->Find_Image(L"Stretch");

	if (m_bStretch)
	{
		GdiTransparentBlt(hDC,	//	복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left),	//	2, 3인자 복사 받을 위치의 좌표를 전달
			int(m_tRect.top),
			(int)m_tInfo.fCX,	//	4, 5인자 복사 받을 X,Y의 길이를 전달	
			(int)m_tInfo.fCY,
			hMemDC,				// 비트맵 정보를 가지고 있는 DC
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,	// 7,8인자 비트맵을 출력할 시작좌표
			m_tFrame.iFrameScene * (int)m_tInfo.fCY,
			75,				// 9, 10인자 비트맵의 X,Y의 길이를 전달
			75,
			RGB(0, 0, 0));// 제거하고자 하는 색상
	}
	else
	{
		StretchBlt(hStretchDC,	// 이미지를 출력할 위치 핸들
			0,					// 2, 3 : 이미지를 출력할 위치 x,y
			0,
			m_tInfo.fCX,		// 4, 5 : 출력할 이미지 사이즈
			m_tInfo.fCY,
			hMemDC,				// 이미지 핸들
			m_tFrame.iFrameStart * (int)m_tInfo.fCX,	// 가져올 이미지의 시작점 x,y좌표	
			m_tFrame.iFrameScene * (int)m_tInfo.fCY,
			-200,				// 원본이미지로부터 잘라낼 이미지의 너비와 높이값							
			200,
			(int)SRCCOPY);			// 원본값 그대로 출력
		GdiTransparentBlt(hDC,	//	복사 받을, 최종적으로 그림을 그릴 DC
			int(m_tRect.left),	//	2, 3인자 복사 받을 위치의 좌표를 전달
			int(m_tRect.top),
			(int)m_tInfo.fCX,	//	4, 5인자 복사 받을 X,Y의 길이를 전달	
			(int)m_tInfo.fCY,
			hStretchDC,			// 비트맵 정보를 가지고 있는 DC
			0,					// 7,8인자 비트맵을 출력할 시작좌표
			0,
			75,				// 9, 10인자 비트맵의 X,Y의 길이를 전달
			75,
			RGB(0, 0, 0));
	}
}

void CPlayer::Release(void)
{
}
