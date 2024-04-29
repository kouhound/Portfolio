#include "Geometory.h"
#include <DirectXMath.h>
#include "Shader.h"
#include "ConstantBuffer.h"
#include "DirectX.h"
#include "VertexBuffer.h"

const char* GeometoryVS = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};
cbuffer WVP : register(b0) {
	float4x4 world;
	float4x4 proj;
};
cbuffer Param : register(b1) {
	float4 color;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, proj);
	vout.color = color;
	return vout;
}
)EOT";
const char* GeometoryPS = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};
float4 main(PS_IN pin) : SV_TARGET0 {
	return pin.color;
}
)EOT";

DirectX::XMFLOAT4X4 g_geometoryMat[2];
DirectX::XMFLOAT4 g_geometoryColor;
ConstantBuffer* g_pBuf[2];
VertexShader* g_pGeometoryVS;
PixelShader* g_pGeometoryPS;
VertexBuffer* g_pVertexBuffer[3];

void InitGeometory(float screenWidth, float screenHeight)
{
	HRESULT hr;
	DirectX::XMStoreFloat4x4(&g_geometoryMat[0], DirectX::XMMatrixIdentity());
	DirectX::XMStoreFloat4x4(&g_geometoryMat[1], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixOrthographicOffCenterLH(0, screenWidth, screenHeight, 0, -1.f, 1.0f)
	));
	g_pBuf[0] = new ConstantBuffer();
	hr = g_pBuf[0]->Create(sizeof(g_geometoryMat));
	g_pBuf[0]->Write(g_geometoryMat);

	g_pBuf[1] = new ConstantBuffer();
	hr = g_pBuf[1]->Create(sizeof(g_geometoryColor));
	GeometoryColor(1, 1, 1, 1);

	g_pGeometoryVS = new VertexShader();
	hr = g_pGeometoryVS->Compile(GetDevice(), GeometoryVS);
	g_pGeometoryPS = new PixelShader();
	hr = g_pGeometoryPS->Compile(GetDevice(), GeometoryPS);


	//------
	// ‡@Œ´“_‚©‚çX²•ûŒü‚Ö‚PL‚Ñ‚½ü‚ğì¬
	//------
	Vertex lineVtx[] = {
		{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
		{{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
	};
	g_pVertexBuffer[0] = new VertexBuffer();
	hr = g_pVertexBuffer[0]->Create(lineVtx, 2);
	//------
	// ‡A•‚PA’†S‚ªŒ´“_‚ÌlŠp‚ğì¬
	//------
	Vertex rectVtx[] = {
		{{-0.5f,-0.5f, 0.0f}, {0.0f, 0.0f}},
		{{ 0.5f,-0.5f, 0.0f}, {0.0f, 0.0f}},
		{{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f}},
		{{ 0.5f, 0.5f, 0.0f}, {0.0f, 0.0f}}
	};
	g_pVertexBuffer[1] = new VertexBuffer();
	g_pVertexBuffer[1]->Create(rectVtx, 4);
	//------
	// ‡B’†S‚ªŒ´“_‚ÅA”¼Œa0.5‚Ì‰~‚ğì¬
	//------
	const int CircleSplit = 16;
	Vertex circleVtx[3 * CircleSplit] = {};
	for (int i = 0; i < CircleSplit; ++i)
	{
		// Œ´“_
		circleVtx[i * 3 + 0].pos[0] = 0.0f;
		circleVtx[i * 3 + 0].pos[1] = 0.0f;
		circleVtx[i * 3 + 0].pos[2] = 0.0f;
		// ’¸“_‡@
		circleVtx[i * 3 + 1].pos[0] = sinf(i * 2 * 3.14f / CircleSplit) * 0.5f;
		circleVtx[i * 3 + 1].pos[1] = cosf(i * 2 * 3.14f / CircleSplit) * -0.5f;
		circleVtx[i * 3 + 1].pos[2] = 0.0f;
		// ’¸“_‡A
		circleVtx[i * 3 + 2].pos[0] = sinf((i + 1) * 2 * 3.14f / CircleSplit) * 0.5f;
		circleVtx[i * 3 + 2].pos[1] = cosf((i + 1) * 2 * 3.14f / CircleSplit) * -0.5f;
		circleVtx[i * 3 + 2].pos[2] = 0.0f;
	}
	g_pVertexBuffer[2] = new VertexBuffer();
	g_pVertexBuffer[2]->Create(circleVtx, 3 * CircleSplit);
}
void UninitGeometory()
{
	delete g_pVertexBuffer[2];
	delete g_pVertexBuffer[1];
	delete g_pVertexBuffer[0];
	delete g_pGeometoryPS;
	delete g_pGeometoryVS;
	delete g_pBuf[1];
	delete g_pBuf[0];
}
void GeometoryColor(float r, float g, float b, float a)
{
	g_geometoryColor.x = r;
	g_geometoryColor.y = g;
	g_geometoryColor.z = b;
	g_geometoryColor.w = a;
	g_pBuf[1]->Write(&g_geometoryColor);
}
void DrawLine(float startX, float startY, float endX, float endY)
{
	DirectX::XMVECTOR start = DirectX::XMVectorSet(startX, startY, 0.0f, 0.0f);
	DirectX::XMVECTOR end = DirectX::XMVectorSet(endX, endY, 0.0f, 0.0f);
	DirectX::XMVECTOR vec = DirectX::XMVectorSubtract(start, end);
	DirectX::XMVECTOR dot = DirectX::XMVector3Dot(
		DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),
		DirectX::XMVector3Normalize(vec));
	DirectX::XMVECTOR cross = DirectX::XMVector3Cross(
		DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f),
		DirectX::XMVector3Normalize(vec));
	float len;
	DirectX::XMStoreFloat(&len, DirectX::XMVector3Length(vec));
	float fDot;
	DirectX::XMStoreFloat(&fDot, dot);
	DirectX::XMFLOAT3 fCross;
	DirectX::XMStoreFloat3(&fCross, cross);
	float angle = acosf(fDot * (fCross.z > 0.0f ? 1 : -1));

	DirectX::XMStoreFloat4x4(&g_geometoryMat[0], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixScaling(len, 10.0f, 1.0f) * 
		DirectX::XMMatrixRotationZ(angle) *
		DirectX::XMMatrixTranslation(startX, startY, 0.0f)
	));
	g_pBuf[0]->Write(g_geometoryMat);

	g_pGeometoryVS->Bind(GetContext());
	g_pGeometoryPS->Bind(GetContext());
	g_pBuf[0]->bind(0);
	g_pBuf[1]->bind(1);
	g_pVertexBuffer[0]->Draw(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}
void DrawRect(float centerX, float centerY, float width, float height)
{
	DirectX::XMStoreFloat4x4(&g_geometoryMat[0], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixScaling(width, height, 1.0f) *
		DirectX::XMMatrixTranslation(centerX, centerY, 0.0f)
	));
	g_pBuf[0]->Write(g_geometoryMat);
	g_pGeometoryVS->Bind(GetContext());
	g_pGeometoryPS->Bind(GetContext());
	g_pBuf[0]->bind(0);
	g_pBuf[1]->bind(1);
	g_pVertexBuffer[1]->Draw();
}
void DrawCircle(float centerX, float centerY, float radius)
{
	DirectX::XMStoreFloat4x4(&g_geometoryMat[0], DirectX::XMMatrixTranspose(
		DirectX::XMMatrixScaling(radius, radius, 1.0f) *
		DirectX::XMMatrixTranslation(centerX, centerY, 0.0f)
	));
	g_pBuf[0]->Write(g_geometoryMat);
	g_pGeometoryVS->Bind(GetContext());
	g_pGeometoryPS->Bind(GetContext());
	g_pBuf[0]->bind(0);
	g_pBuf[1]->bind(1);
	g_pVertexBuffer[2]->Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}