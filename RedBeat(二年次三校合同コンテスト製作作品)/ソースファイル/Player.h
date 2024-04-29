#pragma once

#include"Sprite.h"

class Player
{
public:
	Player(SpriteDesc desc);
	~Player();
	void UpdatePlayer(void);
	void Draw(void);
	bool isShot();
	Transform  Gettrans();
private:


	AnimeUV m_uv;
	int m_frame;
	Transform m_Trans;
	int Animframe;
	Sprite*m_pSprite;
};
