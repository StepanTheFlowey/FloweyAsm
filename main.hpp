#pragma once

#define STRING_FORCE_IMPL_CHAR 0



#ifndef __cplusplus
#error Code must be compilled as C++!
#endif // !__cplusplus

#if __cplusplus < 199711L
#error C++ standard must be at least 11!
#endif

#define COMPILLER_TIME __TIME__
#define COMPILLER_DATE __DATE__

#if _WIN32

#define STL_IS_AVAILABLE 1
#define PLATFORM_STRING "Windows"
#define PLATFORM_WINDOWS 1

#else

#define STL_IS_AVAILABLE 0
#define PLATFORM_STRING "unknown"
#define PLATFORM_UNKNOWN 1

#endif

#include <inttypes.h>

constexpr const char* operator""_F(const char* str) {
#if A
  return F(str);
#else
  return str;
#endif
}

const char stringWelcome[] =
"Welcome to FloweyAsm!\n"
"Build date: " COMPILLER_TIME " " COMPILLER_DATE "\n"
"Build platform: " PLATFORM_STRING
;

const char stringShoice[] =
"1. Explorer\n"
"2. Exit\n"
"Select: "
;