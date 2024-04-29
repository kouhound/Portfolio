#include "FPS.h"
#pragma comment(lib,"winmm.lib")
FPS::FPS()
{
	timeBeginPeriod(1);
	m_preTime = timeGetTime();
}
FPS::~FPS()
{

	timeEndPeriod(1);
}

bool FPS::Ischeck(void)
{
	DWORD nowTime = timeGetTime();
	if (nowTime - m_preTime >= 1000 /60)
	{
		m_preTime = nowTime;
			return true;
	}
	return false;
}

bool FPS::Ischeckms(void)
{
	DWORD nowTime2 = timeGetTime();
	if (nowTime2 - m_preTime2 >= 1 )
	{
		m_preTime2 = nowTime2;
		return true;
	}
	return false;
}