#include<iostream>
#include"parser/parser.h"
#include"database/database.h"
int main()
{
  parser p;
  std::vector<net*> hello = p.m_parser();
  int a = hello.size();
  for(int i = 0;i < a ;i++)
  {
    std::cout<<"------------------------------------" <<std::endl;
    std::cout << "num_pmos:" <<hello[i]->num_pmos <<std::endl;
    for(int j = 0; j < (hello[i]->num_pmos);j++)
    {
      std::cout << "name:" <<hello[i]->pmos[j]->m_name <<std::endl;
      std::cout << "sort:" <<hello[i]->pmos[j]->m_sort <<std::endl;
      std::cout << "source:"<<hello[i]->pmos[j]->m_source<<std::endl;
      std::cout << "gate:" <<hello[i]->pmos[j]->m_gate<<std::endl;
      std::cout << "drain:"<<hello[i]->pmos[j]->m_drain<<std::endl;
      std::cout << "long:" <<hello[i]->pmos[j]->m_long<<std::endl;
      std::cout << "wide:" <<hello[i]->pmos[j]->m_wide<<std::endl;
      std::cout << "x:"<<hello[i]->pmos[j]->m_x<<std::endl;
      std::cout << "f:" <<hello[i]->pmos[j]->m_f<<std::endl;
    }
    std::cout << "num_nmos:" <<hello[i]->num_nmos <<std::endl;
    for(int j = 0; j < (hello[i]->num_nmos);j++)
    {
      std::cout << "name:" <<hello[i]->nmos[j]->m_name <<std::endl;
      std::cout << "sort:" <<hello[i]->nmos[j]->m_sort <<std::endl;
      std::cout << "source:"<<hello[i]->nmos[j]->m_source<<std::endl;
      std::cout << "gate:" <<hello[i]->nmos[j]->m_gate<<std::endl;
      std::cout << "drain:"<<hello[i]->nmos[j]->m_drain<<std::endl;
      std::cout << "long:" <<hello[i]->nmos[j]->m_long<<std::endl;
      std::cout << "wide:" <<hello[i]->nmos[j]->m_wide<<std::endl;
      std::cout << "x:"<<hello[i]->nmos[j]->m_x<<std::endl;
      std::cout << "f:" <<hello[i]->nmos[j]->m_f<<std::endl;
    }
  }
  return 0;
}

