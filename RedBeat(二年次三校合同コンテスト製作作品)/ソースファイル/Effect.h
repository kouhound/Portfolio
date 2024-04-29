#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "Sprite.h"

class Effect
{
public:
	struct Param
	{
		float speed;
		float accele;
	};
	struct Desc
	{
		float lifeTime;
		Param moveX;
		Param moveY;
		Param rotate;
		Param scaleX;
		Param scaleY;
	};
public:
	Effect(SpriteDesc desc, Transform trans, Desc effect);
	~Effect();

	void Update();
	void Draw();

	bool IsDestroy();

private:
	Sprite* m_pSprite;
	Transform m_transform;
	Desc m_desc;
	bool m_isDestroy;
};

#endif // __EFFECT_H__