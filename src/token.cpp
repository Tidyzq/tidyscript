//
// Created by Tidyzq on 2016/11/20.
//

#include "token.hpp"

Token Token::EndOfFile = Token(eof, -1, -1, "");

Token::Type Token::getType() const {
  return _type;
}

int Token::getLineNumber() const {
  return _lineNumber;
}

int Token::getColumnNumber() const {
  return _columnNumber;
}

std::string Token::getText() const {
  return _text;
}

Token::Token(Token::Type type, int line, int column, const std::string &text)
  : _type(type), _lineNumber(line), _columnNumber(column), _text(text) {

}
