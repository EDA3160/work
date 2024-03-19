//
// Created by spiderman on 24-3-10.
//

#ifndef PROJECT_DATABASE_H
#define PROJECT_DATABASE_H


#include<iostream>
#include<vector>
class mos
{
    public:
    mos(){}
    mos(const mos &mos_i){}
    ~mos(){}
    std::string m_name;
    int m_sort;
    std::string m_source;
    std::string m_gate;
    std::string m_drain;
    float w_width;
    float w_length;
    int m_x;//x_loc
    int m_f;//is_roll
};
class net
{
    int num_pmos;
    std::vector<mos> pmos;
    int num_nmos;
    std::vector<mos> nmos;
};
#endif //PROJECT_DATABASE_H
