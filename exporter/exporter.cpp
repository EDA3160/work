//
// Created by Defender on 2024/4/22.
//
#include "exporter.h"
#include "../placement/placement.h"
#include "../parser/parser.h"
#include "../database/database.h"
#include <iostream>
#include <fstream>

void exporter::exportPlacementData(const placement& placementData) {
  std::ofstream outFile("placementData.spi");


  outFile << "下降率: " << placementData.getTDescentRate() << std::endl;
  outFile << "温度: " << placementData.getT() << std::endl;
  outFile << "冷却率: " << placementData.getCoolRate() << std::endl;
  outFile << "成本: " << placementData.getCost() << std::endl;
  outFile << "最佳成本: " << placementData.getBestCost() << std::endl;
  outFile << "pmos位置: ";

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


  outFile.close();
}