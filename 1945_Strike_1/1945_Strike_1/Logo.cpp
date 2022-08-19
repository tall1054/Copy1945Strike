#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

CLogo::CLogo()
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize(void)
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stage/Logo/menu.bmp", L"Logo");
	CSoundMgr::Get_Instance()->PlaySound(L"02 - In the name of Strikers.mp3", CSoundMgr::PLAYER, 0.5f);
}

int CLogo::Update(void)
{
	
	return 0;
}

void CLogo::Late_Update(void)
{
	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_RETURN))
	{
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER);
		CSceneMgr::Get_Instance()->Scene_Change(SCENE_STAGE);
		return;
	}
}

void CLogo::Render(HDC hDC)
{
	HDC	hLogoDC = CBmpMgr::Get_Instance()->Find_Image(L"Logo");

	BitBlt
	(hDC,
		0,
		0,
		WINCX,
		WINCY,
		hLogoDC,
		0,
		0,
		SRCCOPY);
}

void CLogo::Release(void)
{
}
