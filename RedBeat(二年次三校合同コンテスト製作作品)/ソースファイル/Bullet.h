#pragma once
#include "Sprite.h"
class Bullet
{
public:
	Bullet(SpriteDesc desc);
	~Bullet();
	void Update();
	void Draw();
	void SetPos(float x, float y);
	void SetMove(float x, float y);
	bool isDestroy();
	void Destroy();
	Transform GetTrans();
	float getWidth();
	float getHeight();
private:
	Sprite* m_pSprite;

	float m_sizeW, m_sizeH;
	
	Transform m_trans;
	//ãÖÇ…ä÷Ç∑ÇÈèÓïÒ
	bool m_isDestoroy;
	float m_moveX; int Animframe;
	float m_moveY;
};



