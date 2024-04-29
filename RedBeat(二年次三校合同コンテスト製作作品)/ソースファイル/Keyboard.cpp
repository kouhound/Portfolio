#include "Keyboard.h"
#include <Windows.h>
#include<joystickapi.h>
//グローバル変数

BYTE g_KeyTable[256];//現在の入力
BYTE g_OldKeyTable[256];//ひとつ前の入力
void KeyboardUpdate()
{
	//前フレームの最新情報が古い情報になる
	memcpy(g_OldKeyTable, g_KeyTable, sizeof(g_OldKeyTable));
	//最新のキー情報取得
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
