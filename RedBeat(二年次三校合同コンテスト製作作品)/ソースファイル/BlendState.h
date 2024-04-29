#pragma once
#include"DirectX.h"
class BlendState
{
public:
	BlendState(bool add);
	~BlendState();
	void Bind(void);
private:
	ID3D11BlendState* m_pBlendState;
};

