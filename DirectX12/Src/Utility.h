#pragma once
#include <string>

#define SAFE_RELEASE(x)  { if(x) { (x)->Release(); (x)=NULL; } }	// ‰ğ•úƒ}ƒNƒ

void ErrorStop(std::string message);