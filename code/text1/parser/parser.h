
#ifndef TEXT1_PARSER_H
#define TEXT1_PARSER_H

#endif //TEXT1_PARSER_H
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "database.h"

void parseDie(std::ifstream& ifs, DieSize& die);
void parseInstances(std::ifstream& ifs, NumInstances& instance);
void parseNumNets(std::ifstream& ifs, NumNets& numnets);
void parseNets(std::ifstream& ifs, Net& net);
void parseNumNet(Net* net1, Net* net2, Net* net3, NumNets& numnets);
