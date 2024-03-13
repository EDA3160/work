//
// Created by spiderman on 24-3-10.
//

#ifndef PROJECT_DATEBASE_H
#define PROJECT_DATEBASE_H


#include<iostream>
#include<vector>
class mos
{
    std::string m_name;
    int m_sort;
    std::string m_source;
    std::string m_gate;
    std::string m_drain;
    int w_wide;
    int w_long;
    int m_x;
    int m_f;
};
class net
{
    int num_pmos;
    std::vector<mos> pmos;
    int num_nmos;
    std::vector<mos> nmos;
};
#endif //PROJECT_DATEBASE_H
