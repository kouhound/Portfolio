#pragma once
#include "DirectX.h"
#include"Camera.h"
#include"HUMEN1.h"
#include"Effect.h"
typedef struct
{
	float centerX;
	float centerY;
	float Width;
	float Height;

}POS; 

const int BULLET_NUM = 300;
void UpdateCollision(int n);
HRESULT initgame(void);
void uninitgame(void);
void updategame(void);
void drawgame(void);
CAMERA* GetCamera();
void bulletshot(Float_3);
void Createeffect(Transform Trans, const char* pTex, Effect::Desc effect);
DWORD Getnow(void);
void UpdateTime(DWORD now);