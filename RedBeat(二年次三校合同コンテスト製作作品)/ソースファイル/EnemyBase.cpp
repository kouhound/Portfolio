#include "EnemyBase.h"
#include"Game.h"
EnemyBase::EnemyBase()
	:m_trans{0.0f,0.0f,1.0f,1.0f,0.0f},n_life(3),m_pEnemy(nullptr),m_isDestroy(false)
{
	//�p����̃N���X���ƂɃe�N�X�`���Ⓒ�_�̈ʒu���قȂ邽�߂����ł̓X�v���C�g�쐬���s��Ȃ�
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
	//�摜�̑傫��
	m_sizeW = desc.pVtx[1].pos[0] - desc.pVtx[0].pos[0];
	m_sizeH= desc.pVtx[2].pos[1] - desc.pVtx[0].pos[1];
}