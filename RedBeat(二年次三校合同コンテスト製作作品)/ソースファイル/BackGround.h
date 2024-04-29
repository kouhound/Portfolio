#pragma once
#include"Sprite.h"

class BG
{
public:
	BG(SpriteDesc desc);
	~BG();
	void UpdateBG(void);
	void Draw(void);
	void UpperBG(int);
	bool checkbg();
private:
	int Animframe=0;
	AnimeUV m_uv;
	int m_frame;
	Transform m_Trans;
	Sprite*m_pSprite;
};
