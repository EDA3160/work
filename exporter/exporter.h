//
// Created by Defender on 2024/4/22.
//

#ifndef PROJECT_EXPORTER_EXPORTER_H_
#define PROJECT_EXPORTER_EXPORTER_H_

#include "../database/database.h"
#include "../placement/placement.h"
#include "../parser/parser.h"
#include<ostream>
#include<sstream>
#include<string>
#include<vector>
class exporter
{
public:
  exporter(std::vector<net*> network);
  void exportPlacementData(const placement& placementData,std::vector<net*> exporterNet);

private:
  std::vector<net*> exportNet;

};


#endif // PROJECT_EXPORTER_EXPORTER_H_
