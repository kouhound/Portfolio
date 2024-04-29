#include "ConstantBuffer.h"



ConstantBuffer::ConstantBuffer():m_pBuffer(nullptr) 
{
	
}
ConstantBuffer::~ConstantBuffer() 
{
	if (m_pBuffer != nullptr)
	{
	
	m_pBuffer->Release();
}
}
HRESULT ConstantBuffer::Create(int size) 
{
	HRESULT hr;
	D3D11_BUFFER_DESC Bufdesc;
	ZeroMemory(&Bufdesc, sizeof(Bufdesc));
	Bufdesc.ByteWidth = size;
	Bufdesc.Usage = D3D11_USAGE_DEFAULT;
	Bufdesc.BindFlags =
		D3D11_BIND_CONSTANT_BUFFER;
	//�o�b�t�@�̐���
	hr = GetDevice()->CreateBuffer(&Bufdesc, nullptr, &m_pBuffer);
	return hr;

}
void ConstantBuffer::Write(void * pData) 
{
	GetContext()->UpdateSubresource(m_pBuffer, 0, nullptr, pData, 0, 0);
}

void ConstantBuffer::bind(int slot) {
	//��ڂ̈����͒萔�o�b�t�@�����蓖�Ă�ԍ�
	GetContext()->VSSetConstantBuffers(slot, 1, &m_pBuffer);
}
