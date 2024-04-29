#include "title.h"
#include"VertexBuffer.h"
#include "Shader.h"
#include"DirectXTex/TextureLoad.h"
#include"BlendState.h"
#include"SamplerState.h"

#include"BackGround.h"

#include"Effect.h"
#include"Sound.h"
#include"DebugPrint.h"

#include "Geometory.h"
#include "Keyboard.h"
#include"Scene.h"



BG* g_BGT;

VertexShader* g_pPolygonT;
VertexShader* g_pVsT;
VertexShader* g_pAnimVsT;
VertexShader* g_pTransVsT;
PixelShader* g_pPsT;
PixelShader* g_pNPPsT;
ConstantBuffer* g_pAnimBufT;
ConstantBuffer* g_pTransBufT;
CAMERA* g_pCameraT;
//グローバル変数
VertexBuffer* g_PolygonT;
ID3D11ShaderResourceView* g_pTexT;
BlendState* g_pBlendStateT;
BlendState* g_pAddBlendT;
SamplerState* g_pSamplerStateT;
Float_3 positionT;

XAUDIO2_BUFFER*g_pBGMT;
XAUDIO2_BUFFER*g_pSET;
IXAudio2SourceVoice*g_pBGMSourceT;

HRESULT inittitle()
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


	g_PolygonT = new VertexBuffer;
	hr = g_PolygonT->Create(vtx, 4);
	if (FAILED(hr)) { return hr; }
	//頂点シェーダー
	g_pVsT = new VertexShader;
	hr = g_pVsT->Load(GetDevice(), "PolygonVS.cso");
	if (FAILED(hr)) { return hr; }
	//アニメシェーダー
	g_pAnimVsT = new VertexShader;
	hr = g_pAnimVsT->Load(GetDevice(), "AnimPolyVS.cso");
	if (FAILED(hr)) { return hr; }
	g_pTransVsT = new VertexShader;
	hr = g_pTransVsT->Load(GetDevice(), "TransPolyVS.cso");
	if (FAILED(hr)) { return hr; }
	//ピクセルシェーダー
	g_pPsT = new PixelShader;
	hr = g_pPsT->Load(GetDevice(), "PolygonPS.cso");
	if (FAILED(hr)) { return hr; }
	//ネガポジシェーダー
	g_pNPPsT = new PixelShader;
	hr = g_pNPPsT->Load(GetDevice(), "NegaPosiPS.cso");
	if (FAILED(hr)) { return hr; }
	//定数バッファ作成
	//テクスチャアニメーション
	g_pAnimBufT = new ConstantBuffer;
	hr = g_pAnimBufT->Create(sizeof(AnimeUV));
	if (FAILED(hr)) { return hr; }
	//テクスチャアニメーション
	g_pTransBufT = new ConstantBuffer;
	hr = g_pTransBufT->Create(sizeof(Transform));
	if (FAILED(hr)) { return hr; }
	//テクスチャ読み込み
	hr = LoadTextureFromFile(GetDevice(), "Assets/nc117126.png", &g_pTexT);
	if (FAILED(hr)) { return hr; }
	//BlendState作成
	g_pBlendStateT = new BlendState(false);
	g_pAddBlendT = new BlendState(true);
	g_pSamplerStateT = new SamplerState;

	//音データの読み込み

	g_pBGMT = CreateSound("Assets/FIXBGMMM.wav",false);
	if (g_pBGMT == nullptr) { return E_FAIL; }
	g_pSET = CreateSound("Assets/SE.wav", false);
	if (g_pSET == nullptr) { return E_FAIL; }
	////BGMの再生
	g_pBGMSourceT = StartSound(g_pBGMT);
	g_pBGMSourceT->SetVolume(0.7f);//MAX=1

	//ゲームオブジェクトの作成
	SpriteDesc desc;
	ZeroMemory(&desc, sizeof(SpriteDesc));
	desc.pVS = g_pAnimVsT;
	desc.pPS = g_pPsT;
	desc.pConst[0] = g_pAnimBufT;
	desc.pConst[1] = g_pTransBufT;

	g_BGT= new BG(desc);
	//初期化のタイミングで球は作らない

	//ZeroMemory(&desc, sizeof(desc));
	desc.pVS = g_pTransVsT;
	//desc.pPS = g_pPs;
	//desc.pConst[0] = g_pTransBuf;
	//for (int i = 0; i < BULLET_NOTE; i++) {
	//	g_pEnemy[i] = new Notes(desc);
	//	g_pEnemy[i] ->SetPos(
	//		((rand() % 5)*240.0f), 
	//		((rand() % 5)*135.0f));
	//		

	//}

	//g_pCameraT = new CAMERA(g_pPlayerT);
	initHumen();
	return hr;


}

void uninittitle()
{
	g_pBGMSourceT->Stop();
	UninitHumen();
	//delete g_pCameraT;


	delete g_BGT;

	delete g_pSamplerStateT;
	delete g_pAddBlendT;
	delete g_pBlendStateT;
	g_pTexT->Release();
	delete g_pTransBufT;
	delete g_pAnimBufT;
	delete g_pNPPsT;
	delete g_pPsT;
	delete g_pTransVsT;
	delete g_pAnimVsT;
	delete g_pVsT;
	delete g_PolygonT;
}

void drawtitle()
{
	g_pVsT->Bind(GetContext());
	g_pPsT->Bind(GetContext());

	g_pAnimVsT->Bind(GetContext());
	g_pNPPsT->Bind(GetContext());
	g_pBlendStateT->Bind();
	g_pSamplerStateT->Bind();
	g_BGT->Draw();
	g_pVsT->Bind(GetContext());
	GetContext()->PSSetShaderResources(0, 1, &g_pTexT);
	//g_PolygonT->Draw();

	g_pAnimVsT->Bind(GetContext());

	g_pTransVsT->Bind(GetContext());
	
}

void updatetitle()
{
	if (IsKeyTrigger(VK_RETURN))
	{
		StartSC(GAME);
	}
}
