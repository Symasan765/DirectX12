#include "Main.h"
#include <crtdbg.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment( lib, "winmm.lib" )
#pragma comment(lib,"xinput.lib")
//#pragma comment(lib,"assimp-vc140-mt.lib")
#pragma comment( lib, "legacy_stdio_definitions.lib" )



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	return 0;
}