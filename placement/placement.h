#ifndef PROJECT_PLACEMENT_PLACEMENT_H_
#define PROJECT_PLACEMENT_PLACEMENT_H_

#include "../database/database.h"
#include <string>
#include <vector>
#define T_lambda 100  //初始化温度参数
#define T_descent_lambda 0.9  //初始化下降温度参数  //这两个参数只在初始化时候出现过，没什么深意
#define T_min 0
class placement
        {
public:
        placement(std::vector<net*> m_network);
        void Slover();    //主函数(!!!)


        //得到私有数据
        double getTDescentRate() const { return T_descent_rate; }
        double getT() const { return T; }
        double getCoolRate() const { return cool_rate; }
        int getCost() const { return cost; }
        int getBestCost() const { return bset_cost; }
        std::vector<int> getPmosLoc() const { return pmos_loc; }
        std::vector<int> getNmosLoc() const { return nmos_loc; }
        //有用数据
        std::vector<int> getBestPmosLoc() const { return best_pmos_loc; }
        std::vector<int> getBestNmosLoc() const { return best_nmos_loc; }



private:
        std::vector<net*> network;
        double T_descent_rate;
        double T;
        double cool_rate;
        int cost;
        int bset_cost;
        std::vector<int> pmos_loc;
        std::vector<int> nmos_loc;
        std::vector<int> best_pmos_loc;
        std::vector<int> best_nmos_loc;
        void GenerateRandomSolutions();
        double get_cost_0(net* anet);//全局代价  
        double get_cost_1(int action,net* this_net,mos* mos);//局域某个mos管操作后的以及其周围影响的mos的代价 返回通过率 action_int决定执行什么操作 0是不进行操作 1是往能减少的方向移动（带上和自己在一块的）2是换位 3是旋转
        void layout(net* this_net );
        void init_SA(double &T_descent_rate,double &T,net* this_net);
        void swap_mos();
        double action(double max_T, double &T_descent_rate,double &T,net* this_net);
        void run_SA(double &T_descent_rate,double &T,net* this_net);

        };

#endif // PROJECT_PLACEMENT_PLACEMENT_H_
