#include "database.h"
#include "placement.h"
#include "parser.h"
#include "exporter.h"

int main()
{
    std::ifstream file("/home/spiderman/桌面/nihoz/test.txt");
    if (!file.is_open())
        return -1;
    DieSize die;
    die.width = 0;
    die.heigth = 0;
    parseDie(file, die);
    NumInstances instances;
    parseInstances(file, instances);
    Net N1, N2, N3;
    NumNets numnets;
    parseNumNets(file, numnets);
    parseNets(file, N1);
    parseNets(file, N2);
    parseNets(file, N3);
    parseNumNet(&N1, &N2, &N3, numnets);
    int grathic[3][3] = { 0 };
    int minsum = 1000;
    int bestgrathic[3][3] = { 0 };
    Calculate(bestgrathic, grathic, die, 1, numnets, minsum);
    return 0;
}
