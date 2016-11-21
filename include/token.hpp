//
// Created by Tidyzq on 2016/11/20.
//

#ifndef __TOKEN_HPP__
#define __TOKEN_HPP__ 1

#include <string>

class Token {

public:

  enum Type {
    keywords,   // 保留字，如 def return 等等
    identifier, // 标识符，变量名或函数名
    number,     // 数字字面量
    string,     // 字符串字面量
    eof
  };

  static Token EndOfFile;

  Type getType() const;

  int getLineNumber() const;

  int getColumnNumber() const;

  std::string getText() const;

private:

  int _lineNumber;
  int _columnNumber;
  Type _type;
  std::string _text;

protected:

  Token(Type type, int line, int column, const std::string & text);

  friend class Lexer;

};

#endif // __TOKEN_HPP__
