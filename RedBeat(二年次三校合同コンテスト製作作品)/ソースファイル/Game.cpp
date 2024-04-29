#include"Game.h"
#include"VertexBuffer.h"
#include "Shader.h"
#include"DirectXTex/TextureLoad.h"
#include"BlendState.h"
#include"SamplerState.h"
#include"Player.h"
#include"BackGround.h"
#include "Bullet.h"
#include "Notes.h"
#include "Camera.h"
#include"Effect.h"
#include"Sound.h"
#include"DebugPrint.h"
#include"Result.h"
#include "Geometory.h"
#include"Keyboard.h"
#include"Scene.h"
//#include "HUMEN1.h"
int Checkframe = 5400;
bool Result;
const int BULLET_NOTE =5;
const int EFFECTNUM = 100;
POS pos;
DWORD nowtime;
RERSULT* result;
Player* g_pPlayer;
BG* g_BG;
Bullet* g_pBullet[BULLET_NUM];
Notes* g_pEnemy[BULLET_NOTE];
Effect* g_pEffect[EFFECTNUM];
VertexShader* g_pPolygon;
VertexShader* g_pVs;
VertexShader* g_pAnimVs;
VertexShader* g_pTransVs;
PixelShader* g_pPs;
PixelShader* g_pNPPs;
ConstantBuffer* g_pAnimBuf;
ConstantBuffer* g_pTransBuf;
CAMERA* g_pCamera;
//グローバル変数
VertexBuffer* g_Polygon;
ID3D11ShaderResourceView* g_pTex;
BlendState* g_pBlendState;
BlendState* g_pAddBlend;
SamplerState* g_pSamplerState;
Float_3 position;

XAUDIO2_BUFFER*g_pBGM;
XAUDIO2_BUFFER*g_pSE;
IXAudio2SourceVoice*g_pBGMSource;


void CheckDelete();
HRESULT initgame(void)
{

	//pos.centerX = 480;
	//pos.centerY = 270;
	//pos.Width = 100;
	//pos.Height = 100;
	HRESULT hr;
	//ポリゴンの座標データ
	Vertex vtx[] =
	{

	{{200.0f,90.0f,0.0f},{0.0f,0.0f}},
	{{250.0f, 90.0f, 0.0f},{1.0f,0.0f} },
	{{ 200.0f, 140.0f, 0.0f }, { 0.0f,1.0f }},
	{{250.0f, 140.0f, 0.0f} ,{1.0f,1.0f}}
	};


	g_Polygon = new VertexBuffer;
	hr = g_Polygon->Create(vtx, 4);
	if (FAILED(hr)) { return hr; }
	//頂点シェーダー
	g_pVs = new VertexShader;
	hr = g_pVs->Load(GetDevice(), "PolygonVS.cso");
	if (FAILED(hr)) { return hr; }
	//アニメシェーダー
	g_pAnimVs = new VertexShader;
	hr = g_pAnimVs->Load(GetDevice(), "AnimPolyVS.cso");
	if (FAILED(hr)) { return hr; }
	g_pTransVs = new VertexShader;
	hr = g_pTransVs->Load(GetDevice(), "TransPolyVS.cso");
	if (FAILED(hr)) { return hr; }
	//ピクセルシェーダー
	g_pPs = new PixelShader;
	hr = g_pPs->Load(GetDevice(), "PolygonPS.cso");
	if (FAILED(hr)) { return hr; }
	//ネガポジシェーダー
	g_pNPPs = new PixelShader;
	hr = g_pNPPs->Load(GetDevice(), "NegaPosiPS.cso");
	if (FAILED(hr)) { return hr; }
	//定数バッファ作成
	//テクスチャアニメーション
	g_pAnimBuf = new ConstantBuffer;
	hr = g_pAnimBuf->Create(sizeof(AnimeUV));
	if (FAILED(hr)) { return hr; }
	//テクスチャアニメーション
	g_pTransBuf = new ConstantBuffer;
	hr = g_pTransBuf->Create(sizeof(Transform));
	if (FAILED(hr)) { return hr; }
	//テクスチャ読み込み
	hr = LoadTextureFromFile(GetDevice(), "Assets/nc117126.png", &g_pTex);
	if (FAILED(hr)) { return hr; }
	//BlendState作成
	g_pBlendState = new BlendState(false);
	g_pAddBlend = new BlendState(true);
	g_pSamplerState = new SamplerState;

	//音データの読み込み

	g_pBGM = CreateSound("Assets/FIXBGMMM.wav", false);
	if (g_pBGM == nullptr) { return E_FAIL; }
	g_pSE = CreateSound("Assets/SE.wav", false);
	if (g_pSE == nullptr) { return E_FAIL; }
	////BGMの再生
	g_pBGMSource = StartSound(g_pBGM);
	g_pBGMSource->SetVolume(0.7f);//MAX=1

	//ゲームオブジェクトの作成
	SpriteDesc desc;
	ZeroMemory(&desc, sizeof(SpriteDesc));
	desc.pVS = g_pAnimVs;
	desc.pPS = g_pPs;
	desc.pConst[0] = g_pAnimBuf;
	desc.pConst[1] = g_pTransBuf;
	g_pPlayer = new Player(desc);
	g_BG = new BG(desc);
	result = new RERSULT(desc);
	//初期化のタイミングで球は作らない
	for (int i = 0; i < BULLET_NUM; i++) {
		g_pBullet[i] = nullptr;
	}
	for (int i = 0; i < EFFECTNUM; i++) {
		g_pEffect[i] = nullptr;
	}
	//ZeroMemory(&desc, sizeof(desc));
	desc.pVS = g_pTransVs;
	//desc.pPS = g_pPs;
	//desc.pConst[0] = g_pTransBuf;
	//for (int i = 0; i < BULLET_NOTE; i++) {
	//	g_pEnemy[i] = new Notes(desc);
	//	g_pEnemy[i] ->SetPos(
	//		((rand() % 5)*240.0f), 
	//		((rand() % 5)*135.0f));
	//		

	//}

	g_pCamera = new CAMERA(g_pPlayer);
	initHumen();
	return hr;


}


