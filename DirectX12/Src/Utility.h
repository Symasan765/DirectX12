#pragma once
#include <string>
#include <Windows.h>

#define SAFE_RELEASE(x)  { if(x) { (x)->Release(); (x)=NULL; } }	// ����}�N��
#define SAFE_DELETE(x)  { if(x) { delete x; (x)=nullptr; } }	// ����}�N��

void ErrorStop(std::string message);

/// <summary>
/// ������HRESULT�l���m�F���A�G���[�ł���Η�O��f���֐�
/// </summary>
void CheckHR(HRESULT hr);