#include "String.hpp"

#if STRING_IMPL_CHAR
#include <string.h>
#endif

String::String(const char ch) {
#if STRING_IMPL_STL
  string_ = ch;
#elif STRING_IMPL_CHAR
  if(cstr == nullptr) {
    return;
  }
  size_ = static_cast<string_size_t>(strlen(cstr) + 1);
  string_ = new char[size_] {};
  strcpy_s(string_, static_cast<size_t>(size_), cstr);
#endif
}

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
  std::string string = path.string();
  size_ = string.size() + 1;
  string_ = new char[size_];
  strcpy_s(string_, static_cast<size_t>(size_), string.c_str());
#elif STRING_IMPL_STL
  string_ = path.string();
#endif // STRING_IMPL_CHAR
}
#endif

String::String(const short integer) {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_ = std::to_string(integer);
#endif // STRING_IMPL_CHAR
}

String::String(const unsigned short integer) {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_ = std::to_string(integer);
#endif // STRING_IMPL_CHAR
}

String::String(const int integer) {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_ = std::to_string(integer);
#endif // STRING_IMPL_CHAR
}

String::String(const unsigned int integer) {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_ = std::to_string(integer);
#endif // STRING_IMPL_CHAR
}

String::String(const long integer) {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_ = std::to_string(integer);
#endif // STRING_IMPL_CHAR
}

String::String(const unsigned long integer) {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_ = std::to_string(integer);
#endif // STRING_IMPL_CHAR
}

String::String(const long long integer) {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_ = std::to_string(integer);
#endif // STRING_IMPL_CHAR
}

String::String(const unsigned long long integer) {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_ = std::to_string(integer);
#endif // STRING_IMPL_CHAR
}

String::String(const float real) {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_ = std::to_string(real);
#endif // STRING_IMPL_CHAR
}

String::String(const double real) {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_ = std::to_string(real);
#endif // STRING_IMPL_CHAR
}

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

void String::append(const String string) {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_.append(string.string_);
#endif
}

void String::truncate() {
  if(isEmpty()) {
    return;
  }
  while(getFront() == ' ') {
    popFront();
  }
  while(getBack() == ' ') {
    popBack();
  }
}

string_size_t String::getSize() const {
#if STRING_IMPL_CHAR
  return size_ - 1;
#elif STRING_IMPL_STL
  return string_.size();
#endif
}

const char* String::c_str() const {
#if STRING_IMPL_CHAR
  return string_;
#elif STRING_IMPL_STL
  return string_.c_str();
#endif
}

void String::clear() {
#if STRING_IMPL_CHAR
  if(string_ != nullptr) {
    delete[] string_;
    string_ = nullptr;
  }
#elif STRING_IMPL_STL
  string_.clear();
#endif
}

const char& String::getFront() const {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  return string_.front();
#endif
}

char& String::getFront() {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  return string_.front();
#endif
}

const char& String::getBack() const {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  return string_.back();
#endif
}

char& String::getBack() {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  return string_.back();
#endif
}

const char* String::getBegin() const {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  return string_.begin()._Ptr;
#endif
}

char* String::getBegin() {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  return const_cast<char*>(string_.begin()._Ptr);
#endif
}

const char* String::getEnd() const {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  return string_.end()._Ptr;
#endif
}

char* String::getEnd() {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  return const_cast<char*>(string_.end()._Ptr);
#endif
}

void String::resize(string_size_t size) {
#if STRING_IMPL_CHAR
  if(string_ != nullptr) {
    delete[] string_;
  }

  string_ = new char[size];
#elif STRING_IMPL_STL
  string_.resize(static_cast<size_t>(size));
#endif
}

void String::erase(string_size_t pos, string_size_t count) {
#if STRING_IMPL_CHAR  
  memmove_s(string_ + pos, count, string_ + pos + count, count);

#elif STRING_IMPL_STL
  string_.erase(static_cast<size_t>(pos), static_cast<size_t>(count));
#endif
}

void String::pushFront(char ch) {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_.insert(string_.begin(), ch);
#endif
}

void String::popFront() {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_.erase(0, 1);
#endif
}

void String::popFront(string_size_t count) {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_.erase(count);
#endif
}

void String::pushBack(char ch) {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_.push_back(ch);
#endif
}

void String::popBack() {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_.pop_back();
#endif
}

void String::popBack(string_size_t count) {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  string_.erase(string_.end() - count, string_.end());
#endif
}

int String::parseInt() {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  return std::stoi(string_);
#endif
}

long String::parseLong() {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  return std::stol(string_);
#endif
}

float String::parseFloat() {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  return std::stof(string_);
#endif
}

double String::parseDouble() {
#if STRING_IMPL_CHAR

#elif STRING_IMPL_STL
  return std::stod(string_);
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

String String::operator+(const String string) {
  String str = *this;
  str.append(string);
  return str;
}

#if STL_IS_AVAILABLE
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
#endif
