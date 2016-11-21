//
// Created by Tidyzq on 2016/11/20.
//

#define DEBUG

#include "lexer.hpp"
#include <string>
#include <iostream>
#include <sstream>

int main() {
  std::string str = "a7vn32&";
  std::istringstream input = std::istringstream(str);
  Lexer lexer(input);
  int i = 0;
  try {
    while (lexer.hasNext()) {
      Token token = lexer.next();
      std::cout << "type: " << token.getType() << std::endl;
      std::cout << "text: " << token.getText() << std::endl;
    }
  } catch (ParseException e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
