//
// Created by Tidyzq on 2016/11/21.
//

#include "parse_exception.hpp"
#include <sstream>

ParseException::ParseException(int lineNo, int columnNo, std::string text) {
  std::stringstream stream;
  stream << "Parse error in " << lineNo << ":" << columnNo << " \"" << text << "\"";
  _msg = stream.str();
}

const char *ParseException::what() const throw() {
  return _msg.c_str();
}
