#pragma once

#include "Player.h"
#include "Monster.h"
#include "Bullet.h"

#include "KeyMgr.h"
#include "SceneMgr.h"



class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize(void);
	void		Update(void);
	void		Late_Update(void);
	void		Render(void);
	void		Release(void);

private:
	HDC			m_DC;
	DWORD		m_dwTime;
};

