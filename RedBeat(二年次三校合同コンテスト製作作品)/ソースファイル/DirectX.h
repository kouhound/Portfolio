#pragma once


//DirectX�̋@�\���Ăяo��
#include<d3d11.h>
#pragma comment(lib,"d3d11.lib")

//----�v���g�^�C�v�錾�@
/*
Width �t���[���o�b�t�@��
Height�@�t���[���o�b�t�@�c
hWnd ���蓖�Ă�E�B���h�E
fullscreen �t���X�N���[���̐ݒ�
�߂�l�@�������̌���







*/
HRESULT InitDirectX(UINT Width, UINT Height, HWND hWnd, bool fullscreeen);



//DirectX�̏I������
void UninitDirectX(void);
//DirectX�̕`��J�n
void BeginDirectX(void);
//DirectX�̕`��I��
void EndDirectX(void);

//Device���擾���邽�߂̊֐�
ID3D11Device* GetDevice(void);
ID3D11DeviceContext* GetContext(void);
