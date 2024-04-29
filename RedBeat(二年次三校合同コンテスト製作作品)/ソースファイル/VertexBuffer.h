#pragma once
#include "DirectX.h"

 struct Vertex {
	float pos[3];
	float uv[2];
};


class VertexBuffer {
public:
	//頂点バッファの作成
	//pVtx	頂点情報の先頭アドレス
	//num	頂点情報配列のデータ数
	HRESULT Create(Vertex*pVtx,int num);
	//ポリゴン描画
	//void Draw(void);
	void Draw(D3D11_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
private:
	ID3D11Buffer*m_pVtxBuf;//作成した頂点バッファ
	int m_vtxNum;//頂点の数

};