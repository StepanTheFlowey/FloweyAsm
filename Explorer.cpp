#include "Explorer.hpp"

#include "Terminal.hpp"
#include "Workspace.hpp"
#include "switch.h"

#if EXPLORER_IMPL_STL
#include <fstream>
namespace fs = std::filesystem;
#endif

Explorer explorer;

#if EXPLORER_IMPL_STL
bool isSubDir(fs::path p, const fs::path& root) {
  while(!p.empty()) {
    if(fs::equivalent(p, root)) {
      return true;
    }
    p = p.parent_path();
  }
  return false;
}
#endif

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

void Explorer::check(bool b) {
  if(b) {
    terminal.println("OK");
  }
  else {
    terminal.println("Error");
  }
}

String Explorer::chdir() const {
#if EXPLORER_IMPL_STL
  return fs::relative(fs::current_path(), root_).string();
#endif
}

bool Explorer::chdir(const String& path) {
#if EXPLORER_IMPL_STL
  std::error_code error_code;

  if(path.isEmpty()) {
    fs::current_path(root_, error_code);
  }
  else {
    if(!isSubDir(fs::absolute(path), root_)) {
      return false;
    }
    fs::current_path(path, error_code);
  }

  return !error_code;
#endif
}

bool Explorer::touch(const String& path) {
#if EXPLORER_IMPL_STL
  return std::ofstream(path).is_open();
#endif
}

bool Explorer::list() {
  return list(root_ / chdir());
}

bool Explorer::list(const String& path) {
#if EXPLORER_IMPL_STL
  std::error_code error_code;

  for(const auto& i : fs::directory_iterator(path, error_code)) {
    terminal.println(i.path().filename().string());
  }

  //terminal.println(error_code.message());

  return !error_code;
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

bool Explorer::remove(const String& path) {
#if EXPLORER_IMPL_STL
  if(!isFile(path)) {
    return false;
  }
  return fs::remove(path);
#endif
}

void Explorer::interactive() {
#if EXPLORER_IMPL_STL
  bool work = true;
  String com;
  while(work) {
    terminal.print(chdir());
    terminal.print("> ");
    terminal.scan(com);

    switch(strHashSwitch(com.c_str())) {
      case strHashSwitch("exit"):
        work = false;
        break;

      case strHashSwitch("chdir"):
      case strHashSwitch("cd"):
        check(chdir(terminal.scan(true)));
        break;

      case strHashSwitch("mkdir"):
      case strHashSwitch("md"):
        check(mkdir(terminal.scan(true)));
        break;

      case strHashSwitch("rmdir"):
      case strHashSwitch("rd"):
        check(rmdir(terminal.scan(true)));
        break;

      case strHashSwitch("remove"):
      case strHashSwitch("rm"):
        check(remove(terminal.scan(true)));
        break;

      case strHashSwitch("list"):
      case strHashSwitch("ls"):
        list();
        break;

      case strHashSwitch(""):
        break;
      default:
        terminal.println("Not found");
        break;
    }

    terminal.flush();
  }
#endif
}

#if EXPLORER_IMPL_STL
void Explorer::setRoot(const std::filesystem::path root) {
  root_ = fs::absolute(root);
  fs::current_path(root_);
}
#endif
