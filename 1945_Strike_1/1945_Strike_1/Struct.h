#pragma once

typedef struct tagInfo
{
	float		fX;	// 내가 그리고자 하는 물체의 중점 x
	float		fY; // 내가 그리고자 하는 물체의 중점 y
	float		fCX; // 가로 사이즈
	float		fCY; // 세로 사이즈
}INFO;

typedef	struct tagFrame
{
	int		iFrameStart;
	int		iFrameEnd;
	int		iFrameScene;	// 모션

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
