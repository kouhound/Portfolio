#pragma once
#include"Sprite.h"

class RERSULT
{
public:
	RERSULT(SpriteDesc desc);
	~RERSULT();
	void Update(void);
	void Draw(void);
	void Change(bool);
private:
	int Animframe = 0;
	AnimeUV m_uv;
	int m_frame;
	Transform m_Trans;
	Sprite*m_pSprite;
};
