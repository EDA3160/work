#ifndef TEXT1_DATABASE_H
#define TEXT1_DATABASE_H

#include <vector>
#include <iostream>
#include <string>

struct DieSize
{
    int width;
    int heigth;
};

struct NumInstances
{
    int size;
    std::vector<std::string> instances;
};

struct Net
{
    int size;
    int pins[10];
};

struct NumNets
{
    int size;
    Net* nets[3];
};
#endif //TEXT1_HHH_H