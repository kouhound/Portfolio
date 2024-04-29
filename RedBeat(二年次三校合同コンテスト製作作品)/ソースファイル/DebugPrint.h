#ifndef __DEBUG_PRINT_H__
#define __DEBUG_PRINT_H__

#include <d3d11.h>

void DebugPrint(const char* text);

void InitDebugPrint(ID3D11Device* pDevice, IDXGISwapChain* pSwapChain, float fontSize);
void UninitDebugPrint();
void DrawDebugPrint();

#endif // __DEBUG_PRINT_H__