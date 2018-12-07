#include "Utility.h"
#include <crtdbg.h>
#include <stdexcept>

using namespace std;

void ErrorStop(std::string message) {
	_ASSERT_EXPR(true, message.c_str());
}

void CheckHR(HRESULT hr)
{
	if (FAILED(hr))
		throw runtime_error("HRESULT is failed value.");
}
