#pragma once
#include"VertexBuffer.h"
#include"ConstantBuffer.h"
#include"Shader.h"
typedef struct
{
	float uvW;//分割時の横幅
	float uvH;//分割時の縦幅
	float uvLX;//目的の左上U座標
	float uvLY;//目的の右上V座標
}AnimeUV;
typedef struct
{
	float posX, posY, scaleX, scaleY, angle;
	float dummy[3];
}Transform;
//Sprite設定用構造体
typedef struct {
	Vertex* pVtx;
	const char* pTexture;
	VertexShader* pVS;
	PixelShader* pPS;
	ConstantBuffer* pConst[4];
}SpriteDesc;
class Sprite
{
public:
	Sprite(SpriteDesc desc);
	~Sprite();
	void Write(void* pData,int slot);
	void Draw(void);
private:
	VertexBuffer* m_pVtxBuf;
	VertexShader* m_pVS;
	PixelShader* m_pPS;
	ConstantBuffer* m_pConst[4];
	ID3D11ShaderResourceView* m_pTex;
};

