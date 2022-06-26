#pragma once

#include "main.hpp"

#if STL_IS_AVAILABLE
#include <filesystem>
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

  void check(bool b);

  String chdir() const;

  bool chdir(const String& path);

  bool touch(const String& path);

  bool list();

  bool list(const String& path);

  bool mkdir(const String& path);

  bool rmdir(const String& path);

  bool remove(const String& path);

  void interactive();

#if EXPLORER_IMPL_STL
  void setRoot(const std::filesystem::path root);
#endif

protected:
#if EXPLORER_IMPL_STL
  std::filesystem::path root_;
#endif
};
extern Explorer explorer;
