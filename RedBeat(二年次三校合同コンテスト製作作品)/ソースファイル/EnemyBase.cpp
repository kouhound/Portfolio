#include "EnemyBase.h"
#include"Game.h"
EnemyBase::EnemyBase()
	:m_trans{0.0f,0.0f,1.0f,1.0f,0.0f},n_life(3),m_pEnemy(nullptr),m_isDestroy(false)
{
	//継承先のクラスごとにテクスチャや頂点の位置が異なるためここではスプライト作成を行わない
}

EnemyBase::~EnemyBase()
{
	if (m_pEnemy != nullptr) {
		delete m_pEnemy;
	}
}

void EnemyBase::Update()
{
	//m_trans.posY++;
	//Transform Drawcopy = m_trans;
	//m_trans.posX = GetCamera()->GetCamX();
}

void EnemyBase::Draw()
{
	Transform Drawcopy = m_trans;
	Drawcopy.posX -= GetCamera()->GetCamX();
	m_pEnemy->Write(&Drawcopy,0);
	m_pEnemy->Draw();
}

bool EnemyBase::isDestroy()
{
	return m_isDestroy;
}

void EnemyBase::damage(int val)
{
	n_life -= val;
	if (n_life <= 0) {
		m_isDestroy = true;
	}
}

void EnemyBase::SetPos(float x, float y)
{
	m_trans.posX = x;
	m_trans.posY= y;
}

Transform EnemyBase::GetTrans()
{
	return m_trans;
}

float EnemyBase::getWidth()
{
	return m_sizeW;
}

float EnemyBase::getHeight()
{
	return m_sizeH;
}

void EnemyBase::CreateSprite(SpriteDesc desc)
{
	m_pEnemy = new Sprite(desc);
	//画像の大きさ
	m_sizeW = desc.pVtx[1].pos[0] - desc.pVtx[0].pos[0];
	m_sizeH= desc.pVtx[2].pos[1] - desc.pVtx[0].pos[1];
}