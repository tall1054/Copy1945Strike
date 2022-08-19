#include "stdafx.h"
#include "MainGame.h"
#include "Include.h"
#include "Bullet.h"
#include "AbstractFactory.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "BmpMgr.h"


CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize(void)
{
	m_DC = GetDC(g_hWnd);

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackBuffer/BackBuffer.bmp", L"BackBuffer");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackBuffer/Back.bmp", L"Back");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Stage_B.bmp", L"Stage");
	/*CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Inter_Hp.bmp", L"HP");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Inter_HpBar.bmp", L"Bar");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/Inter_Number_1.bmp", L"Number");*/

	CSceneMgr::Get_Instance()->Scene_Change(SCENE_LOGO);

	//브금 채널을 사용하기 때문에 채널 아이디만 지워주면 된다
	//CSoundMgr::Get_Instance()->PlayBGM(L"Success.wav", 1.f);
	//파일 이름(확장자 명 포함)	, 체널이름 (주의할점은 BGM은 건들지말자) 사운드 크기 (1이 최대)
	//CSoundMgr::Get_Instance()->PlaySound(L"02 - In the name of Strikers.mp3", CSoundMgr::PLAYER, 0.5f);
}

void CMainGame::Update(void)
{
	CObjMgr::Get_Instance()->Update();
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update(void)
{
	CObjMgr::Get_Instance()->Late_Update();
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render(void)
{
	HDC		hBackBufferDC = CBmpMgr::Get_Instance()->Find_Image(L"BackBuffer");
	HDC		hBackDC = CBmpMgr::Get_Instance()->Find_Image(L"Back");
	HDC		hMapDC = CBmpMgr::Get_Instance()->Find_Image(L"Stage");

	BitBlt(hBackBufferDC,     //복사 받을, 최종적으로 그림을 그릴 DC
		0,                    //2,3인자 : 복사 받을 위치의 좌표를 전달
		0,
		WINCX,                //4,5인자 : 복사 받을 X,Y의 길이를 전달
		WINCY,
		hBackDC,               //비트맵 정보를 가지고 있는 DC
		0,                    //7,8인자 : 비트맵을 출력할 시작좌표
		0,
		SRCCOPY);

	//신메니저에서 백버퍼를 인스턴스화
	CSceneMgr::Get_Instance()->Render(hBackBufferDC);

	BitBlt(m_DC,		//복사 받을, 최종적으로 그림을 그릴 DC
		0,              //2,3인자 : 복사 받을 위치의 좌표를 전달
		0,
		WINCX,          //4,5인자 : 복사 받을 X,Y의 길이를 전달
		WINCY,
		hBackBufferDC,  //비트맵 정보를 가지고 있는 DC
		0,              //7,8인자 : 비트맵을 출력할 시작좌표
		0,
		SRCCOPY);

	BitBlt(hBackDC,	//복사 받을, 최종적으로 그림을 그릴 DC
		0,					//2, 3인자 복사 받을 위치의 좌표를 전달
		0,
		900,				//4,5인자 복사 받을 X,Y의 길이를 전달
		8030,
		hMapDC,				//비트맵 정보를 가지고 있는 DC
		0,					//7,8인자 비트맵을 출력할 시작좌표
		7130,
		SRCCOPY);

	HDC		hBackUIDC = CBmpMgr::Get_Instance()->Find_Image(L"HP");
	HDC		hUIDC = CBmpMgr::Get_Instance()->Find_Image(L"Bar");
	//HDC		hScoreDC = CBmpMgr::Get_Instance()->Find_Image(L"Number");
	
	CSceneMgr::Get_Instance()->Render(hBackBufferDC);

	//UI체력바
	GdiTransparentBlt
	(m_DC,					//복사 받을, 최종적으로 그림을 그릴 DC
		0,					//2, 3인자 복사 받을 위치의 좌표를 전달
		0,
		80,					//4,5인자 복사 받을 X,Y의 길이를 전달
		11,
		hBackUIDC,			//비트맵 정보를 가지고 있는 DC
		0,					//7,8인자 비트맵을 출력할 시작좌표
		0,
		80,
		11,
		RGB(255, 255, 255));

	//UI
	GdiTransparentBlt
	(m_DC,					//복사 받을, 최종적으로 그림을 그릴 DC
		0,					//2, 3인자 복사 받을 위치의 좌표를 전달
		0,
		80,					//4,5인자 복사 받을 X,Y의 길이를 전달
		11,
		hUIDC,				//비트맵 정보를 가지고 있는 DC
		0,					//7,8인자 비트맵을 출력할 시작좌표
		0,
		80,
		11,
		RGB(255, 255, 255));

	//점수
	//GdiTransparentBlt
	//(m_DC,					//복사 받을, 최종적으로 그림을 그릴 DC
	//	450,					//2, 3인자 복사 받을 위치의 좌표를 전달
	//	0,
	//	50,					//4,5인자 복사 받을 X,Y의 길이를 전달
	//	70,
	//	hScoreDC,				//비트맵 정보를 가지고 있는 DC
	//	0,					//7,8인자 비트맵을 출력할 시작좌표
	//	0,
	//	50,
	//	70,
	//	RGB(255, 255, 255));

	/*m_iScore = * 10;*/

	//전역변수 선언		extern은 define헤더에 넣으면 되며메인게임, 윈도우 창 cpp파일에서 넣거나 다른 방법을 사용하면 된다.
	//메인게임 
	//객체 죽을떄 스코어 올리기

	//m_iScore += CObjMgr::Update;

	TCHAR	szTemp[256] = L"";
	swprintf_s(szTemp, L"Score : %d", g_iScore);
	TextOut(m_DC, 450, 0, szTemp, lstrlen(szTemp));

	static int nY = 8030 - WINCY;

	if (nY < 0)
	{
		//뒤에 흩뿌려주는 친구(배경을 백버퍼에 복사에 해주는 거)
		BitBlt(hBackDC,	//복사 받을, 최종적으로 그림을 그릴 DC
			0,					//2,3인자 : 복사 받을 위치의 좌표를 전달
			-nY,				//락키고,오프셋
			900,				//4,5인자 : 복사 받을 X,Y의 길이를 전달
			8030 + nY,
			hMapDC,				//비트맵 정보를 가지고 있는 DC
			0,					//7,8인자 : 비트맵을 출력할 시작좌표
			0,
			SRCCOPY);

		BitBlt(hBackDC,			//복사 받을, 최종적으로 그림을 그릴 DC
			0,					//2,3인자 : 복사 받을 위치의 좌표를 전달
			0,
			900,				//4,5인자 : 복사 받을 X,Y의 길이를 전달
			-nY,
			hMapDC,		//비트맵 정보를 가지고 있는 DC
			0,					//7,8인자 : 비트맵을 출력할 시작좌표
			8030 + nY,
			SRCCOPY);
	}
	else
	{
		BitBlt(hBackDC,	//복사 받을, 최종적으로 그림을 그릴 DC
			0,					//2,3인자 : 복사 받을 위치의 좌표를 전달
			0,
			900,				//4,5인자 : 복사 받을 X,Y의 길이를 전달
			8030,
			hMapDC,				//비트맵 정보를 가지고 있는 DC
			0,					//7,8인자 비트맵을 출력할 시작좌표
			nY,
			SRCCOPY);
	}
	nY -= 3;

	if (nY + 8030 <= 0)
		nY = 8030;

	CObjMgr::Get_Instance()->Render(m_DC);

}

void CMainGame::Release(void)
{
	ReleaseDC(g_hWnd, m_DC);

	CSceneMgr::Get_Instance()->Destroy_Intance();
	CBmpMgr::Get_Instance()->Destroy_Intance();
	CKeyMgr::Get_Instance()->Destroy_Intance();
	CObjMgr::Get_Instance()->Destroy_Intance();
	CSoundMgr::Get_Instance()->Destroy_Instance();
}
