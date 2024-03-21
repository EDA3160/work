#include <iostream>
#include "./parser/parser.h"
#include <fstream>
int main()
{
  
  parser readfile;
  std::vector<mos> Moses;
  readfile.parsers(Moses);
  std::ifstream li("cells.spi",std::ios::in);
  if(li.is_open())
  {
    std::cout<<"open in main\n";
  }
  std::string line;
  std::getline(li,line);
  li.close();
  for(auto it:Moses)
  {
    it.ShowData();
    std::cout<<"-----------------------"<<std::endl;
  }
  return 0;
}