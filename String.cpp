#include "String.hpp"

#if STRING_IMPL_CHAR
#include <string.h>
#endif

String::String(const char* cstr) {
#if STRING_IMPL_STL
  string_ = cstr;
#elif STRING_IMPL_CHAR
  if(cstr == nullptr) {
    return;
  }
  size_ = static_cast<string_size_t>(strlen(cstr) + 1);
  string_ = new char[size_] {};
  strcpy_s(string_, static_cast<size_t>(size_), cstr);
#endif
}

String::String(const String& string) {
#if STRING_IMPL_CHAR
  size_ = string.size_;
  string_ = new char[size_];
  strcpy_s(string_, static_cast<size_t>(size_), string.string_);
#elif STRING_IMPL_STL
  string_ = string.string_;
#endif // STRING_IMPL_CHAR
}

#if STL_IS_AVAILABLE
String::String(const std::string& string) {
#if STRING_IMPL_CHAR
  size_ = string.size() + 1;
  string_ = new char[size_];
  strcpy_s(string_, static_cast<size_t>(size_), string.c_str());
#elif STRING_IMPL_STL
  string_ = string;
#endif // STRING_IMPL_CHAR
}

String::String(const std::filesystem::path& path) {
#if STRING_IMPL_CHAR
  std::string string=path.string();
  size_ = string.size() + 1;
  string_ = new char[size_];
  strcpy_s(string_, static_cast<size_t>(size_), string.c_str());
#elif STRING_IMPL_STL
  string_ = path.string();
#endif // STRING_IMPL_CHAR
}
#endif

#if STRING_IMPL_CHAR
String::~String() {
  if(string_ != nullptr) {
    delete string_;
  }
}
#endif

bool String::isEmpty() const {
#if STRING_IMPL_CHAR
  return size_ == 0;
#else
  return string_.empty();
#endif
}

char String::at(const string_size_t pos) const {
#if STRING_IMPL_CHAR
  if(pos >= size_) {
    return 0;
  }
  return string_[pos];
#elif STRING_IMPL_STL
  return string_.at(pos);
#endif
}

String& String::operator=(const String& string) noexcept {
  if(this == &string) {
    return *this;
  }

#if STRING_IMPL_CHAR
  if(size_ != string.size_) {
    if(string_ != nullptr) {
      delete[] string_;
    }

    size_ = string.size_;
    string_ = new char[size_];
  }
  strcpy_s(string_, static_cast<size_t>(size_), string.string_);
#elif STRING_IMPL_STL
  string_ = string.string_;
#endif

  return *this;
}

String& String::operator=(String&& string) noexcept {
  if(this == &string) {
    return *this;
  }

#if STRING_IMPL_CHAR
  if(string_ != nullptr) {
    delete[] string_;
  }

  size_ = string.size_;
  string.size_ = 0;

  string_ = string.string_;
#elif STRING_IMPL_STL
  string_ = std::move(string.string_);
#endif

  return *this;
}

String& String::operator=(const std::string& string) noexcept {
#if STRING_IMPL_CHAR
  if(size_ != string.size() + 1) {
    if(string_ != nullptr) {
      delete string_;
    }

    size_ = string.size() + 1;
    string_ = new char[size_];
  }
  strcpy_s(string_, static_cast<size_t>(size_), string.c_str());
#elif STRING_IMPL_STL
  string_ = string;
#endif
  return *this;
}

String::operator std::string() const {
#if STRING_IMPL_CHAR
  return std::string(string_);
#elif STRING_IMPL_STL
  return string_;
#endif
}

String::operator std::filesystem::path() const {
  return operator std::string();
}
