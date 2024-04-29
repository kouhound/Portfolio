#pragma once
#include<Windows.h>

class FPS
{
public:
	FPS();
	~FPS();
	bool Ischeck(void);
	bool Ischeckms(void);
private:
	DWORD m_preTime;
	DWORD m_preTime2;
};