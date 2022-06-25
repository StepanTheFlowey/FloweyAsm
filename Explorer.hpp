#pragma once

#include "main.hpp"

#if STL_IS_AVAILABLE
#define EXPLORER_IMPL_STL 1
#endif

#include "String.hpp"

class Explorer {
public:

  Explorer() = default;

  ~Explorer() = default;

  bool isExist(const String& path);

  bool isDirectory(const String& path);

  bool isFile(const String& path);

  String getCwd() const;

  void chdir(const String& path);

  bool touch(const String& path);

  bool list();

  bool list(const String& path);

  bool mkdir(const String& path);

  bool rmdir(const String& path);

  bool rm(const String& path);

  void interactive();
};
extern Explorer explorer;
