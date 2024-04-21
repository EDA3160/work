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
net::net(const net& other)
{
    this->num_pmos = other.num_pmos;
    this->num_nmos = other.num_nmos;
    this->pmos.clear();
    for (int i = 0; i < other.pmos.size(); i++) {
        this->pmos.push_back(new mos(*other.pmos[i]));
    }
    this->nmos.clear();
    for (int i = 0; i < other.nmos.size(); i++) {
        this->nmos.push_back(new mos(*other.nmos[i]));
    }
    this->name = other.name;
}

net::~net() {
    for (int i = 0; i < pmos.size(); i++) {
        delete pmos[i];
    }
    for (int i = 0; i < nmos.size(); i++) {
        delete nmos[i];
    }
}

net& net::operator=(const net& other)
{
    if (this == &other) 
        {                 
            return *this;
        }                 // 检查自赋值情况

        // 先清空当前的指针向量
        for (mos *ptr : this->nmos) 
        {
            delete ptr;
        }
        nmos.clear();

        // 复制 other 中的指针向量
        for (mos* ptr : other.nmos) 
        {
            mos* newPtr = new mos(*ptr);  // 使用默认的拷贝构造
            this->nmos.push_back(newPtr);     // 将新对象的指针添加到当前指针向量中
        }
        //pmos再来一次
        for (mos *ptr : this->pmos) 
        {
            delete ptr;
        }
        nmos.clear();

        // 复制 other 中的指针向量
        for (mos* ptr : other.pmos) 
        {
            mos* newPtr = new mos(*ptr);  // 使用默认的拷贝构造
            this->pmos.push_back(newPtr);     // 将新对象的指针添加到当前指针向量中
        }

        return *this;
}