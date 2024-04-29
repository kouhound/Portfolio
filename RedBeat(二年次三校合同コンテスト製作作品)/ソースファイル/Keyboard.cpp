#include "Keyboard.h"
#include <Windows.h>
#include<joystickapi.h>
//�O���[�o���ϐ�

BYTE g_KeyTable[256];//���݂̓���
BYTE g_OldKeyTable[256];//�ЂƂO�̓���
void KeyboardUpdate()
{
	//�O�t���[���̍ŐV��񂪌Â����ɂȂ�
	memcpy(g_OldKeyTable, g_KeyTable, sizeof(g_OldKeyTable));
	//�ŐV�̃L�[���擾
	GetKeyboardState(g_KeyTable);
	//joyGetPosEx(0,);
}

bool IsKeyPress(int nVirtKey)
{
	return g_KeyTable[nVirtKey] & 0x80;
}

bool IsKeyTrigger(int nVirtKey)
{
	
	return (g_OldKeyTable[nVirtKey]^g_KeyTable[nVirtKey])&g_KeyTable[nVirtKey] & 0x80;
}



bool IsKeyRelease(int nVirtKey)
{
	return (g_OldKeyTable[nVirtKey] ^ g_KeyTable[nVirtKey])&g_OldKeyTable[nVirtKey] & 0x80;
}
