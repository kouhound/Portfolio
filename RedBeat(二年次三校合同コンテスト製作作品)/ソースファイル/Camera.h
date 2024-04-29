#pragma once
#include"Player.h"
class CAMERA
{
public:
	CAMERA(Player*player);
	~CAMERA();
	void Update();
	float GetCamX();
	float GetcamY();
private:
	float mPosX;
	float mPosY;
	Player* m_pPlayer;
};

