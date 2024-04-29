#include "SamplerState.h"

SamplerState::SamplerState()
{
	//事前情報
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	//繰り返し設定　デフォルトはCLAMP、繰り返さず最後の色を使い続ける
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW= D3D11_TEXTURE_ADDRESS_WRAP;
	//テクスチャを拡大縮小した時の処理
	//point　元の色を保つ
	//Linear 周辺の色と滑らかにつながるようにする
	//デフォルトはライナー　ドット絵にはpoint指定

	desc.Filter = D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT;
	//生成
	GetDevice()->CreateSamplerState(&desc, &m_pState);

}

SamplerState::~SamplerState()
{
	if (m_pState != nullptr) {
		m_pState->Release();
		m_pState = nullptr;
	}
}

void SamplerState::Bind()
{
	GetContext()->PSSetSamplers(0, 1, &m_pState);
}
