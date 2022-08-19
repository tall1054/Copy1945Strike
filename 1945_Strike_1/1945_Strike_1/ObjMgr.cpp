#include "stdafx.h"
#include "ObjMgr.h"
#include "Obj.h"

CObjMgr*	CObjMgr::m_pInstance = nullptr;

CObjMgr::CObjMgr()
	: m_iScore(0)
{
}


CObjMgr::~CObjMgr()
{
}

CObj * CObjMgr::Get_Target(OBJID::ID _eID, CObj * pObj)
{
	CObj*		pTarget = nullptr;

	float		fDistance = 0.f;

	for (auto& iter : m_ObjList[_eID])
	{
		float fWidth = iter->Get_Info().fX - pObj->Get_Info().fX;
		float fHeight = iter->Get_Info().fY - pObj->Get_Info().fY;

		float fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		if (fDistance > fDiagonal || !pTarget)
		{
			pTarget = iter;
			fDistance = fDiagonal;
		}
	}

	return pTarget;
}

void CObjMgr::Add_Object(OBJID::ID eID, CObj * pObj)
{
	m_ObjList[eID].push_back(pObj);
}

int CObjMgr::Update(void)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		auto& iter = m_ObjList[i].begin();
		for (; iter != m_ObjList[i].end(); )
		{
			int	iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				if (i == OBJID::MONSTER)
					m_iScore += 100;
				Safe_Delete(*iter);
				iter = m_ObjList[i].erase(iter);
			}
			else
				++iter;
		}
	}

	return 0;
	
}

void CObjMgr::Late_Update(void)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for (auto& iter : m_ObjList[i])
		{
			iter->Late_Update();

			if (m_ObjList[i].empty())
				break;

			RENDERID	eRender = iter->Get_RenderID();
			m_RenderSort[eRender].push_back(iter);		// 매 프레임마다 새로 렌더 그룹을 편성
		}
	}

	CCollisionMgr::Collision_Rect_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTERBULLET]);
	CCollisionMgr::Collision_Rect_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTERBULLET2]);
	CCollisionMgr::Collision_Rect_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTERBULLET3]);
	CCollisionMgr::Collision_Rect_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTERBULLET4]);
	CCollisionMgr::Collision_Rect_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::MONSTERBULLET5]);
	CCollisionMgr::Collision_Rect_Player(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::BOSSBULLET]);
	CCollisionMgr::Collision_Rect_Monster(m_ObjList[OBJID::MONSTER], m_ObjList[OBJID::BULLET]);
	CCollisionMgr::Collision_Rect_Monster(m_ObjList[OBJID::BOSS], m_ObjList[OBJID::BULLET]);
	CCollisionMgr::Collision_Rect_Power(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::POWER]);
	CCollisionMgr::Collision_Rect_IBomb(m_ObjList[OBJID::PLAYER], m_ObjList[OBJID::IBOMB]);
}

void CObjMgr::Render(HDC m_DC)
{
	for (int i = 0; i < RENDER_END; ++i)
	{
		m_RenderSort[i].sort(CompareY<CObj*>);

		for (auto& iter : m_RenderSort[i])
			iter->Render(m_DC);

		m_RenderSort[i].clear();		// 매 프레임마다 기존 그룹의 내용을 지워준다.
	}
}

void CObjMgr::Release(void)
{
	for (int i = 0; i < OBJID::END; ++i)
	{
		for_each(m_ObjList[i].begin(), m_ObjList[i].end(), CDeleteObj());
		m_ObjList[i].clear();
	}
}

void CObjMgr::Delete_ID(OBJID::ID eID)
{
	for (auto& iter : m_ObjList[eID])
		Safe_Delete(iter);

	m_ObjList[eID].clear();
}