void uninitgame(void)
{
	g_pBGMSource->Stop();
	UninitHumen();
	delete g_pCamera;
	for (int i = 0; i < BULLET_NOTE; i++)
	{
		if (g_pEnemy[i]!=nullptr)
		{
			delete g_pEnemy[i];
		}
	}	
	for (int i = 0; i < EFFECTNUM; i++)
	{
		if (g_pEffect[i] != nullptr)
		{
			delete g_pEffect[i];
		}
	}
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (g_pBullet[i] == nullptr)
		{
			continue;
		}

	}
	delete result;
	delete g_BG;
	delete g_pPlayer;
	delete g_pSamplerState;
	delete g_pAddBlend;
	delete g_pBlendState;
	g_pTex->Release();
	delete g_pTransBuf;
	delete g_pAnimBuf;
	delete g_pNPPs;
	delete g_pPs;
	delete g_pTransVs;
	delete g_pAnimVs;
	delete g_pVs;
	delete g_Polygon ;

}

void updategame(void)
{
	UpdateHumen();
	position.x = g_pPlayer->Gettrans().posX;
	position.y= g_pPlayer->Gettrans().posY;
		g_pPlayer->UpdatePlayer();
 	if (g_pPlayer->isShot())
	{
		bulletshot(position);
	
	}

	for (int i = 0; i < BULLET_NOTE; i++)
	{
		if (g_pEnemy[i] != nullptr)
		{
			g_pEnemy[i]->Update();

		}
	}
 	for (int i = 0; i < BULLET_NUM; i++) {
  		if (g_pBullet[i] != nullptr) 
		{
			
			g_pBullet[i]->Update();
			
		}
	} 
	g_BG->UpdateBG();

	for (int i = 0; i < EFFECTNUM; i++)
	{
		if (g_pEffect[i] != nullptr)
		{
			g_pEffect[i]->Update();
		}

	}
	g_pCamera->Update();
	if (IsKeyTrigger(VK_RETURN))
	{
		StartSC(TITLE);
	}
	CheckDelete();
}
void drawgame(void) 
{
	//事前に行う描画の設定

	g_pVs->Bind(GetContext());
	g_pPs->Bind(GetContext());

	g_pAnimVs->Bind(GetContext());
	g_pNPPs->Bind(GetContext());
	g_pBlendState->Bind();
	g_pSamplerState->Bind();
	g_BG->Draw();
	g_pVs->Bind(GetContext());
	GetContext()->PSSetShaderResources(0, 1, &g_pTex);
	//g_Polygon->Draw();

	g_pAnimVs->Bind(GetContext());
	g_pAddBlend->Bind();
	g_pPlayer->Draw();
	g_pBlendState->Bind();
	g_pTransVs->Bind(GetContext());
	for (int i = 0; i < BULLET_NOTE; i++)
	{
		if (g_pEnemy[i] != nullptr)
		{
			g_pEnemy[i]->Draw();
		}
	}
	g_pAddBlend->Bind();
	for (int i = 0; i < BULLET_NUM; i++) {
		if (g_pBullet[i] != nullptr)
		{
			g_pBullet[i]->Draw();
		}
	}

	for (int i = 0; i < EFFECTNUM; i++)
		if (g_pEffect[i] != nullptr)
	{
		{
			g_pEffect[i]->Draw();
		}
	}


	if (GetFramecount() >= Checkframe)
	{
		Result = g_BG->checkbg();
		if (Result == true) {
			result->Change(true);
			result->Draw();
		}
		else {
			result->Change(false);
			result->Draw();
		}
	}
	//Debug表示
	g_pBlendState->Bind();
	//GeometoryColor(0.0, 0.0, 1.0,1.0);
	//DrawLine(0, 0, 100, 100);
	//DrawRect(150, 150, 100, 100);
	//DrawCircle(150, 250, 100);
	/*DebugPrint("Score:%d",);*/

}


