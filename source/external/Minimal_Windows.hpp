#pragma once

#define _WIN32_WINNT 0x0A00
#define NOMINMAX
// Include <mcx.h> if needed
#define NOMCX
// Include <winsvc.h> if needed
#define NOSERVICE
// WinHelp is deprecated
#define NOHELP
#define WIN32_LEAN_AND_MEAN

#include <windows.h>