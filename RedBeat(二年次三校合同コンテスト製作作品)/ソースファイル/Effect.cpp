#include "Effect.h"
#include "Game.h"

Effect::Effect(SpriteDesc desc, Transform trans, Desc effect)
	: m_transform(trans)
	, m_desc(effect)
	, m_isDestroy(false)
{
	Vertex vtx[] = {
		{{-50,-50, 0}, {0,0}},
		{{ 50,-50, 0}, {1,0}},
		{{-50, 50, 0}, {0,1}},
		{{ 50, 50, 0}, {1,1}},
	};
	desc.pVtx = vtx;
	m_pSprite = new Sprite(desc);
}
Effect::~Effect()
{
	delete m_pSprite;
}
void Effect::Update()
{
	m_desc.lifeTime -= 1.0f / 60.0f;
	if (m_desc.lifeTime <= 0.0f)
	{
		m_isDestroy = true;
	}
	else
	{
		m_desc.moveX.speed += m_desc.moveX.accele;
		m_desc.moveY.speed += m_desc.moveY.accele;
		m_desc.rotate.speed += m_desc.rotate.accele;
		m_desc.scaleX.speed += m_desc.scaleX.accele;
		m_desc.scaleY.speed += m_desc.scaleY.accele;
		
		
	}
}
void Effect::Draw()
{
	m_transform.posX += m_desc.moveX.speed;
	m_transform.posY += m_desc.moveY.speed;
	m_transform.angle += m_desc.rotate.speed;
	m_transform.scaleX += m_desc.scaleX.speed;
	m_transform.scaleY += m_desc.scaleY.speed;

	Transform Drawcopy = m_transform;
	Drawcopy.posX -= GetCamera()->GetCamX();
	m_pSprite->Write(&Drawcopy, 0);
	m_pSprite->Draw();
}
bool Effect::IsDestroy()
{
	return m_isDestroy;
}