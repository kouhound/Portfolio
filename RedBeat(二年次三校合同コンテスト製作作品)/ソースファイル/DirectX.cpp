#include "DirectX.h"
#include "DebugPrint.h"


//グローバル変数
ID3D11Device* g_pDevice;
//描画命令を取り扱う
ID3D11DeviceContext* g_pContext;
//フレームバッファから画面への出力を担う
IDXGISwapChain* g_pSwapChain;

//GPUの出力先を変える設定
ID3D11RenderTargetView* g_pRTV;


ID3D11Device* GetDevice(void)
{
	return g_pDevice;
}
ID3D11DeviceContext* GetContext(void)
{
	return g_pContext;
}







HRESULT InitDirectX(UINT Width, UINT Height, HWND hWnd, bool fullscreeen) 
{
	//変数宣言
	HRESULT hr;//DirectXの処理結果
				//成功なら0失敗なら0以外
	//スワップチェインの設定
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferDesc.Width = Width;
	sd.BufferDesc.Height = Height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.SampleDesc.Count = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	//三項演算子（）一行で書けるif文
	sd.Windowed = fullscreeen ? FALSE : TRUE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	
	//ドライバの種類
	D3D_DRIVER_TYPE driverType;
	D3D_DRIVER_TYPE driverTypes[] = {
		D3D_DRIVER_TYPE_HARDWARE,D3D_DRIVER_TYPE_WARP,D3D_DRIVER_TYPE_REFERENCE
	};
	UINT numDriverTypes = ARRAYSIZE(driverTypes);
	//機能レベル
	D3D_FEATURE_LEVEL featureLevel;
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1,D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,D3D_FEATURE_LEVEL_9_2,D3D_FEATURE_LEVEL_9_1
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);

	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif 
	//作成可能な設定でDirectXの機能を有効化
	for (UINT i = 0; i < numDriverTypes; i++) {
		driverType = driverTypes[i];
		hr = D3D11CreateDeviceAndSwapChain(
			NULL, driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,
			D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pDevice, &featureLevel, &g_pContext);
		//成功判定
		if (SUCCEEDED(hr)) { break; }
	}
	//失敗判定
	if (FAILED(hr)) { return hr; }


	//レンダーターゲットの作成
	//GPUがフレームバッファへ出力するよう設定
	//フレームバッファへのポインタを取得
	ID3D11Texture2D* pFrameBuffer = nullptr;
	hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pFrameBuffer);
	//フレームバッファへのポインタで紐づけてレンダーターゲットビューを作成
	if (SUCCEEDED(hr)) {
		hr = g_pDevice->CreateRenderTargetView(pFrameBuffer, NULL, &g_pRTV);
		g_pContext->OMSetRenderTargets(1 , &g_pRTV, nullptr);
	}

	//ビューポートの設定
	//フレームバッファへ書き込んでよい部分の設定
	D3D11_VIEWPORT vp;
	ZeroMemory(&vp, sizeof(vp));
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = Width;
	vp.Height = Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	g_pContext->RSSetViewports(1, &vp);



	InitDebugPrint(g_pDevice, g_pSwapChain, 20);
	


	//処理結果
	return hr;
}

void UninitDirectX(void) 
{
	UninitDebugPrint();
	g_pRTV->Release();
	g_pSwapChain->SetFullscreenState(false, NULL);
	g_pSwapChain->Release();
	g_pContext->ClearState();
	g_pContext->Release();
	g_pDevice->Release();
}
void BeginDirectX(void)
{
	float color[4] = { 0.6f,0.8f,1.0f,1.0f };
	g_pContext->ClearRenderTargetView(g_pRTV, color);
}
//DirectXの描画終了
void EndDirectX(void) 
{
	DrawDebugPrint();
	g_pSwapChain->Present(0, 0); 
}
