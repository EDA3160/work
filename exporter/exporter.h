//
// Created by Defender on 2024/4/22.
//

#ifndef PROJECT_EXPORTER_EXPORTER_H_
#define PROJECT_EXPORTER_EXPORTER_H_

#include "../database/database.h"
#include "../placement/placement.h"
#include "../parser/parser.h"
#include<ostream>
#include<string>
#include<sstream>
class exporter
{
public:
  void exportPlacementData(const placement& placementData);


};


#endif // PROJECT_EXPORTER_EXPORTER_H_
