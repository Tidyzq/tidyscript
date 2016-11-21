//
// Created by Tidyzq on 2016/11/20.
//

#include "lexer.hpp"

// #define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

const std::string IGNORE_REGEX     = "[ \\t\\n]+|//.*";
const std::string KEYWORDS_REGEX   = "if|else|while|def|=|\\+|-|\\*|/|\\(|\\)|\\{|\\}";
const std::string IDENTIFIER_REGEX = "[A-Za-z][A-Za-z0-9_]*";
const std::string NUMBER_REGEX     = "[0-9]+(\\.[0-9]+)?";
const std::string STRING_REGEX     = "\"(\\\\\"|[^\"])*\"|'(\\\\'|[^'])*'";

const std::string REGEX_PATTERN    = "(" + IGNORE_REGEX     + ")|("
                                         + KEYWORDS_REGEX   + ")|("
                                         + IDENTIFIER_REGEX + ")|("
                                         + NUMBER_REGEX     + ")|("
                                         + STRING_REGEX     + ")";

const int IGNORE_INDEX     = 1;
const int KEYWORDS_INDEX   = 2;
const int IDENTIFIER_INDEX = 3;
const int NUMBER_INDEX     = 4;
const int STRING_INDEX     = 6;

std::regex Lexer::_regexPat = std::regex(REGEX_PATTERN);

Lexer::Lexer(std::istream &input) : _input(input), _lineCount(0) {
  _hasMore = !_input.eof();
#ifdef DEBUG
  std::cout << REGEX_PATTERN << std::endl;
  if (!_hasMore) {
    std::cout << "input is empty" << std::endl;
  }
#endif
}

Token Lexer::next() throw(ParseException) {
  if (_queue.empty() && (!_hasMore || !fillQueue(1))) {
    return Token::EndOfFile;
  }
  Token rst = _queue.front();
  _queue.pop();
  return rst;
}

bool Lexer::hasNext() const {
  return !_queue.empty() || _hasMore;
}

bool Lexer::fillQueue(int num) throw(ParseException) {
  int count = 0;
  while (count < num) {
    if (!_hasMore) return false;
    count += readLine();
  }
  return true;
}

int Lexer::readLine() throw(ParseException) {
  std::string line;
  std::smatch sm;
  int columnCount = 0, tokenCount = 0;
  getline(_input, line);
  _hasMore = !_input.eof();
  while (line.size()) {
    if (!std::regex_search(line, sm, _regexPat, std::regex_constants::match_continuous)) {
      throw ParseException(_lineCount, columnCount, line);
    }
    tokenCount += addToken(_lineCount, columnCount, sm);
    columnCount += sm.length();
    line = sm.suffix().str();
#ifdef DEBUG
    std::cout << "\033[1;31mbold red text\033[0m\n";
    std::cout << "str: " << line << std::endl;
#endif
  }
  ++_lineCount;
  return tokenCount;
}

bool Lexer::addToken(int lineNo, int columnNo, const std::smatch & match) throw(ParseException) {
  Token::Type type;
  if (match[IGNORE_INDEX] != "") {
    return false; // ignore
  } else if (match[IDENTIFIER_INDEX] != "") {
    type = Token::identifier;
  } else if (match[KEYWORDS_INDEX] != "") {
    type = Token::keywords;
  } else if (match[NUMBER_INDEX] != "") {
    type = Token::number;
  } else if (match[STRING_INDEX] != "") {
    type = Token::string;
  } else {
    throw ParseException(lineNo, columnNo, match[0]);
  }
#ifdef DEBUG
  std::cout << "match: ";
  for (auto submatch:match) {
    std::cout << "[" << submatch << "] ";
  }
  std::cout << std::endl << "line: " << lineNo << " column: " << columnNo << std::endl;
#endif
  _queue.push(Token(type, lineNo, columnNo, match[0]));
  return true;
}
