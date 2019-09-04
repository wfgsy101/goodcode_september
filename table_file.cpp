#include "table_file.h"

using namespace goodcoder::table_file;

TableFile::TableFile(): _lineno(0) {
}

TableFile::~TableFile() {
  close();
}

bool TableFile::open(const std::string& file) {
  if (_fin.is_open()) {
    CWARNING_LOG("File is opened already");
    return false;
  }

  _fin.open(file, std::ios::in);
  if (!_fin.is_open()) {
    CWARNING_LOG("Cannot open file: %s", file.c_str());
    return false;
  }
  _lineno = 0;
  return true;
}

void TableFile::close() {
  if (_fin.is_open())
    _fin.close();
}

//bool TableFile::parse_field(const std::string& line, size_t begin) {
//  if (begin != line.npos) {
//    CWARNING_LOG("Parsing failed, extra string");
//    return false;
//  }
//  return true;
//}
