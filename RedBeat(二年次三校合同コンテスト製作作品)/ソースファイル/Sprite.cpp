#include "Sprite.h"
#include"DirectXTex/TextureLoad.h"
Sprite::Sprite(SpriteDesc desc)
{
	HRESULT hr;
	m_pVtxBuf = new VertexBuffer;
	hr = m_pVtxBuf->Create(desc.pVtx, 4);
	hr = LoadTextureFromFile(GetDevice(), desc.pTexture, &m_pTex);
	m_pVS = desc.pVS;
	m_pPS = desc.pPS;
	for (int i = 0; i < 4; i++)m_pConst[i] = desc.pConst[i];
}

Sprite::~Sprite()
{
	delete m_pVtxBuf;
	m_pTex->Release();
}

void Sprite::Write(void * pData, int slot)
{
	if (m_pConst[slot])
		m_pConst[slot]->Write(pData);

}

void Sprite::Draw(void)
{
	m_pVS->Bind(GetContext());
	m_pPS->Bind(GetContext());
	for (int i = 0; i < 4; i++)
	if (m_pConst[i])
		m_pConst[i]->bind(i);
	GetContext()->PSSetShaderResources(0, 1, &m_pTex);
	m_pVtxBuf->Draw();
}
