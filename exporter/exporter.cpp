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
#include <string>

exporter::exporter(std::vector<net*> network) :exportNet(network){};

void exporter::exportPlacementData(std::vector<net*> exporterNet) {
  std::ofstream outFile("C:/Users/Defender/Desktop/project/work/placementData.json");
  if(!outFile.is_open())
  {
    std::cout << "fail to open the file" << std::endl;
  }
  else
  {
    std::cout << " open the file successfully and successful output" << std::endl;
    nlohmann::ordered_json j; // 使用ordered_json代替json
    for (int i = 0; i < exporterNet.size(); i++) {
      j["placement"][i]["case"] = exporterNet[i]->name;
      for (int j_pmos = 0; j_pmos < exporterNet[i]->pmos.size(); j_pmos++) {
        j["placement"][i]["pmos"][j_pmos]["name"] = exporterNet[i]->pmos[j_pmos]->m_name;
        j["placement"][i]["pmos"][j_pmos]["x"] = std::to_string(exporterNet[i]->pmos[j_pmos]->m_x);
        j["placement"][i]["pmos"][j_pmos]["y"] = "1";
        j["placement"][i]["pmos"][j_pmos]["source"] = exporterNet[i]->pmos[j_pmos]->m_source;
        j["placement"][i]["pmos"][j_pmos]["gate"] = exporterNet[i]->pmos[j_pmos]->m_gate;
        j["placement"][i]["pmos"][j_pmos]["drain"] = exporterNet[i]->pmos[j_pmos]->m_drain;
        j["placement"][i]["pmos"][j_pmos]["width"] = std::to_string(exporterNet[i]->pmos[j_pmos]->m_wide);
      }
      for (int j_nmos = 0; j_nmos < exporterNet[i]->nmos.size(); j_nmos++) {
        j["placement"][i]["nmos"][j_nmos]["name"] = exporterNet[i]->nmos[j_nmos]->m_name;
        j["placement"][i]["nmos"][j_nmos]["x"] = std::to_string(exporterNet[i]->nmos[j_nmos]->m_x);
        j["placement"][i]["nmos"][j_nmos]["y"] = "0";
        j["placement"][i]["nmos"][j_nmos]["source"] = exporterNet[i]->nmos[j_nmos]->m_source;
        j["placement"][i]["nmos"][j_nmos]["gate"] = exporterNet[i]->nmos[j_nmos]->m_gate;
        j["placement"][i]["nmos"][j_nmos]["drain"] = exporterNet[i]->nmos[j_nmos]->m_drain;
        j["placement"][i]["nmos"][j_nmos]["width"] = std::to_string(exporterNet[i]->nmos[j_nmos]->m_wide);
      }
    }

    outFile << j.dump(4); // 4个缩进空格
    outFile << std::endl;
  }
  outFile.close();
}

