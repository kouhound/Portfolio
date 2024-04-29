#pragma once
#include"VertexBuffer.h"
#include"ConstantBuffer.h"
#include"Shader.h"
typedef struct
{
	float uvW;//�������̉���
	float uvH;//�������̏c��
	float uvLX;//�ړI�̍���U���W
	float uvLY;//�ړI�̉E��V���W
}AnimeUV;
typedef struct
{
	float posX, posY, scaleX, scaleY, angle;
	float dummy[3];
}Transform;
//Sprite�ݒ�p�\����
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

