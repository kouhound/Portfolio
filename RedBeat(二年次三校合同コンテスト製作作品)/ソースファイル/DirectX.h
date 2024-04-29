#pragma once


//DirectXの機能を呼び出し
#include<d3d11.h>
#pragma comment(lib,"d3d11.lib")

//----プロトタイプ宣言　
/*
Width フレームバッファ横
Height　フレームバッファ縦
hWnd 割り当てるウィンドウ
fullscreen フルスクリーンの設定
戻り値　初期化の結果







*/
HRESULT InitDirectX(UINT Width, UINT Height, HWND hWnd, bool fullscreeen);



//DirectXの終了処理
void UninitDirectX(void);
//DirectXの描画開始
void BeginDirectX(void);
//DirectXの描画終了
void EndDirectX(void);

//Deviceを取得するための関数
ID3D11Device* GetDevice(void);
ID3D11DeviceContext* GetContext(void);
