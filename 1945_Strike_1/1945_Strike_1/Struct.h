#pragma once

typedef struct tagInfo
{
	float		fX;	// ���� �׸����� �ϴ� ��ü�� ���� x
	float		fY; // ���� �׸����� �ϴ� ��ü�� ���� y
	float		fCX; // ���� ������
	float		fCY; // ���� ������
}INFO;

typedef	struct tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iFrameScene;	// ���

	DWORD	dwFrameSpeed;
	DWORD	dwFrameTime;

}FRAME;

class CDeleteObj
{
public:
	CDeleteObj() {}
	~CDeleteObj() {}

public:
	template<typename T>
	void operator()(T& Temp)
	{
		if (nullptr != Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

class CDeleteMap
{
public:
	CDeleteMap() {}
	~CDeleteMap() {}

public:
	template<typename T>
	void operator()(T& Temp)
	{
		if (nullptr != Temp.second)
		{
			delete Temp.second;
			Temp.second = nullptr;
		}
	}
};

class CTag_Finder
{
public:
	CTag_Finder(const TCHAR* pString)
		: m_pString(pString) {}

public:
	template<typename T>
	bool	operator()(T& Temp)
	{
		return !lstrcmp(m_pString, Temp.first);
	}

private:
	const TCHAR*		m_pString;
};

template<typename T>
void		Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

template<typename T>
bool CompareY(T Dest, T Sour)
{
	return Dest->Get_Info().fY < Sour->Get_Info().fY;
}
