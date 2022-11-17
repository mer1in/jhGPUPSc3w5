#pragma once
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

