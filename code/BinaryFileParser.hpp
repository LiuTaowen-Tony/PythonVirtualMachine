#ifndef BINARY_FILE_PARSER_HPP
#define BINARY_FILE_PARSER_HPP

#include "CodeObject.hpp"
#include "../object/MyObject.hpp"
#include "../object/MyString.hpp"
#include "../utils/BufferedInputStream.hpp"
#include "../utils/MyArray.hpp"

class BinaryFileParser {
private:
  BufferedInputStream *file_stream;
  int cur;
  MyArray<MyString *> _string_table;

public:
  BinaryFileParser(BufferedInputStream *stream);

public:
  CodeObject *parse();
  CodeObject *get_code_object();
  MyString *get_byte_codes();
  MyString *get_no_table();
  int get_int();
  MyString *get_string();
  MyString *get_name();

  MyString *get_file_name();

  MyArray<MyObject *> *get_consts();
  MyArray<MyObject *> *get_names();
  MyArray<MyObject *> *get_var_names();
  MyArray<MyObject *> *get_free_vars();
  MyArray<MyObject *> *get_cell_vars();
  MyArray<MyObject *> *get_tuple();
};

#endif