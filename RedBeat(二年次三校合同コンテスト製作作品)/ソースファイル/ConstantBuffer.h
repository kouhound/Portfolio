#pragma once
#include "DirectX.h"

class ConstantBuffer
{
public:
	ConstantBuffer();
	~ConstantBuffer();
	//定数バッファの生成
	//size バッファの大きさ

	HRESULT Create(int size);

	//定数バッファへデータ書き込み
	//pdata　もとになるデータ
	//void*にはアドレスであれば何でも渡せる

	void Write(void * pData);


	//定数バッファをGPUへ設定

	void bind(int slot);
private:
	ID3D11Buffer* m_pBuffer;
};

