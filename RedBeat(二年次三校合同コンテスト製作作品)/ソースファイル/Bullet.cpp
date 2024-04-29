#include "Bullet.h"
#include "Game.h"
//íËêî
const float BMargin = 50.0f;
const float BLIMIT_LEFT = 0.0f- BMargin;
const float BLIMIT_RIGHT = 960.0f+ BMargin;
const float BLIMIT_TOP = 0.0f- BMargin;
const float BLIMIT_BOTTOM = 540.0f+ BMargin;

Bullet::Bullet(SpriteDesc desc) :m_trans{ 0.0f,0.0f,1.0f,1.0f,0.0f },m_isDestoroy(false),m_moveX(0),m_moveY(0)

{
	Vertex vtx[] = {
	{{-70,-70,0.0f},{0.0f,0.0f} },
	{ {70,-70,0.0f},{1.0f,0.0f}},
	{ {-70, 70,0},{0.0f,1.0f}},
	{ {70,70,0},{1.0f,1.0f}}
	};
	desc.pVtx = vtx;
	desc.pTexture = "Assets/untitled.png";
	m_pSprite= new Sprite(desc);
	m_sizeW = vtx[1].pos[0] - vtx[0].pos[0];
	m_sizeH = vtx[2].pos[1] - vtx[0].pos[1];
};

Bullet::~Bullet()
{
	delete m_pSprite;
}

void Bullet::Update()
{

	//à⁄ìÆèàóù
	m_trans.posX += m_moveX;
	m_trans.posY += m_moveY;

	//m_trans.angle += 12.0f/180*3.14;
	if (m_trans.posX < BLIMIT_LEFT || m_trans.posX > BLIMIT_RIGHT /*|| m_trans.posY < BLIMIT_TOP*/ || m_trans.posY > BLIMIT_BOTTOM) 
	{ 
		m_isDestoroy = true;
	}
}

void Bullet::Draw()
{
	Transform Drawcopy = m_trans;
	Drawcopy.posX -= GetCamera()->GetCamX();
	m_pSprite->Write(&Drawcopy, 0);
	m_pSprite->Draw();
}

void Bullet::SetPos(float x, float y)
{
	m_trans.posX = x;
	m_trans.posY = y;
}

void Bullet::SetMove(float x, float y)
{
	m_moveX = x;
	m_moveY = y;
}

bool Bullet::isDestroy()
{
	return m_isDestoroy;
}

void Bullet::Destroy()
{
	m_isDestoroy= true;
}

Transform Bullet::GetTrans()
{
	return m_trans;
}

float Bullet::getWidth()
{
	return m_sizeW;
}

float Bullet::getHeight()
{
	return m_sizeH;
}
