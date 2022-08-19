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

	//��� ä���� ����ϱ� ������ ä�� ���̵� �����ָ� �ȴ�
	//CSoundMgr::Get_Instance()->PlayBGM(L"Success.wav", 1.f);
	//���� �̸�(Ȯ���� �� ����)	, ü���̸� (���������� BGM�� �ǵ�������) ���� ũ�� (1�� �ִ�)
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

	BitBlt(hBackBufferDC,     //���� ����, ���������� �׸��� �׸� DC
		0,                    //2,3���� : ���� ���� ��ġ�� ��ǥ�� ����
		0,
		WINCX,                //4,5���� : ���� ���� X,Y�� ���̸� ����
		WINCY,
		hBackDC,               //��Ʈ�� ������ ������ �ִ� DC
		0,                    //7,8���� : ��Ʈ���� ����� ������ǥ
		0,
		SRCCOPY);

	//�Ÿ޴������� ����۸� �ν��Ͻ�ȭ
	CSceneMgr::Get_Instance()->Render(hBackBufferDC);

	BitBlt(m_DC,		//���� ����, ���������� �׸��� �׸� DC
		0,              //2,3���� : ���� ���� ��ġ�� ��ǥ�� ����
		0,
		WINCX,          //4,5���� : ���� ���� X,Y�� ���̸� ����
		WINCY,
		hBackBufferDC,  //��Ʈ�� ������ ������ �ִ� DC
		0,              //7,8���� : ��Ʈ���� ����� ������ǥ
		0,
		SRCCOPY);

	BitBlt(hBackDC,	//���� ����, ���������� �׸��� �׸� DC
		0,					//2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		0,
		900,				//4,5���� ���� ���� X,Y�� ���̸� ����
		8030,
		hMapDC,				//��Ʈ�� ������ ������ �ִ� DC
		0,					//7,8���� ��Ʈ���� ����� ������ǥ
		7130,
		SRCCOPY);

	HDC		hBackUIDC = CBmpMgr::Get_Instance()->Find_Image(L"HP");
	HDC		hUIDC = CBmpMgr::Get_Instance()->Find_Image(L"Bar");
	//HDC		hScoreDC = CBmpMgr::Get_Instance()->Find_Image(L"Number");
	
	CSceneMgr::Get_Instance()->Render(hBackBufferDC);

	//UIü�¹�
	GdiTransparentBlt
	(m_DC,					//���� ����, ���������� �׸��� �׸� DC
		0,					//2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		0,
		80,					//4,5���� ���� ���� X,Y�� ���̸� ����
		11,
		hBackUIDC,			//��Ʈ�� ������ ������ �ִ� DC
		0,					//7,8���� ��Ʈ���� ����� ������ǥ
		0,
		80,
		11,
		RGB(255, 255, 255));

	//UI
	GdiTransparentBlt
	(m_DC,					//���� ����, ���������� �׸��� �׸� DC
		0,					//2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
		0,
		80,					//4,5���� ���� ���� X,Y�� ���̸� ����
		11,
		hUIDC,				//��Ʈ�� ������ ������ �ִ� DC
		0,					//7,8���� ��Ʈ���� ����� ������ǥ
		0,
		80,
		11,
		RGB(255, 255, 255));

	//����
	//GdiTransparentBlt
	//(m_DC,					//���� ����, ���������� �׸��� �׸� DC
	//	450,					//2, 3���� ���� ���� ��ġ�� ��ǥ�� ����
	//	0,
	//	50,					//4,5���� ���� ���� X,Y�� ���̸� ����
	//	70,
	//	hScoreDC,				//��Ʈ�� ������ ������ �ִ� DC
	//	0,					//7,8���� ��Ʈ���� ����� ������ǥ
	//	0,
	//	50,
	//	70,
	//	RGB(255, 255, 255));

	/*m_iScore = * 10;*/

	//�������� ����		extern�� define����� ������ �Ǹ���ΰ���, ������ â cpp���Ͽ��� �ְų� �ٸ� ����� ����ϸ� �ȴ�.
	//���ΰ��� 
	//��ü ������ ���ھ� �ø���

	//m_iScore += CObjMgr::Update;

	TCHAR	szTemp[256] = L"";
	swprintf_s(szTemp, L"Score : %d", g_iScore);
	TextOut(m_DC, 450, 0, szTemp, lstrlen(szTemp));

	static int nY = 8030 - WINCY;

	if (nY < 0)
	{
		//�ڿ� ��ѷ��ִ� ģ��(����� ����ۿ� ���翡 ���ִ� ��)
		BitBlt(hBackDC,	//���� ����, ���������� �׸��� �׸� DC
			0,					//2,3���� : ���� ���� ��ġ�� ��ǥ�� ����
			-nY,				//��Ű��,������
			900,				//4,5���� : ���� ���� X,Y�� ���̸� ����
			8030 + nY,
			hMapDC,				//��Ʈ�� ������ ������ �ִ� DC
			0,					//7,8���� : ��Ʈ���� ����� ������ǥ
			0,
			SRCCOPY);

		BitBlt(hBackDC,			//���� ����, ���������� �׸��� �׸� DC
			0,					//2,3���� : ���� ���� ��ġ�� ��ǥ�� ����
			0,
			900,				//4,5���� : ���� ���� X,Y�� ���̸� ����
			-nY,
			hMapDC,		//��Ʈ�� ������ ������ �ִ� DC
			0,					//7,8���� : ��Ʈ���� ����� ������ǥ
			8030 + nY,
			SRCCOPY);
	}
	else
	{
		BitBlt(hBackDC,	//���� ����, ���������� �׸��� �׸� DC
			0,					//2,3���� : ���� ���� ��ġ�� ��ǥ�� ����
			0,
			900,				//4,5���� : ���� ���� X,Y�� ���̸� ����
			8030,
			hMapDC,				//��Ʈ�� ������ ������ �ִ� DC
			0,					//7,8���� ��Ʈ���� ����� ������ǥ
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
