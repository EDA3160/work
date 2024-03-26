//
// Created by Defender on 2024/3/25.
//

#ifndef PROJECT_DATABASE_DATABASE_H_
#define PROJECT_DATABASE_DATABASE_H_
#include<iostream>
#include<vector>
class mos
{
 public:
  mos();
  /*{
      this->m_f = 0;
      this->m_x = -1;
      this->m_long = 0;
      this->m_wide = 0;
  }*/
  mos(std::string name,int sort,std::string source,std::string gate,std::string drain,int wide,int lon);
  /*{
      this->m_x = -1;
      this->m_f = 0;
      this->m_drain = drain;
      this->m_gate = gate;
      this->m_source = source;
      this->m_wide =wide;
      this->m_sort = sort;
      this->m_name = name;
      this->m_long = lon;
  }*/
  std::string m_name;
  int m_sort;
  std::string m_source;
  std::string m_gate;
  std::string m_drain;
  int m_wide;
  int m_long;
  int m_x;
  int m_f;
};
class net
{
 public:
  net();
  /*{
      this->num_nmos = 0;
      this->num_pmos = 0;
  }*/
  net(int num_pmos,int num_nmos,std::vector<mos*> pmos,std::vector<mos*> nmos);
  /*{
      this->num_pmos = num_pmos;
      this->num_nmos = num_nmos;
      this->pmos = pmos;
      this->nmos = nmos;
  }*/
  int num_pmos;
  std::vector<mos*> pmos;
  int num_nmos;
  std::vector<mos*> nmos;
};
#endif //PROJECT_DATABASE_DATABASE_H_
