#pragma once
#include"Sprite.h"
class EnemyBase
{
public:
	EnemyBase();
	~EnemyBase();
	void Update();
	void Draw();
	bool isDestroy();
	void damage(int val);
	void SetPos(float x, float y);
	Transform GetTrans();
	float getWidth();
	float getHeight();
protected:
	AnimeUV m_uv;
	Transform m_trans;
	int n_life;

	void CreateSprite(SpriteDesc desk);
private :
	Sprite* m_pEnemy;
	float m_sizeW, m_sizeH;
	bool m_isDestroy;
};

