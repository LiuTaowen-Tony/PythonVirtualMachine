#ifndef _MY_INT_HPP
#define _MY_INT_HPP

#include "MyObject.hpp"

class MyInt : public MyObject {
private:
  int _value;

public:
  MyInt(int x): _value(x) {}
  int value() { return _value; }
};

#endif