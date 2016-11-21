//
// Created by Tidyzq on 2016/11/20.
//

#ifndef __LEXER_HPP__
#define __LEXER_HPP__ 1


#include <string>
#include <istream>
#include <queue>
#include <regex>
#include "token.hpp"
#include "parse_exception.hpp"

class Lexer {

public:

  Lexer(std::istream & input);

  Token next() throw(ParseException);
  bool hasNext() const;

private:

  static std::regex _regexPat;

  std::istream & _input;
  std::queue<Token> _queue;
  int _lineCount;
  bool _hasMore;

  bool fillQueue(int num) throw(ParseException);

protected:

  int readLine() throw(ParseException);

  bool addToken(int lineNo, int columnNo, const std::smatch & match) throw(ParseException);

};

#endif // __LEXER_HPP__
