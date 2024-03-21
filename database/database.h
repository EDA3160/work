
//
// Created by spiderman on 24-3-10.
//

#ifndef PROJECT_DATEBASE_H
#define PROJECT_DATEBASE_H

#include<iostream>
#include<vector>
class mos
{
public:
    mos();
    mos(std::string name,int sort,std::string source,std::string gate,std::string drain,int wide,int lon);
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
    net(int num_pmos,int num_nmos,std::vector<mos*> pmos,std::vector<mos*> nmos);
    int num_pmos;
    std::vector<mos*> pmos;
    int num_nmos;
    std::vector<mos*> nmos;
};
#endif //PROJECT_DATEBASE_H
