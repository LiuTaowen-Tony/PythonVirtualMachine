#ifndef CODE_OBJECT_HPP
#define CODE_OBJECT_HPP

#include "../object/MyObject.hpp"
#include "../object/MyString.hpp"
#include "../utils/MyArray.hpp"

class CodeObject : public MyObject {
public:
    int _argcount;
    int _nlocals;
    int _stack_size;
    int _flag;

    MyString* _bytecodes;
    MyArray<MyObject*>*  _names;
    MyArray<MyObject*>*  _consts;
    MyArray<MyObject*>*  _var_names;

    MyArray<MyObject*>*  _free_vars;
    MyArray<MyObject*>*  _cell_vars;

    MyString* _co_name;
    MyString* _file_name;

    int _lineno;
    MyString* _notable;
    CodeObject(int argcount, int nlocals, int stacksize, int flag, MyString* bytecodes,
        MyArray<MyObject*>* consts, MyArray<MyObject*>* names,
        MyArray<MyObject*>* varnames,
        MyArray<MyObject*>* freevars, MyArray<MyObject*>* cellvars,
        MyString* file_name, MyString* co_name, int lineno, MyString* notable);
};

#endif