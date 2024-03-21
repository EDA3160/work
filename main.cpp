#include <iostream>
#include "./parser/parser.h"
int main()
{
  
  std::vector<mos> Moses;
  
  parser readflie;
  
  std::vector<net*> network=readflie.m_parser();

  std::string a{"wdnmd"};
  
  std::cout << "hello1  2 " <<network.at(0)<<" "<<""<< std::endl;
  return 0;
}