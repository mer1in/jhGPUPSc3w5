#ifndef EXCEPTION_H_
#define EXCEPTION_H_
#include <iostream>
#include <string>

using namespace std;

class Exception : public exception {

public:
   Exception(const string& msg) : msg_(msg) {}
  ~Exception() {}
   const char* what() {return(msg_.c_str());}
private:
   string msg_;
};

#endif // EXCEPTION_H_
