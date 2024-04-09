//
// Created by Defender on 2024/3/31.
//
#include "placement.h"
#include "database.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

void placement:: init_SA()
{

;
}


int placement::get_cost(net* this_net){
    int f_cost=0;
    for(int i=0;i<this_net->num_pmos;i++)
    {
        f_cost=std::max(f_cost,this_net->pmos[i]->m_x);
    }
    for(int i=0;i<this_net->num_nmos;i++)
    {
        f_cost=std::max(f_cost,this_net->nmos[i]->m_x);
    }
    return f_cost;


}

void placement::swap_mos(){
    int method=rand()%2;
    //交换
    //0表示交换pmos，1表示交换nmos
    if(method==0)
    {
        int random1=rand()%pmos_loc.size();
        int random2=rand()%pmos_loc.size();
        std::swap(pmos_loc[random1],pmos_loc[random2]);
    }
    else if(method==1)
    {
        int random1=rand()%nmos_loc.size();
        int random2=rand()%nmos_loc.size();
        std::swap(nmos_loc[random1],nmos_loc[random2]);
    }

}

//产生随机解
void placement::GenerateRandomSolutions()
{
        std::random_device rd;
        std::mt19937 rng(rd());
        for(int i=0;i<pmos_loc.size();i++)
        {
                pmos_loc[i]=i;
        }
        std::shuffle(pmos_loc.begin(), pmos_loc.end(),rng);
        for(int i=0;i<nmos_loc.size();i++)
        {
            nmos_loc[i]=i;
        }
        std::shuffle(nmos_loc.begin(), nmos_loc.end(),rng);

}

//依据loc布局
void placement::layout(net* this_net)
{
    int num_nmos=0;
    int num_pmos=0;
    int x_p=1;
    int x_n=1;
    std::string p_right;
    std::string n_right;

    while (num_nmos < this_net->num_nmos && num_pmos < this_net->num_pmos)
    {
        //除布局第一个mos外，布局mos时判断是否可重叠
        if(num_pmos>0)
        {
            //不可重叠
            if(this_net->pmos[pmos_loc[num_pmos]]->m_source!=p_right){
                x_p++;
            }
            //可重叠但是上一个nmos占用该x坐标并且栅极不相等
            else if(x_p==this_net->nmos[nmos_loc[num_nmos]]->m_x-1&&this_net->nmos[nmos_loc[num_nmos-1]]->m_gate!=this_net->pmos[pmos_loc[num_pmos]]->m_gate){
                x_p++;
            }

        }
        if(num_nmos>0)
        {
            if(this_net->nmos[nmos_loc[num_nmos]]->m_source!=n_right)
                x_n++;
        }

        //布局pmos
        this_net->pmos[pmos_loc[num_pmos]]->m_x=x_p++;
        //判断栅极是否可连接
        if(this_net->nmos[nmos_loc[num_nmos]]->m_gate!=this_net->pmos[pmos_loc[num_pmos]]->m_gate)
            x_n++;
        //布局nmos
        this_net->nmos[nmos_loc[num_nmos]]->m_x=x_n++;
        //记录右端线网
        p_right=this_net->pmos[pmos_loc[num_pmos]]->m_drain;
        n_right=this_net->nmos[nmos_loc[num_nmos]]->m_drain;
        num_nmos++;
        num_pmos++;
    }

    //nmos布局完pmos剩余的情况
    while (num_pmos<this_net->num_pmos)
    {
        if(num_pmos>0)
        {
            if(this_net->pmos[pmos_loc[num_pmos]]->m_source!=p_right)
                x_p++;
        }
        this_net->pmos[pmos_loc[num_pmos]]->m_x=x_p++;
        p_right=this_net->pmos[pmos_loc[num_pmos]]->m_drain;
        num_pmos++;
    }
    //pmos布局完nmos剩余的情况
    while (num_nmos<this_net->num_nmos)
    {
        if(num_nmos>0)
        {
            if(this_net->nmos[nmos_loc[num_nmos]]->m_source!=n_right)
                x_n++;
        }
        this_net->nmos[nmos_loc[num_nmos]]->m_x=x_n++;
        n_right=this_net->nmos[nmos_loc[num_nmos]]->m_drain;
        num_nmos++;
    }





}

void placement::slover()
{
    srand(time(nullptr));
    for(int a=0;a<network.size();a++)
    {
        pmos_loc.resize(network[a]->num_nmos);
        nmos_loc.resize(network[a]->num_pmos);
        best_nmos_loc.resize(network[a]->num_nmos);
        best_pmos_loc.resize(network[a]->num_pmos);
        GenerateRandomSolutions();
        layout(network[a]);
        cost= get_cost(network[a]);


    }
}