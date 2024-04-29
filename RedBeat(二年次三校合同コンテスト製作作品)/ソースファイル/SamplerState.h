#pragma once


#include"DirectX.h"
class SamplerState
{
public:
	SamplerState();
	~SamplerState();
	void Bind();
private:
	ID3D11SamplerState* m_pState;
};
