#include "Explorer.hpp"

#include "Terminal.hpp"
#include "Workspace.hpp"

#if EXPLORER_IMPL_STL
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
#endif

Explorer explorer;

bool Explorer::isExist(const String& path) {
#if EXPLORER_IMPL_STL
  return fs::exists(path);
#endif
}

bool Explorer::isDirectory(const String& path) {
#if EXPLORER_IMPL_STL
  return fs::is_directory(path);
#endif
}

bool Explorer::isFile(const String& path) {
#if EXPLORER_IMPL_STL
  return fs::is_regular_file(path);
#endif
}

String Explorer::getCwd() const {
  return fs::current_path().string();
}

void Explorer::chdir(const String& path) {
  fs::current_path(path);
}

bool Explorer::touch(const String& path) {
#if EXPLORER_IMPL_STL
  return std::ofstream(path).is_open();
#endif
}

bool Explorer::list() {
 return list(getCwd());
}

bool Explorer::list(const String& path) {
#if EXPLORER_IMPL_STL
  std::error_code error_code;

  for(const auto& i : fs::directory_iterator(path, error_code)) {
    terminal.println(i.path().string());
  }
  return true;
#endif
}

bool Explorer::mkdir(const String& path) {
#if EXPLORER_IMPL_STL
  return fs::create_directory(path);
#endif
}

bool Explorer::rmdir(const String& path) {
#if EXPLORER_IMPL_STL
  if(!isDirectory(path)) {
    return false;
  }
  return fs::remove(path);
#endif
}

bool Explorer::rm(const String& path) {
#if EXPLORER_IMPL_STL
  if(!isFile(path)) {
    return false;
  }
  return fs::remove(path);
#endif
}

void Explorer::interactive() {
#if EXPLORER_IMPL_STL

#endif
}
