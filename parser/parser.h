//
// Created by Defender on 2024/3/25.
//

#ifndef PROJECT_PARSER_PARSER_H_
#define PROJECT_PARSER_PARSER_H_
#include "../database/database.h"
#include<fstream>
#include<string>
#include<sstream>
class parser
{
 public:
  static std::vector<net*> m_parser();
  /*{
      std::vector<net*> network;
      std::string name = "";
      std::string source ="";
      int sort = 0;
      std::string gate = "";
      std::string drain = "";
      int m_wide = 0;
      int m_long = 0;
      int num_nmos = 0;
      int num_pmos = 0;
      std::string l = "";
      std::string w ="";
      std::string sort1="";
      std::string sort2="";
      std::vector<mos*> pmos;
      std::vector<mos*> nmos;
      std::ifstream ifs;
      ifs.open("/home/spiderman/project/work1/cell.spi",std::ios::in);
      if(!ifs.is_open())
      {
          std::cout << "fail to open the file" << std::endl;
      }
      else
      {
          std::cout << "hello" << std::endl;
          while(1)
          {
              std::string line;
              getline(ifs, line);
              if(line.empty())
                  break;
              else if (line.substr(0, 7) == ".SUBCKT")
              {
                  continue;
              }
              else if (line.substr(0,5) == ".ENDS")
              {
                  net* net1 = new net(num_pmos,num_nmos,pmos,nmos);
                  network.push_back(net1);
                  num_pmos = 0;
                  num_nmos = 0;
                  pmos.clear();
                  nmos.clear();
              }
              else
              {
                  std::istringstream is(line);
                  is >> name >> source >> gate >> drain >> sort1 >> sort2 >> l >> w;
                  name = name.substr(1,(name.size()-1)) ;
                  if(sort1 == "VSS")
                  {
                      num_nmos++;
                      sort = 0;
                  }
                  else
                  {
                      num_pmos++;
                      sort = 1;
                  }
                  if(l[l.size()-1] == 'n')
                      m_long = std::stof(l.substr(2,l.size()-3));
                  else
                      m_long = (std::stof(l.substr(2,l.size()-3)))*1000;
                  if(w[w.size()-1] == 'n')
                      m_wide = std::stof(w.substr(2,w.size()-3));
                  else
                      m_wide = (std::stof(w.substr(2,w.size()-3)))*1000;
                  if(sort == 0)
                  {
                      mos* n = new mos(name,sort,source,gate,drain,m_wide,m_long);
                      nmos.push_back(n);
                  }
                  else
                  {
                      mos* m = new mos(name,sort,source,gate,drain,m_wide,m_long);
                      pmos.push_back(m);
                  }
              }
          }
      }
      ifs.close();
      return network;
  }*/
  parser();
};

#endif //PROJECT_PARSER_PARSER_H_
