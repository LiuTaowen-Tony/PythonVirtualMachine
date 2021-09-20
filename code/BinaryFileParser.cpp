#include <assert.h>
#include <stdio.h>

#include "BinaryFileParser.hpp"
#include "../object/MyInt.hpp"

BinaryFileParser::BinaryFileParser(BufferedInputStream *buf_file_stream) {
  file_stream = buf_file_stream;
}

CodeObject *BinaryFileParser::parse() {
  int magic_number = file_stream->read_int();
  printf("magic number is 0x%x\n", magic_number);
  int moddate = file_stream->read_int();
  printf("moddate is 0x%x\n", moddate);

  char object_type = file_stream->read();

  if (object_type == 'c') {
    CodeObject *result = get_code_object();
    printf("parse OK!\n");
    return result;
  }

  return NULL;
}

CodeObject *BinaryFileParser::get_code_object() {
  int argcount = file_stream->read_int();
  int nlocals = file_stream->read_int();
  int stacksize = file_stream->read_int();
  int flags = file_stream->read_int();
  printf("flags is 0x%x\n", flags);

  MyString *byte_codes = get_byte_codes();
  MyArray<MyObject *> *consts = get_consts();
  MyArray<MyObject *> *names = get_names();
  MyArray<MyObject *> *var_names = get_var_names();
  MyArray<MyObject *> *free_vars = get_free_vars();
  MyArray<MyObject *> *cell_vars = get_cell_vars();

  MyString *file_name = get_file_name();
  MyString *module_name = get_name();
  int begin_line_no = file_stream->read_int();
  MyString *lnotab = get_no_table();

  return new CodeObject(argcount, nlocals, stacksize, flags, byte_codes, consts,
                        names, var_names, free_vars, cell_vars, file_name,
                        module_name, begin_line_no, lnotab);
}

MyString *BinaryFileParser::get_string() {
  int length = file_stream->read_int();
  char *str_value = new char[length];

  for (int i = 0; i < length; i++) {
    str_value[i] = file_stream->read();
  }

  MyString *s = new MyString(str_value, length);
  delete[] str_value;

  return s;
}

MyString *BinaryFileParser::get_name() {
  char ch = file_stream->read();

  if (ch == 's') {
    return get_string();
  } else if (ch == 't') {
    MyString *str = get_string();
    _string_table.push_back(str);
    return str;
  } else if (ch == 'R') {
    return _string_table.at(file_stream->read_int());
  }

  return NULL;
}

MyString *BinaryFileParser::get_file_name() { return get_name(); }

MyString *BinaryFileParser::get_byte_codes() {
  assert(file_stream->read() == 's');

  return get_string();
}

MyString *BinaryFileParser::get_no_table() {
  char ch = file_stream->read();

  if (ch != 's' && ch != 't') {
    file_stream->unread();
    return NULL;
  }

  return get_string();
}

MyArray<MyObject *> *BinaryFileParser::get_consts() {
  if (file_stream->read() == '(') {
    return get_tuple();
  }

  file_stream->unread();
  return NULL;
}

MyArray<MyObject *> *BinaryFileParser::get_names() {
  if (file_stream->read() == '(') {
    return get_tuple();
  }

  file_stream->unread();
  return NULL;
}

MyArray<MyObject *> *BinaryFileParser::get_var_names() {
  if (file_stream->read() == '(') {
    return get_tuple();
  }

  file_stream->unread();
  return NULL;
}

MyArray<MyObject *> *BinaryFileParser::get_free_vars() {
  if (file_stream->read() == '(') {
    return get_tuple();
  }

  file_stream->unread();
  return NULL;
}

MyArray<MyObject *> *BinaryFileParser::get_cell_vars() {
  if (file_stream->read() == '(') {
    return get_tuple();
  }

  file_stream->unread();
  return NULL;
}

MyArray<MyObject *> *BinaryFileParser::get_tuple() {
  int length = file_stream->read_int();
  MyString *str;

  MyArray<MyObject *> *list = new MyArray<MyObject  *>(length);
  for (int i = 0; i < length; i++) {
    char obj_type = file_stream->read();

    switch (obj_type) {
    case 'c':
      printf("got a code object\n");
      list->push_back(get_code_object());
      break;
    case 'i':
      list->push_back(new MyInt(file_stream->read_int()));
      break;
    case 'N':
      list->push_back(NULL);
      break;
    case 't':
      str = get_string();
      list->push_back(str);
      _string_table.push_back(str);
      break;
    case 's':
      list->push_back(get_string());
      break;
    case 'R':
      list->push_back(_string_table.at(file_stream->read_int()));
      break;
    default:
      printf("parser, unrecognized type : %c\n", obj_type);
    }
  }

  return list;
}
