#include "Result.h"

#include"Game.h"
//#include"BlendState.h"
//BlendState* m_pBlendState;

RERSULT::RERSULT(SpriteDesc desc)
	:m_frame(0)
{


	Vertex vtx[] =
	{
	{{0.0f,0.0f,0.0f},{0.0f,0.0f}},
	{{960.0f, 0.0f, 0.0f},{1.0f,0.0f} },
	{{ 0.0f, 1080.0f, 0.0f }, { 0.0f,1.0f }},
	{{960.0f, 1080.0f, 0.0f} ,{1.0f,1.0f}}
	};
	desc.pVtx = vtx;



	desc.pTexture = "Assets/Result.png";

	m_uv.uvW = 1.0f /*/ 10*/;
	m_uv.uvH = 1.0f;
	m_uv.uvLX = m_uv.uvW;
	m_uv.uvLY = 0.0f;

	m_Trans.posX = m_Trans.posY = 0.0f;
	m_Trans.scaleX = m_Trans.scaleY = 1.0f;
	m_Trans.angle = 0.0f;
	m_pSprite = new Sprite(desc);
}

RERSULT::~RERSULT()
{
	delete m_pSprite;

}


void RERSULT::Update(void)
{//画像を指定された位置までスクロールさせるなら
	//画像のUVは0~1、端から端まで移動するとなると
	//1.0/60
	Animframe++;

	//m_uv.uvLY = sin(Animframe *360.0f / 60 * 3.14f / 180) * 0.01 + 0;
	//m_uv.uvLX += cos(Animframe *360.0f / 60 * 3.14f / 180) * 0.01 + 0;
	m_uv.uvLX += 0.001f;
	m_uv.uvLY -= 0.003f;
	//if (m_uv.uvLX >= 1.0f- m_uv.uvW-0.001)
	//{
	//	m_uv.uvLX = m_uv.uvW;


	//}
//m_uv.uvLX = GetCamera()->GetCamX()*0.001;
	//フレームカウントのリセット

}
void RERSULT::Draw(void)
{

	m_pSprite->Write(&m_uv, 0);
	m_pSprite->Write(&m_Trans, 1);

	m_pSprite->Draw();
}
void RERSULT::Change(bool b)
{
	if (b == true) { m_uv.uvLY = 0; }
	else {
		m_uv.uvLY	= 0.5f;
	}
}