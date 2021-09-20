#ifndef _MY_STRING_HPP
#define _MY_STRING_HPP

#include "MyObject.hpp"
#include "../utils/MyArray.hpp"
#include <vector>


class MyString : public MyObject {
private:
  MyArray<char> _value;
public:
  MyString(const char * v){
    std::copy(v, v + std::strlen(v), std::back_inserter(_value));
  }
  MyString(const char * v, const int length){
    std::copy(v, v + length, std::back_inserter(_value));
  };
  MyString(const MyString& other);
  MyString& operator=(const MyString& other);
  ~MyString(){}

  const std::vector<char> raw_value() const {return _value;}
  int length() const {return _value.size();}
};

#endif