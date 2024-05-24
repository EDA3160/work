//
// Created by Defender on 2024/3/31.
//
#include "placement.h"



placement::placement(std::vector<net*> m_network) :network(m_network){};


void placement:: init_SA(double &T_descent_rate,double &T,net* this_net)
{
    std::cout<<"run_into_init_SA"<<std::endl;
    T=100+T_lambda*log(1+(static_cast<double>(this_net->num_nmos+this_net->num_pmos)));//类型转换
    T_descent_rate=0.95;

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
double placement::get_cost_1(int action,net* this_net,mos* mos) //这里传了这么多参数进来是想就算局部变化量的 我鸽了：）
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
    else if(action==1||action==2)
    {
        swap_mos(this_net);
        layout(this_net);
        j=get_cost_0(this_net);
    }
    else if(action==3)
    {
        mos->m_f^=1; //旋转
        std::swap(mos->m_drain,mos->m_source);//由于cost函数的单调目前这玩意好像没有什么实质性作用啊啊(#｀-_ゝ-)
        layout(this_net);
        j=get_cost_0(this_net);
    }
    differ_j_i=j-i;
    if(differ_j_i<=0)
        return 1;
    return exp((differ_j_i));  //差别越小接受率越高 differ_j_i不为1是都是负数 越接近0返回的值越接近1也越容易被接受 eff_T是因为温度越小越难接受差解
}                                    

void placement::swap_mos(net* this_net){
    int method=rand()%3;
    //交换
    //0表示交换pmos，1表示交换nmos,2表示都换
    if(method==0)
    {
        int random1=rand()%this_net->num_pmos;
        int random2=rand()%this_net->num_pmos;


        std::swap(this_net->pmos_loc[random1],this_net->pmos_loc[random2]);
    }
    else if(method==1)
    {
        int random1=rand()%this_net->num_nmos;
        int random2=rand()%this_net->num_nmos;


        std::swap(this_net->nmos_loc[random1],this_net->nmos_loc[random2]);
    }
    else if(method==2)
    {
        if(this_net->num_nmos>=this_net->num_pmos)
        {
            int random1=rand()%this_net->num_pmos;
            int random2=rand()%this_net->num_pmos;

            std::swap(this_net->pmos_loc[random1],this_net->pmos_loc[random2]);
            std::swap(this_net->nmos_loc[random1],this_net->nmos_loc[random2]);
        }
        else{
            int random1=rand()%this_net->num_nmos;
            int random2=rand()%this_net->num_nmos;

            std::swap(this_net->pmos_loc[random1],this_net->pmos_loc[random2]);
            std::swap(this_net->nmos_loc[random1],this_net->nmos_loc[random2]);

        }
    }
}

//产生随机解
void placement::GenerateRandomSolutions(net* this_net)
{

        std::random_device rd;
        std::mt19937 rng(rd());
        for(int i=0;i<this_net->num_pmos;i++)
        {
                this_net->pmos_loc[i]=i;
        }
        std::shuffle(this_net->pmos_loc.begin(), this_net->pmos_loc.end(),rng);

        for(int i=0;i<this_net->num_nmos;i++)
        {
            this_net->nmos_loc[i]=i;
        }
        std::shuffle(this_net->nmos_loc.begin(), this_net->nmos_loc.end(),rng);

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
    std::vector<int>& pmos_loc=this_net->pmos_loc;
    std::vector<int>& nmos_loc=this_net->nmos_loc;
    
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
        std::cout<<"a="<<a<<"  "<<network[a]->name<<std::endl;



        GenerateRandomSolutions(network[a]);
        layout(network[a]);
        for(int i : network[a]->pmos_loc){
            std::cout<<i<<" ";
        }
        std::cout<<"\n";
        for(int i: network[a]->nmos_loc){
            std::cout<<i<<" ";
        }
        std::cout<<"\n";
        std::cout<<get_cost_0(network[a])<<std::endl;


        SA(network[a]);
        for(int i : network[a]->pmos_loc){
            std::cout<<i<<" ";
        }
        std::cout<<"\n";
        for(int i: network[a]->nmos_loc){
            std::cout<<i<<" ";
        }
        std::cout<<"\n";
        std::cout<<get_cost_0(network[a])<<std::endl;
        std::cout<<"end"<<std::endl;


    }
}
void placement::reverse_mos(net* this_net){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> random_noms(0,this_net->num_nmos-1);
    std::uniform_int_distribution<int> random_pmos(0,this_net->num_pmos-1);
    std::uniform_int_distribution<int> methon(0,1);
    int random_num1=random_noms(gen);
    int random_num2=random_pmos(gen);
    if(methon(gen)==0)
    {
        this_net->nmos[random_num1]->m_f^=1;
        std::swap(this_net->nmos[random_num1]->m_drain,this_net->nmos[random_num1]->m_source);
    }
    else
    {
        this_net->pmos[random_num2]->m_f^=1;
        std::swap(this_net->pmos[random_num2]->m_drain,this_net->pmos[random_num2]->m_source);
    }

}

