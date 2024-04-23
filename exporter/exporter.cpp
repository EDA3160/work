//
// Created by Defender on 2024/4/22.
//
#include "exporter.h"
#include "../placement/placement.h"
#include "../parser/parser.h"
#include "../database/database.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

exporter::exporter(std::vector<net*> network) :exportNet(network){};

void exporter::exportPlacementData(const placement& placementData, std::vector<net*> exporterNet) {
  std::ofstream outFile("placementData.json");
  if(!outFile.is_open())
  {
    std::cout << "fail to open the file" << std::endl;
  }
  else
  {
    while(1){
        outFile << "最佳布局: " << std::endl;
        for (int i = 0; i < exporterNet.size(); i++) {
          outFile << "net" << i << ": ";
          for (int j = 0; j < exporterNet[i]->num_pmos; j++) {
            outFile << "pmos" << j << "位置: " << exporterNet[i]->pmos[j]->m_x
                    << " ";
          }
          for (int j = 0; j < exporterNet[i]->num_nmos; j++) {
            outFile << "nmos" << j << "位置: " << exporterNet[i]->nmos[j]->m_x
                    << " ";
          }
          outFile << std::endl;
        }

        outFile << "最佳pmos位置: ";
        for (int loc : placementData.getBestPmosLoc()) {
          outFile << loc << " ";
        }
        outFile << std::endl;

        outFile << "最佳nmos位置: ";
        for (int loc : placementData.getBestNmosLoc()) {
          outFile << loc << " ";
        }
        outFile << std::endl;
    }
  }
  outFile.close();
}