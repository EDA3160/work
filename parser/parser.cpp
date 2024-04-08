//
// Created by Defender on 2024/3/10.
//
#include "parser.h"
parser::parser() {}
std::vector<net*> parser::m_parser()
{
    std::vector<net*> network;
    std::string name;
    std::string name1;
    std::string source;
    int sort;
    std::string gate;
    std::string drain;
    int m_wide;
    int m_long;
    int num_nmos=0;
    int num_pmos=0;
    std::string l;
    std::string w;
    std::string sort1;
    std::string sort2;
    int m_long1;
    int m_wide1;
    std::vector<mos*> pmos;
    std::vector<mos*> nmos;
    std::ifstream ifs;
    ifs.open("../cells.spi",std::ios::in);
    if(!ifs.is_open())
    {
        std::cout << "fail to open the file" << std::endl;
    }
    else
    {
        while(1)
        {
            std::string line;
            getline(ifs, line);
            if(line =="")
            break;
            else if (line.substr(0, 7) == ".SUBCKT")
            {
                std::istringstream is(line);
                is >> name >> name1;
            }
            else if (line.substr(0,5) == ".ENDS")
            {
                 net* net1 = new net(num_pmos,num_nmos,pmos,nmos,name1);
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
                    m_long1 = std::stof(l.substr(2,l.size()-3));
                else
                    m_long1 = (std::stof(l.substr(2,l.size()-3)))*1000;
                if(l[0] == 'l' || l[0] == 'L')
                    m_long = m_long1;
                else
                    m_wide = m_long1;
                if(w[w.size()-1] == 'n')
                    m_wide1 = std::stof(w.substr(2,w.size()-3));
                else
                    m_wide1 = (std::stof(w.substr(2,w.size()-3)))*1000;
                if(w[0] == 'w' || w[0] == 'W')
                    m_wide = m_wide1;
                else
                    m_long = m_wide1;
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
}
