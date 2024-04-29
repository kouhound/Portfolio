#include "Camera.h"

CAMERA::CAMERA(Player* player):m_pPlayer(player),mPosX(0.0f),mPosY(0.0f)
{
	
}

CAMERA::~CAMERA()
{
}

void CAMERA::Update()
{
	//mPosX = m_pPlayer->Gettrans().posX;
	//mPosY= m_pPlayer->Gettrans().posY;
}

float CAMERA::GetCamX()
{
	return mPosX;
}

float CAMERA::GetcamY()
{
	return mPosY;
}
