#include "database.h"
//
// Created by spiderman on 24-3-10.
//
mos::mos()
{
    this->m_f = 0;
    this->m_x = -1;
    this->m_long = 0;
    this->m_wide = 0;
}
mos::mos(std::string name,int sort,std::string source,std::string gate,std::string drain,int wide,int lon)
{
    this->m_x = -1;
    this->m_f = 0;
    this->m_drain = drain;
    this->m_gate = gate;
    this->m_source = source;
    this->m_wide =wide;
    this->m_sort = sort;
    this->m_name = name;
    this->m_long = lon;
}
net::net()
{
    this->num_nmos = 0;
    this->num_pmos = 0;
}
net::net(int num_pmos,int num_nmos,std::vector<mos*> pmos,std::vector<mos*> nmos,std::string name)
{
    this->num_pmos = num_pmos;
    this->num_nmos = num_nmos;
    this->pmos = pmos;
    this->nmos = nmos;
    this->name = name;
}
net& net::operator=(const net* net)
{
    this->name=net->name;
    for(auto it=net->nmos.begin();it<nmos.end();++it)// 感觉有问题啊
{
	this->nmos.push_back(*it);
}
    for(auto it=net->pmos.begin();it<pmos.end();++it)
{
	this->pmos.push_back(*it);
}
    this->num_nmos=net->num_nmos;
    this->num_pmos=net->num_pmos;
    return *this;
}