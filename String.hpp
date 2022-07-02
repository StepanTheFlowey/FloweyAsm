#pragma once

#include "main.hpp"

#if STL_IS_AVAILABLE
#include <string>
#include <filesystem>
#endif

#if STRING_FORCE_IMPL_CHAR

#define STRING_IMPL_CHAR 1
#define STRING_IMPL_STL 0

#else

#if STL_IS_AVAILABLE
#define STRING_IMPL_STL 1
#else
#define STRING_IMPL_CHAR 1
#endif

#endif

#if PLATFORM_WINDOWS
using string_size_t = size_t;
constexpr string_size_t string_npos = static_cast<string_size_t>(-1);
#endif

class String {
public:

  String() = default;

  String(const char ch);

  String(const char* cstr);

  String(const String& string);

#if STL_IS_AVAILABLE
  String(const std::string& string);

  String(const std::filesystem::path& path);
#endif

  String(const short integer);

  String(const unsigned short integer);

  String(const int integer);

  String(const unsigned int integer);

  String(const long integer);

  String(const unsigned long integer);

  String(const long long integer);

  String(const unsigned long long integer);

  String(const float real);

  String(const double real);

#if STRING_IMPL_CHAR
  ~String();
#elif STRING_IMPL_STL
  ~String() = default;
#endif

  char at(const string_size_t pos) const;

  bool isEmpty() const;

  string_size_t getSize() const;

  inline string_size_t getLenght() const {
    return getSize();
  }

  const char& getFront() const;

  char& getFront();

  const char& getBack() const;

  char& getBack();

  const char* getBegin() const;

  char* getBegin();

  const char* getEnd() const;

  char* getEnd();
  
  const char* c_str() const;

  int parseInt();

  long parseLong();

  float parseFloat();

  double parseDouble();

  void clear();

  void append(const String string);

  void truncate();

  void resize(string_size_t size);

  void erase(string_size_t pos, string_size_t count = 1);

  void pushFront(char ch);

  void popFront();

  void popFront(string_size_t count);

  void pushBack(char ch);

  void popBack();

  void popBack(string_size_t count);

  inline char& operator[](const string_size_t pos) {
    return string_[pos];
  }

  String& operator=(const String& string) noexcept;

  String& operator=(String&& string) noexcept;

  String& operator=(const std::string& string) noexcept;

  String operator+(const String string);

#if STL_IS_AVAILABLE
  operator std::string() const;

  operator std::filesystem::path() const;
#endif

protected:
#if STRING_IMPL_CHAR
  char* string_ = nullptr;
  string_size_t size_ = 0;
#elif STRING_IMPL_STL
  std::string string_;
#endif
};
