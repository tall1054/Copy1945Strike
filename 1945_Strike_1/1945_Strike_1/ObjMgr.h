#pragma once

#include "Include.h"
#include "CollisionMgr.h"

class CObj;
class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();

public:
	CObj*		Get_Target(OBJID::ID _eID, CObj* pObj);

public:
	void		Add_Object(OBJID::ID eID, CObj* pObj);
	int			Update(void);
	void		Late_Update(void);
	void		Render(HDC m_DC);
	void		Release(void);
	void		Delete_ID(OBJID::ID eID);

private:
	list<CObj*>		m_ObjList[OBJID::END];
	list<CObj*>		m_RenderSort[RENDER_END];

private:
	int			m_iScore;

public:
	static	CObjMgr*		Get_Instance(void)
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CObjMgr;

		return m_pInstance;
	}

	static	void		Destroy_Intance(void)
	{
		if (nullptr != m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}

private:
	static CObjMgr*			m_pInstance;
};

