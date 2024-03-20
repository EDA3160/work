#include <iostream>
#include "./parser/parser.h"
int main()
{
  
  std::vector<mos> Moses;
  
  parser read;
  read.parsers(Moses);
  std::string a{"wdnmd"};
  
  std::cout << "hello1  2 " <<a<<" "<<""<< std::endl;
  return 0;
}