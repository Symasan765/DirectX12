#include "Utility.h"
#include <crtdbg.h>


void ErrorStop(std::string message) {
	_ASSERT_EXPR(true, message.c_str());
}