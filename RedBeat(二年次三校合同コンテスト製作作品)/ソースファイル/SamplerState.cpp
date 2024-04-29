#include "SamplerState.h"

SamplerState::SamplerState()
{
	//���O���
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	//�J��Ԃ��ݒ�@�f�t�H���g��CLAMP�A�J��Ԃ����Ō�̐F���g��������
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW= D3D11_TEXTURE_ADDRESS_WRAP;
	//�e�N�X�`�����g��k���������̏���
	//point�@���̐F��ۂ�
	//Linear ���ӂ̐F�Ɗ��炩�ɂȂ���悤�ɂ���
	//�f�t�H���g�̓��C�i�[�@�h�b�g�G�ɂ�point�w��

	desc.Filter = D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT;
	//����
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
