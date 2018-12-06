#pragma once
#include <string>

#define SAFE_RELEASE(x)  { if(x) { (x)->Release(); (x)=NULL; } }	// ����}�N��

void ErrorStop(std::string message);