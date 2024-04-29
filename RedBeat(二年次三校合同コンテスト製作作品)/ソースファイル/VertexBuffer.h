#pragma once
#include "DirectX.h"

 struct Vertex {
	float pos[3];
	float uv[2];
};


class VertexBuffer {
public:
	//���_�o�b�t�@�̍쐬
	//pVtx	���_���̐擪�A�h���X
	//num	���_���z��̃f�[�^��
	HRESULT Create(Vertex*pVtx,int num);
	//�|���S���`��
	//void Draw(void);
	void Draw(D3D11_PRIMITIVE_TOPOLOGY Topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
private:
	ID3D11Buffer*m_pVtxBuf;//�쐬�������_�o�b�t�@
	int m_vtxNum;//���_�̐�

};