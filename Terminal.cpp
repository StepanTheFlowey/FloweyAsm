#include "Terminal.hpp"

#if TERMINAL_IMPL_STL 
#include <iostream>
#endif

Terminal terminal;

Terminal::Terminal() {
#if TERMINAL_IMPL_STL 
  std::ios::sync_with_stdio(false);
#endif
#if PLATFORM_WINDOWS
  hConsole_ = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

  clear();
}

Terminal::~Terminal() {
#if TERMINAL_IMPL_STL 
  std::cout.flush();
#endif
}

void Terminal::put(char ch) {
#if TERMINAL_IMPL_STL 
  std::cout.put(ch);
#endif
}

char Terminal::get() {
#if TERMINAL_IMPL_STL 
  return std::cin.get();
#endif
}

void Terminal::print(const char* buff) {
#if TERMINAL_IMPL_STL 
  std::cout << buff;
#endif
}

void Terminal::print(const String& string) {
  print(string.c_str());
}

void Terminal::println() {
  put('\n');
}

void Terminal::println(const char* buff) {
  print(buff);
  println();
}

void Terminal::println(const String& string) {
  print(string);
  println();
}

String Terminal::scan(bool checkAvailable) {
  String string;
  scan(string, checkAvailable);
  return string;
}

string_size_t Terminal::scan(char* buff, string_size_t size) {
#if TERMINAL_IMPL_STL
  return static_cast<string_size_t>(std::cin.read(buff, size).gcount());
#endif
}

void Terminal::scan(String& string, bool checkAvailable) {
#if TERMINAL_IMPL_STL
  if(checkAvailable) {
    if(std::cin.rdbuf()->in_avail() <= 0) {
      return;
    }
  }

  std::string str;

  using myis = std::istream;
  using mytraits = myis::traits_type;

  bool changed = false;
  myis::iostate state = myis::goodbit;
  myis::sentry ok(std::cin, true);

  if(ok) {
    try {
      str.erase();
      const mytraits::int_type metadelim0 = mytraits::to_int_type('\n');
      const mytraits::int_type metadelim1 = mytraits::to_int_type(' ');
      mytraits::int_type meta = std::cin.rdbuf()->sgetc();

      for(;; meta = std::cin.rdbuf()->snextc()) {
        if(mytraits::eq_int_type(mytraits::eof(), meta)) {
          state |= myis::eofbit;
          break;
        }
        else if(mytraits::eq_int_type(meta, metadelim0) ||
                mytraits::eq_int_type(meta, metadelim1)) {
          changed = true;
          std::cin.rdbuf()->sbumpc();
          break;
        }
        else if(str.max_size() <= str.size()) {
          state |= myis::failbit;
        }
        else {
          str += mytraits::to_char_type(meta);
          changed = true;
        }
      }
    }
    catch(...) {
      std::cin.setstate(myis::badbit, true);
    }
  }

  if(!changed) {
    state |= myis::failbit;
  }
  std::cin.setstate(state);
  string = str;
#endif
}

String Terminal::scanln() {
  String string;
  scanln(string);
  return string;
}

string_size_t Terminal::scanln(char* buff, string_size_t size) {
#if TERMINAL_IMPL_STL
  return scan(buff, size);
#endif
}

void Terminal::scanln(String& string) {
#if TERMINAL_IMPL_STL
  std::string str;
  std::getline(std::cin, str);
  string = str;
#endif
}

void Terminal::flush() {
#if TERMINAL_IMPL_STL
  std::cout.flush();
  std::cin.clear();
  if(std::cin.rdbuf()->in_avail() > 0) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
#endif
}

void Terminal::clear() {
#if PLATFORM_WINDOWS
  CONSOLE_SCREEN_BUFFER_INFO csbi{};

  // Get the number of character cells in the current buffer.
  if(!GetConsoleScreenBufferInfo(hConsole_, &csbi)) {
    return;
  }

  // Scroll the rectangle of the entire buffer.
  SMALL_RECT scrollRect{};
  scrollRect.Right = csbi.dwSize.X;
  scrollRect.Bottom = csbi.dwSize.Y;

  // Scroll it upwards off the top of the buffer with a magnitude of the entire height.
  COORD scrollTarget{};
  scrollTarget.Y = 0 - csbi.dwSize.Y;

  // Fill with empty spaces with the buffer's default text attribute.
  CHAR_INFO fill{};
  fill.Char.UnicodeChar = L' ';
  fill.Attributes = csbi.wAttributes;

  // Do the scroll
  if(!ScrollConsoleScreenBufferW(hConsole_, &scrollRect, NULL, scrollTarget, &fill)) {
    return;
  }

  // Move the cursor to the top left corner too.
  csbi.dwCursorPosition.X = 0;
  csbi.dwCursorPosition.Y = 0;

  SetConsoleCursorPosition(hConsole_, csbi.dwCursorPosition);
#endif
}
