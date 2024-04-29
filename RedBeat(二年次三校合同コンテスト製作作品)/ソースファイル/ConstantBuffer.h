#pragma once
#include "DirectX.h"

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();
	//�萔�o�b�t�@�̐���
	//size �o�b�t�@�̑傫��

	HRESULT Create(int size);

	//�萔�o�b�t�@�փf�[�^��������
	//pdata�@���ƂɂȂ�f�[�^
	//void*�ɂ̓A�h���X�ł���Ή��ł��n����

	void Write(void * pData);


	//�萔�o�b�t�@��GPU�֐ݒ�

	void bind(int slot);
private:
	ID3D11Buffer* m_pBuffer;
};

