#pragma once
#include <string>
#include <Windows.h>

#define SAFE_RELEASE(x)  { if(x) { (x)->Release(); (x)=NULL; } }	// 解放マクロ
#define SAFE_DELETE(x)  { if(x) { delete x; (x)=nullptr; } }	// 解放マクロ

void ErrorStop(std::string message);

/// <summary>
/// 引数のHRESULT値を確認し、エラーであれば例外を吐く関数
/// </summary>
void CheckHR(HRESULT hr);