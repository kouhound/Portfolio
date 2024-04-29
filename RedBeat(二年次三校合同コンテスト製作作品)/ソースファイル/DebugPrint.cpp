#include "DebugPrint.h"

#include <vector>
#include <string>
#include <dwrite.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

struct DP_Info
{
	std::string text;
	float size;
	float x;
	float y;
};
using DP_InfoList = std::vector<DP_Info>;

// 描画データ
DP_Info g_DP_Info;
DP_InfoList g_DP_InfoLists;
SIZE g_DP_size;
// 各オブジェクト
ID2D1Factory* g_DP_Factory;
IDWriteFactory* g_DP_DirectWrite;
IDWriteTextFormat* g_DP_Format;
ID2D1RenderTarget* g_DP_RenderTarget;
ID2D1SolidColorBrush* g_DP_Brush;
ID2D1SolidColorBrush* g_DP_BrushBack;


std::wstring CharToWide(std::string& str)
{
	// 必要バイト数計算
	size_t size;
	mbstowcs_s(&size, nullptr, 0, str.c_str(), _TRUNCATE);

	// 変換
	wchar_t* pWide = new wchar_t[size];
	mbstowcs_s(nullptr, pWide, size, str.c_str(), _TRUNCATE);

	// 値コピー
	std::wstring wStr = pWide;
	delete[] pWide;

	return wStr;
}


void DebugPrint(const char* text)
{
	g_DP_Info.text = text;
	g_DP_InfoLists.push_back(g_DP_Info);
	g_DP_Info.y += g_DP_Info.size;
}

void InitDebugPrint(ID3D11Device* pDevice, IDXGISwapChain* pSwapChain, float size)
{
	//--- Direct2Dリソースの作成
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_DP_Factory);
	
	//--- DirectWriteの作成
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&g_DP_DirectWrite));
		
	//--- Direct2D用のレンダーターゲット
	IDXGISurface* pFrameBuffer;
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED));
	pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pFrameBuffer));
	g_DP_Factory->CreateDxgiSurfaceRenderTarget(pFrameBuffer, &props, &g_DP_RenderTarget);
	DXGI_SURFACE_DESC desc;
	pFrameBuffer->GetDesc(&desc);
	g_DP_size.cx = desc.Width;
	g_DP_size.cy = desc.Height;
	pFrameBuffer->Release();

	//--- 文字設定
	// フォント作成
	g_DP_DirectWrite->CreateTextFormat(
		L"メイリオ", nullptr,
		DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
		size, L"", &g_DP_Format);
	// テキストアライメント
	g_DP_Format->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
	// ブラシ
	g_DP_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Aqua), &g_DP_Brush);
	g_DP_RenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &g_DP_BrushBack);


	g_DP_Info.size = size;
}

void UninitDebugPrint()
{
	g_DP_Brush->Release();
	g_DP_BrushBack->Release();
	g_DP_Format->Release();
	g_DP_RenderTarget->Release();
	g_DP_DirectWrite->Release();
	g_DP_Factory->Release();
}

void DrawDebugPrint()
{
	g_DP_RenderTarget->BeginDraw();
	
	DP_InfoList::iterator it = g_DP_InfoLists.begin();
	while (it != g_DP_InfoLists.end())
	{
		std::wstring wStr = CharToWide(it->text);
		g_DP_RenderTarget->DrawText(wStr.c_str(), wStr.length(), g_DP_Format,
			D2D1::RectF(it->x + 1.5f, it->y + 1.5f, g_DP_size.cx, g_DP_size.cy), g_DP_BrushBack, D2D1_DRAW_TEXT_OPTIONS_CLIP);
		g_DP_RenderTarget->DrawText(wStr.c_str(), wStr.length(), g_DP_Format,
			D2D1::RectF(it->x, it->y, g_DP_size.cx, g_DP_size.cy), g_DP_Brush, D2D1_DRAW_TEXT_OPTIONS_CLIP);
		++it;
	}
	g_DP_RenderTarget->EndDraw();
	
	g_DP_InfoLists.clear();
	g_DP_Info.x = 0.f;
	g_DP_Info.y = 0.f;
}