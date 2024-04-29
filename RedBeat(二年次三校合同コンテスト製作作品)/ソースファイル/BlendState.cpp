#include "BlendState.h"

BlendState::BlendState(bool add) 
{
	HRESULT hr;

	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	if (add) {//加算合成
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	}
	else {//アルファブレンディング
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	}
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	hr = GetDevice()->CreateBlendState(&blendDesc, &m_pBlendState);
//	float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
//	GetContext()->OMSetBlendState(m_pBlendState, blendFactor, 0xffffffff);
}
BlendState::~BlendState()
{
	
}
void BlendState::Bind(void)
{
	float blendFactor[4] = { 0.0f,0.0f,0.0f,0.0f };
	GetContext()->OMSetBlendState(m_pBlendState, blendFactor, 0xffffffff);


	
}