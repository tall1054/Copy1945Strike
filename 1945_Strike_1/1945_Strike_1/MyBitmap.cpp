#include "stdafx.h"
#include "MyBitmap.h"


CMyBitmap::CMyBitmap()
{
}


CMyBitmap::~CMyBitmap()
{
}

void CMyBitmap::Load_Bmp(const TCHAR * pFilePath)
{
	HDC			hDC = GetDC(g_hWnd);

	// hDC ȣȯ�Ǵ� dc�� �Ҵ��ϴ� �Լ�
	m_hMemDC = CreateCompatibleDC(hDC);

	ReleaseDC(g_hWnd, hDC);

	// ��ηκ��� �̹��� ������ �о���̴� �Լ�
	m_hBitBmp = (HBITMAP)LoadImage(NULL,		// �ν��Ͻ�Ʒ �ڵ�, ���Ϸκ��� �о���̱� ������ NULL
		pFilePath,		// ������ ���
		IMAGE_BITMAP,	// � Ÿ���� �о���� �����ϴ� �÷���
		0,				//	���� ������ 
		0,				//  ���� ������(������ �̹��� ������ �״�� �о���� ���̱� ������ ���� ����� ������ �ʿ䰡 ����)
		LR_LOADFROMFILE | LR_CREATEDIBSECTION); //LR_LOADFROMFILE : ���Ͽ��� �̹����� �ҷ����� | �о�� ������ DIBSECTION���·� ��ȯ

	if (nullptr == m_hBitBmp)
	{
		MessageBox(g_hWnd, L"�ε� ����", L"����", MB_OK);
		return;
	}
	// �غ��� DC�� GDI ������Ʈ�� �ҷ��� ��Ʈ���� �����ϱ� ���� ����ϴ� �Լ�
	// SelectObject GDI ������Ʈ�� �����ϱ� ���� ������ ������ �ִ� ������Ʈ�� ��ȯ
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitBmp);
}

void CMyBitmap::Release(void)
{
	SelectObject(m_hMemDC, m_hOldBmp);

	// ���� dc�� ���õ� gdi ������Ʈ�� ������ �� ����.
	// ���� ����ϰ� �ִ� ��ü�� �Ժη� �����ϵ��� ������ �� �� ���� ������ ���� ���� ��ġ ������ �ϴ� ����
	// �����ϱ� ���� ������ ����ϴ� gdi ������Ʈ�� ��ü�ϰ�, ������ ����

	DeleteObject(m_hBitBmp);
	DeleteDC(m_hMemDC);
}
