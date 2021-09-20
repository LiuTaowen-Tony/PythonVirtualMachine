#include "MyString.hpp"

MyString::MyString(const MyString& other){
  _value = other.raw_value();
}

MyString& MyString::operator=(const MyString& other){
  if (this == &other){
    return *this;
  }
  _value = other.raw_value();
  return *this;
}