#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}
//�÷��̾�� �Ѿ�
void CCollisionMgr::Collision_Rect_Player(list<CObj*> _Dest, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Src->Get_Rect())))
			{
				Dest->Set_Dead();//�÷��̾�
				Src->Set_Dead(); //�Ѿ�
			}
		}
	}
}
//�Ѿ˰� �÷��̾�
void CCollisionMgr::Collision_Rect_Monster(list<CObj*> _Dest, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Src->Get_Rect())))
			{
				Dest->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dest, list<CObj*> _Src)
{
	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			float	fWidth = 0.f, fHeight = 0.f;

			if (Check_Rect(Dest, Src, &fWidth, &fHeight))
			{
				// �� �� �浹
				if (fWidth > fHeight)
				{
					if (Dest->Get_Info().fY < Src->Get_Info().fY)
					{
						Src->Set_PosY(fHeight);
					}
					else
						Src->Set_PosY(-fHeight);
				}

				//  �� �� �浹
				else
				{
					if (Dest->Get_Info().fX < Src->Get_Info().fX)
					{
						Src->Set_PosX(fWidth);
					}
					else
						Src->Set_PosX(-fWidth);
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (Check_Sphere(Dest, Src))
			{
				Dest->Set_Dead();
				Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_Rect_Power(list<CObj*> _Dest, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Src->Get_Rect())))
			{
				Dest->Set_PowUp(2);//�÷��̾� �� ���� ��� �Ŀ����̵� ��ź ���̵� �����ָ� �ȴ�.
				Src->Set_Dead(); //�Ŀ�
			}
		}
	}
}

void CCollisionMgr::Collision_Rect_IBomb(list<CObj*> _Dest, list<CObj*> _Src)
{
	RECT	rc{};

	for (auto& Dest : _Dest)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, &(Dest->Get_Rect()), &(Src->Get_Rect())))
			{
				//Dest->Set_BombUp(2);//�÷��̾� �� ���� ��� �Ŀ����̵� ��ź ���̵� �����ָ� �ȴ�.
				Src->Set_Dead(); //�Ŀ�
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj * pDest, CObj * pSrc)
{
	float		fWidth = abs(pDest->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = abs(pDest->Get_Info().fY - pSrc->Get_Info().fY);

	float		fDistance = sqrtf(fWidth * fWidth + fHeight * fHeight);

	float		fRadius = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;

	return fRadius > fDistance; // �浹
}

bool CCollisionMgr::Check_Rect(CObj * pDest, CObj * pSrc, float * _pWidth, float * _pHeight)
{
	float		fWidth = abs(pDest->Get_Info().fX - pSrc->Get_Info().fX);
	float		fHeight = abs(pDest->Get_Info().fY - pSrc->Get_Info().fY);

	float		fCX = (pDest->Get_Info().fCX + pSrc->Get_Info().fCX) * 0.5f;
	float		fCY = (pDest->Get_Info().fCY + pSrc->Get_Info().fCY) * 0.5f;

	if (fCX > fWidth && fCY > fHeight)
	{
		*_pWidth = fCX - fWidth;
		*_pHeight = fCY - fHeight;

		return true;
	}

	return false;
}
