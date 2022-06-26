#pragma once

#include "main.hpp"

#if STL_IS_AVAILABLE
#include <string>
#include <filesystem>
#endif

#if STRING_FORCE_IMPL_CHAR

#define STRING_IMPL_CHAR 1

#else

#if STL_IS_AVAILABLE
#define STRING_IMPL_STL 1
#else
#define STRING_IMPL_CHAR 1
#endif

#endif

#if PLATFORM_WINDOWS
using string_size_t = size_t;
#endif

class String {
public:

  String() = default;

  String(const char* cstr);

  String(const String& string);

#if STL_IS_AVAILABLE
  String(const std::string& string);
    
  String(const std::filesystem::path& path);
#endif

#if STRING_IMPL_CHAR
  ~String();
#elif STRING_IMPL_STL
  ~String() = default;
#endif

  bool isEmpty() const;

  char at(const string_size_t pos) const;

  inline string_size_t getSize() const {
#if STRING_IMPL_CHAR
    return size_ - 1;
#elif STRING_IMPL_STL
    return string_.size();
#endif
  }

  inline const char* c_str() const {
#if STRING_IMPL_STL
    return string_.c_str();
#elif STRING_IMPL_CHAR
    return string_;
#endif
  }

  inline char& operator[](const string_size_t pos) {
    return string_[pos];
  }

  String& operator=(const String& string) noexcept;

  String& operator=(String&& string) noexcept;

  String& operator=(const std::string& string) noexcept;

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
