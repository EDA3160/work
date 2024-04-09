#ifndef PROJECT_PLACEMENT_PLACEMENT_H_
#define PROJECT_PLACEMENT_PLACEMENT_H_

#include "database.h"
#include <string>
#include <vector>


class placement
        {
public:

            void slover();





private:
        std::vector<net*> network;
        double T_min;
        double T;
        double cool_rate;
        int cost;
        int bset_cost;
        std::vector<int> pmos_loc;
        std::vector<int> nmos_loc;
        std::vector<int> best_pmos_loc;
        std::vector<int> best_nmos_loc;
        void GenerateRandomSolutions();
        int get_cost(net* anet);
        void layout(net* anet );
        void init_SA();
        void swap_mos();
        void run_SA();

        };

#endif // PROJECT_PLACEMENT_PLACEMENT_H_