void UpdateCollision(int n)
{

	float collisionpos;
	switch (n) {
	case 1:
		 collisionpos = 120;
		break;

	case 2:
		 collisionpos = 360;
		break;
	case 3:
		 collisionpos = 600;
		break;
	case 4:
		collisionpos = 840;
		break;


	}
	//球の総当たり
	for (int j = 0; j < BULLET_NUM; j++)
	{
		if (g_pBullet[j] == nullptr)
		{
			continue;
		}
		if (g_pBullet[j]->isDestroy())
		{
			continue;
		}
		//球情報取得
		float BulletX = g_pBullet[j]->GetTrans().posX;
		float BulletY = g_pBullet[j]->GetTrans().posY;
		float BulletW = g_pBullet[j]->getWidth();
		float BulletH = g_pBullet[j]->getHeight();
		float BL = BulletX - BulletW / 2;
		float BR = BulletX + BulletW / 2;
		float BU = BulletY - BulletH / 2;
		float BD = BulletY + BulletH / 2;
		//for (int i = 0; i < BULLET_NOTE; i++)
		//{
		//	if (g_pEnemy[i] == nullptr)
		//	{
		//		continue;
		//	}
		//	if (g_pEnemy[i]->isDestroy())
		//	{
		//		continue;
		//	}
		//	float EnemyX = g_pEnemy[i]->GetTrans().posX;
		//	float EnemyY = g_pEnemy[i]->GetTrans().posY;
		//	float EnemyW = g_pEnemy[i]->getWidth();
		//	float EnemyH = g_pEnemy[i]->getHeight();
		//	float EL = EnemyX - EnemyW / 2;
		//	float ER = EnemyX + EnemyW / 2;
		//	float EU = EnemyY - EnemyH / 2;
		//	float ED = EnemyY + EnemyH / 2;


		if (BulletY > 400 &&BulletY < 600 && BulletX==collisionpos)
		{
			StartSound(g_pSE);
			//break;
			//g_pEnemy[i]->damage(1);
			g_pBullet[j]->Destroy();
			g_BG->UpperBG(1);
			for (int k = 0; k < 10; k++) {
				Transform trans;
				trans.posX =
					g_pBullet[j]->GetTrans().posX;
				trans.posY =
					g_pBullet[j]->GetTrans().posY;
				trans.scaleX = 1;
				trans.scaleY = 1;
				trans.angle = 0.0f;
				Effect::Desc effect;
				ZeroMemory(&effect, sizeof(effect));
				effect.lifeTime = 0.5f;
				effect.moveX.speed = ((rand() % 11) - 5)*0.5f;
				effect.moveY.speed = ((rand() % 11) - 5)*0.5f;

				
				Createeffect(trans, "Assets/Texture.png", effect);
				//効果音を鳴らす

			}



		}
	}
}


void CheckDelete()
{
	for (int i = 0; i < BULLET_NOTE; i++) {
	
		if (g_pEnemy[i] == nullptr) { continue; }
		if (g_pEnemy[i]->isDestroy()) {
			delete g_pEnemy[i];
			g_pEnemy[i] = nullptr;
		}
	}
	for (int i = 0; i < BULLET_NUM; i++) {
		if (g_pBullet[i] == nullptr) { continue; }
		if (g_pBullet[i]->isDestroy()) {
			delete g_pBullet[i];
			g_pBullet[i] = nullptr;
		}
	}
	for (int i = 0; i < EFFECTNUM; i++) {
		if (g_pEffect[i] == nullptr) { continue; }
		if (g_pEffect[i]->IsDestroy())
		{
			delete g_pEffect[i];
			g_pEffect[i] = nullptr;
		}
	}
}
CAMERA* GetCamera()
{
	return g_pCamera;
}

void bulletshot(Float_3 position)
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (g_pBullet[i])
		{
			continue;
		}

		SpriteDesc desc;

		ZeroMemory(&desc, sizeof(desc));
		desc.pVS = g_pTransVs;
		desc.pPS = g_pPs;
		desc.pConst[0] = g_pTransBuf;

		g_pBullet[i] = new Bullet(desc);
		g_pBullet[i]->SetPos(
			position.x
			, position.y - 50);
		g_pBullet[i]->SetMove(0,10);
		break;	

	}
}
void Createeffect(Transform Trans, const char* pTex, Effect::Desc effect)
{
	for (int i = 0; i < EFFECTNUM; i++)
	{
		if (g_pEffect[i] != nullptr)
		{
			continue;
		}

		SpriteDesc desc;

		ZeroMemory(&desc , sizeof(desc));
		desc.pVS = g_pTransVs;
		desc.pPS = g_pPs;
		desc.pConst[0] = g_pTransBuf;
		desc.pTexture = pTex;
		g_pEffect[i] = new Effect(desc, Trans, effect);
		break;
	}
	
}

DWORD Getnow(void)
{
	return nowtime;
}

void UpdateTime(DWORD now)
{

	nowtime = now;
}
