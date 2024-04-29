#include"Player.h"
#include "Keyboard.h"
#include"Game.h"
#include"Bullet.h"
//#include"BlendState.h"
//BlendState* m_pBlendState;
const float LIMIT_LEFT = 0.0f;
const float LIMIT_RIGHT = 960.0f;
const float LIMIT_TOP = 000.0f;
const float LIMIT_BOTTOM = 540.0f;

Player::Player(SpriteDesc desc)
	:m_frame(0),Animframe(0)
{


	Vertex vtx[] =
	{
	{{0.0f,0.0f,0.0f},{0.0f,0.0f}},
	{{960.0f, 0.0f, 0.0f},{1.0f,0.0f} },
	{{ 0.0f, 540.0f, 0.0f }, { 0.0f,1.0f }},
	{{960.0f, 540.0f, 0.0f} ,{1.0f,1.0f}}
	/*{{20.0f,320.0f,0.0f},{0.0f,0.0f}},
	{{195.0f,320.0f, 0.0f},{1.0f,0.0f} },
	{{ 20.0f, 495.0f, 0.0f }, { 0.0f,1.0f }},
	{{195.0f, 495.0f, 0.0f} ,{1.0f,1.0f}}*/
	};
	desc.pVtx = vtx;



	desc.pTexture= "Assets/hantei.png";

	m_uv.uvW = 1.0f ;
	m_uv.uvH = 1.0f;
	m_uv.uvLX = m_uv.uvW;
	m_uv.uvLY = 0.0f;
	//ポリゴン変形用データ
	m_Trans.posX = m_Trans.posY = 0.0f;
	m_Trans.scaleX = m_Trans.scaleY = 1.0f;
	m_Trans.angle = 0.0f;
	//スプライト生成
	m_pSprite = new Sprite(desc);
	//m_Trans.posX = 480.0f;
	//m_Trans.posY = 500.0f;
}

Player::~Player()
{
	delete m_pSprite;

}


void Player::UpdatePlayer(void)
{//数フレーム待ってから次の画像
	//m_Trans.angle += 0.01;
	//const float MOVE_SPEED_X = 15.0f;
	//const float MOVE_SPEED_XY = 0.05f;
	//const float MOVE_SPEED_Y = 2.0f;
	//if (IsKeyPress('A')) { m_Trans.posX -= MOVE_SPEED_X; }
	/*if (IsKeyPress(VK_GAMEPAD_DPAD_LEFT)) { m_Trans.posX -= MOVE_SPEED_X; }*/
	//if (IsKeyPress('D')) { m_Trans.posX += MOVE_SPEED_X; }
	//if (IsKeyPress('W')) { m_Trans.posX += MOVE_SPEED_XY; m_Trans.posY -= MOVE_SPEED_Y;}
	//if (IsKeyPress('S')) { m_Trans.posX -= MOVE_SPEED_XY; m_Trans.posY += MOVE_SPEED_Y;}






	if (IsKeyTrigger('D'))
	{
		UpdateCollision(1);
	}
	if (IsKeyTrigger('F'))
	{
		UpdateCollision(2);
	}
	if (IsKeyTrigger('J'))
	{
		UpdateCollision(3);
	}
	if (IsKeyTrigger('K'))
	{
		UpdateCollision(4);
	}
	
	//if (m_Trans.posX < LIMIT_LEFT) { m_Trans.posX = LIMIT_LEFT; }
	//if (m_Trans.posX > LIMIT_RIGHT) { m_Trans.posX = LIMIT_RIGHT; }
	//if (m_Trans.posY < LIMIT_TOP) { m_Trans.posY = LIMIT_TOP; }
	//if (m_Trans.posY > LIMIT_BOTTOM) { m_Trans.posY = LIMIT_BOTTOM; }
	//float scale = (m_Trans.posY - LIMIT_TOP) / (LIMIT_BOTTOM - LIMIT_TOP)*0.2f + 0.9f;
	//
	//m_Trans.scaleX = scale;
	//m_Trans.scaleY = scale;
	//if (m_frame >= 12)
	//{
	//	
	//	m_uv.uvLX += m_uv.uvW;
	//	if (m_uv.uvLX >= 0.5f) 
	//	{
	//		m_uv.uvLX = 0.0f;
	//		//m_uv.uvLY += m_uv.uvH;
	//		//if (m_uv.uvLY >= 1.0f) 
	//		//{
	//		//	m_uv.uvLY = 0.0f;
	//		//}
	//	
	//	}
	//	
	//	//フレームカウントのリセット
	//	m_frame = 0;
	//}
	//m_frame++;
	//Animframe++;

	//	m_Trans.angle = sin(Animframe *360.0f / 180 *
	//3.14f / 180) *10*3.14f/180 ;

	//	m_Trans.posY = sin(Animframe *360.0f / 60 * 3.14f / 180) * 50 + 0;
	//float rad = Animframe * 360.0f / 120* 3.14 / 180;
	//m_Trans.scaleX = (sin(rad)*0.5f + 0.5f) * 0.3+ 1;
	//m_Trans.scaleY = (sin(rad + 3.14)*0.5f + 0.5f) * 0.3 +1;
}
void Player::Draw(void)
{
	Transform Drawcopy = m_Trans;
	//Drawcopy.posX -= GetCamera()->GetCamX();
	//定数バッファの更新
	m_pSprite->Write(&m_uv, 0);
	m_pSprite->Write(&m_Trans, 1);
	//描画
	m_pSprite->Draw();

}

bool Player::isShot()
{
	//キー入力を調べた結果を判定にする
	return false;
	//return (IsKeyTrigger(VK_SPACE));
	//return (IsKeyPress(VK_SPACE));
}

Transform Player::Gettrans()
{
	return m_Trans;
}
