//
// Created by Defender on 2024/3/31.
//
#include "placement.h"
#include "database.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <random>

placement::placement(std::vector<net*> m_network) :network(m_network){};


void placement:: init_SA(double &T_descent_rate,double &T,net* this_net)
{
    
    T=100+T_lambda*log(1+(static_cast<double>(this_net->num_nmos+this_net->num_pmos)));//类型转换
    T_descent_rate=T_descent_lambda*exp(-(1/static_cast<double>(this_net->num_nmos+this_net->num_pmos)));//数量越大下降越慢 温度高的时候尽可能小
    

}


double placement::get_cost_0(net* this_net){
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
double placement::get_cost_1(int action,net* this_net,mos* mos,double eff_T) //这里传了这么多参数进来是想就算局部变化量的 我鸽了：）
{
    
    double i =get_cost_0(this_net);//前代价
    double j = i;                  //后代价
    double differ_j_i;//两次代价的差值
    std::default_random_engine e;//给随机数
    std::uniform_int_distribution<int> axis(0,this_net->num_nmos); // 左闭右闭区间

    if(action==0)
    {
        differ_j_i=0;
    }
//    else if(action==1)
//    {
//        mos->m_x++;
//        layout(this_net);
//        j=get_cost_0(this_net);
//    }
    else if(action==1)
    {
        swap_mos();
        layout(this_net);
        j=get_cost_0(this_net);
    }
    else if(action==2)
    {
        mos->m_f^=1; //旋转
        std::swap(mos->m_drain,mos->m_source);//由于cost函数的单调目前这玩意好像没有什么实质性作用啊啊(#｀-_ゝ-)
        layout(this_net);
        j=get_cost_0(this_net);
    }
    differ_j_i=j-i;
    if(differ_j_i>=0)
        return 1;
    return exp((differ_j_i))*eff_T;  //差别越小接受率越高 differ_j_i不为1是都是负数 越接近0返回的值越接近1也越容易被接受 eff_T是因为温度越小越难接受差解
}                                    

void placement::swap_mos(){
    int method=rand()%3;
    //交换
    //0表示交换pmos，1表示交换nmos,2表示都换
    if(method==0)
    {
        int random1=rand()%pmos_loc.size();
        int random2=rand()%pmos_loc.size();
        while (random1==random2)
            random2=rand()%pmos_loc.size();
        std::swap(pmos_loc[random1],pmos_loc[random2]);
    }
    else if(method==1)
    {
        int random1=rand()%nmos_loc.size();
        int random2=rand()%nmos_loc.size();
        while (random1==random2)
            random2=rand()%nmos_loc.size();
        std::swap(nmos_loc[random1],nmos_loc[random2]);
    }
    else if(method==2)
    {
        if(nmos_loc.size()>=pmos_loc.size())
        {
            int random1=rand()%pmos_loc.size();
            int random2=rand()%pmos_loc.size();
            while (random1==random2)
                random2=rand()%pmos_loc.size();
            std::swap(pmos_loc[random1],pmos_loc[random2]);
            std::swap(nmos_loc[random1],nmos_loc[random2]);
        }
        else{
            int random1=rand()%nmos_loc.size();
            int random2=rand()%nmos_loc.size();
            while (random1==random2)
                random2=rand()%nmos_loc.size();
            std::swap(pmos_loc[random1],pmos_loc[random2]);
            std::swap(nmos_loc[random1],nmos_loc[random2]);

        }
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
            else if(x_p==this_net->nmos[nmos_loc[num_nmos-1]]->m_x&&this_net->nmos[nmos_loc[num_nmos-1]]->m_gate!=this_net->pmos[pmos_loc[num_pmos]]->m_gate){
                x_p++;
            }

        }
        //布局pmos
        this_net->pmos[pmos_loc[num_pmos]]->m_x=x_p++;

        if(num_nmos>0)
        {
            if(this_net->nmos[nmos_loc[num_nmos]]->m_source!=n_right){
                x_n++;
            }
            else if(x_n==this_net->pmos[pmos_loc[num_pmos-1]]->m_x&&this_net->pmos[pmos_loc[num_pmos-1]]->m_gate!=this_net->nmos[nmos_loc[num_nmos]]->m_gate){
                x_n++;
            }
        }


        //判断栅极是否可连接
        if(x_n==this_net->pmos[pmos_loc[num_pmos]]->m_x&&this_net->pmos[pmos_loc[num_pmos]]->m_gate!=this_net->nmos[nmos_loc[num_nmos]]->m_gate){
            x_n++;
        }
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

void placement::Slover()
{
    srand(time(nullptr));
    for(int a=0;a<network.size();a++)
    {
        pmos_loc.resize(network[a]->num_nmos);
        nmos_loc.resize(network[a]->num_pmos);
        best_nmos_loc.resize(network[a]->num_nmos);
        best_pmos_loc.resize(network[a]->num_pmos);
        std::cout<<"1"<<std::endl;//debug的 a==6时候会出现vectorout of range
        GenerateRandomSolutions();
        std::cout<<"2"<<std::endl;
        layout(network[a]);
        std::cout<<"3"<<std::endl;
        std::cout<<"-------------退火--------------"<<a<<"-------------退火--------------"<<std::endl;
        init_SA(T_descent_rate,T,network[a]);//开始模拟退火
        run_SA(T_descent_rate,T,network[a]);
        std::cout<<"end"<<std::endl;


    }
}

double placement::action(double max_T,double &T_descent_rate,double &T,net* this_net)//返回一个新的下降率 在温度高的时候要尽可能小 得到一个优秀解的时候要尽可能的大
{
    std::default_random_engine e;//给随机数
    std::uniform_real_distribution<double> double_u(0,1); // 左闭右闭区间
    std::uniform_int_distribution<int> int_u(0,2);//1是移动 2是交换 3是反转  0是不动
    e.seed(time(0));
    double temp=get_cost_0(this_net);
    double eff_T = T/max_T; //反应退火的进程 温度越低越小
    int action_int;
    double accept_rate;
    for(auto& nmos:this_net->nmos)
    {
        net temp_net = *this_net;//    需要给重载个赋值来存储临时的state 用于还原  所以database我重载=号了
        action_int=int_u(e);
        accept_rate=get_cost_1(action_int,this_net,nmos,eff_T);//进行随机解 并获得局部更改后的代价参数 返回接受率 如果比原来更好就大于1
        if(accept_rate<1&&action_int)
        {
            if(eff_T*(accept_rate) < double_u(e))//不接受的话撤回操作   温度高的话接受率高    温度低接受率低    
            {
                *this_net = temp_net;
            }
        }
    }
    for(auto& pmos:this_net->pmos)//   pmos同理
    {
        net temp_net = *this_net;
        action_int=int_u(e);
        accept_rate=get_cost_1(action_int,this_net,pmos,eff_T);
        if(accept_rate<1)
        {
            if(eff_T*(accept_rate) < double_u(e))  
            {
                *this_net = temp_net;
            }
        }
    }

    return  T_descent_rate*(exp((get_cost_0(this_net)-temp)/temp)); //根据全局的好坏来调整下降率 cost0怎么归一

}

void placement::run_SA(double &T_descent_rate,double &T,net* this_net)
{
   double max_T = T;// 定义一个最大温度
    //std::cout<<T/max_T<<" "<<std::endl;
    while(T>1.05)
    {
        double differ_T=0;
        while(differ_T<(5*T/max_T)&&T>1)
        {
            //std::cout<<T<<" ";
            T_descent_rate=action(max_T,T_descent_rate,T,this_net);
            differ_T=T*(1-T_descent_rate);//温度下降量
            //std::cout<<T*(1-T_descent_rate)<<" "<<std::endl;

        }
        T-=differ_T;

    }

    
};