double placement::action(double max_T,double &T_descent_rate,double &T,net* this_net)//返回一个新的下降率 在温度高的时候要尽可能小 得到一个优秀解的时候要尽可能的大
{
    std::default_random_engine e;//给随机数
    std::uniform_real_distribution<double> double_u(0,1); // 左闭右闭区间
    std::uniform_int_distribution<int> int_u(0,3);//1是移动 2是交换 3是反转  0是不动
    e.seed(time(0));
    double temp=get_cost_0(this_net);
    double eff_T = T/max_T; //反应退火的进程 温度越低越小
    int action_int;
    double accept_rate;

    for(auto& nmos:this_net->nmos)
    {


        net* temp_net=new net(*this_net);
        action_int=int_u(e);
        accept_rate=get_cost_1(action_int,this_net,nmos);//进行随机解 并获得局部更改后的代价参数 返回接受率 如果比原来更好就大于1
        if(accept_rate<1&&action_int)
        {

                *this_net=*temp_net;
                layout(this_net);

        }
        delete temp_net;
    }
    for(auto& pmos:this_net->pmos)//   pmos同理
    {
        net* temp_net=new net(*this_net);
        action_int=int_u(e);
        accept_rate=get_cost_1(action_int,this_net,pmos);
        if(accept_rate<1)
        {

                *this_net=*temp_net;
                layout(this_net);

        }
        delete temp_net;
    }


    return  T_descent_rate*(exp((get_cost_0(this_net)-temp)/temp)); //根据全局的好坏来调整下降率 cost0怎么归一

}


void placement::SA(net *this_net) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    std::uniform_int_distribution<int> int_u(0,1);//0是交换，1是反转
    int count=0;
    double T_max=std::max(this_net->num_nmos,this_net->num_pmos)*30;
    double T=T_max;
    double T_descent_rate=0.99;
    double T_min=0.002;
    int iteration=5;
    net* new_net=new net(*this_net);
    while (T>T_min)
    {
        for(int i=0;i<=iteration;i++)
        {
            count++;
            if(int_u(gen)==0)
            {
                *new_net=*this_net;
                swap_mos(new_net);
                layout(new_net);
                layout(this_net);
                int current_cost=get_cost_0(this_net);
                int new_cost=get_cost_0(new_net);
                if (new_cost < current_cost || dis(gen) < exp((current_cost - new_cost) / T)) {
                    *this_net = *new_net;
                    layout(this_net);
                }
            }
            else
            {
                *new_net=*this_net;
                reverse_mos(new_net);
                layout(new_net);
                layout(this_net);
                int current_cost=get_cost_0(this_net);
                int new_cost=get_cost_0(new_net);
                if (new_cost < current_cost || dis(gen) < exp((current_cost - new_cost) / T)) {
                    *this_net = *new_net;
                    layout(this_net);
                }
            }
        }
        T*=T_descent_rate;
    }
    delete new_net;
    std::cout<<"itertion="<<count<<std::endl;
}


//void placement::run_SA(double &T_descent_rate,double &T,net* this_net)
//{
//    std::cout<<"run_into_run_SA"<<std::endl;
//    double max_T = T*10;// 定义一个最大温度
//    //std::cout<<T/max_T<<" "<<std::endl;
//    int count_in=1;
//    int count_out=1;
//    int i = 0;
//    while(T>0.001)
//    {
//        i=0;
//        double differ_T=0;
//        while(i<50)
//        {
//            count_in++;
//            //std::cout<<T<<" ";
//            action(max_T,T_descent_rate,T,this_net);
//            differ_T=T*(1-T_descent_rate);//温度下降量
//            //std::cout<<T*(1-T_descent_rate)<<" "<<std::endl;
//            i++;
//        }
//        T-=differ_T;
//
//    }
//    std::cout<<count_in<<std::endl;
//
//
//};



