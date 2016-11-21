//
// Created by Tidyzq on 2016/11/21.
//

#ifndef TIDYSCRIPT_PARSE_EXCEPTION_HPP
#define TIDYSCRIPT_PARSE_EXCEPTION_HPP


#include <exception>
#include <string>

class ParseException: public std::exception {

public:

  ParseException(int lineNo, int columnNo, std::string text);

  virtual const char *what() const throw() override;

private:

  std::string _msg;

};


#endif //TIDYSCRIPT_PARSE_EXCEPTION_HPP
