#include "CodeObject.hpp"

CodeObject::CodeObject(int argcount, int nlocals, int stacksize, int flag,
                       MyString *bytecodes, MyArray<MyObject *> *consts,
                       MyArray<MyObject *> *names, MyArray<MyObject *> *varnames,
                       MyArray<MyObject *> *freevars,
                       MyArray<MyObject *> *cellvars, MyString *file_name,
                       MyString *co_name, int lineno, MyString *notable)
    : _argcount(argcount), _nlocals(nlocals), _stack_size(stacksize),
      _flag(flag), _bytecodes(bytecodes), _names(names), _consts(consts),
      _var_names(varnames), _free_vars(freevars), _cell_vars(cellvars),
      _co_name(co_name), _file_name(file_name), _lineno(lineno),
      _notable(notable) {}