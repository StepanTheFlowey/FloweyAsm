#pragma once

#include "main.hpp"

#if PLATFORM_WINDOWS
#include <Windows.h>

#define TERMINAL_IMPL_STL 1
#endif

#include "String.hpp"

class Terminal {
public:

  Terminal();

  ~Terminal();

  void put(char ch);

  char get();

  void print(const char* buff);

  void print(const String& string);

  void println();

  void println(const char* buff);

  void println(const String& string);

  String scan(bool checkAvailable = false);

  string_size_t scan(char* buff, string_size_t size);

  void scan(String& string, bool checkAvailable = false);

  String scanln();

  string_size_t scanln(char* buff, string_size_t size);

  void scanln(String& string);

  void flush();

  void clear();
protected:

#if PLATFORM_WINDOWS
  HANDLE hConsole_ = nullptr;
#endif
};
extern Terminal terminal;
