#pragma once

#ifdef ZUI_PLATFORM_WINDOWS
#ifdef ZUI_BUILD_DLL
#define ZUI_API __declspec(dllexport)
#else
#define ZUI_API __declspec(dllimport)
#endif
#else
#error Currently Supports Windows Only!
#endif
