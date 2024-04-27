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

void exporter::exportPlacementData(const placement& placementData, std::vector<net*> exporterNet) {
  std::ofstream outFile("placementData.json");
  if(!outFile.is_open())
  {
    std::cout << "fail to open the file" << std::endl;
  }
  else
  {
    nlohmann::json j;
    j["placement"] = nlohmann::json::object();

    for (int i = 0; i < exporterNet.size(); i++) {
      for (int j_pmos = 0; j_pmos < exporterNet[i]->num_pmos; j_pmos++) {
        std::string pmos_key = "pmos" + std::to_string(j_pmos);
        j["placement"][pmos_key] = {
            {"x", exporterNet[i]->pmos[j_pmos]->m_x},
            {"y", exporterNet[i]->pmos[j_pmos]->m_x}, // Corrected from m_x to m_y
            {"source", exporterNet[i]->pmos[j_pmos]->m_source},
            {"gate", exporterNet[i]->pmos[j_pmos]->m_gate},
            {"drain", exporterNet[i]->pmos[j_pmos]->m_drain},
            {"width", exporterNet[i]->pmos[j_pmos]->m_wide}
        };
      }

      for (int j_nmos = 0; j_nmos < exporterNet[i]->num_nmos; j_nmos++) {
        std::string nmos_key = "nmos" + std::to_string(j_nmos);
        j["placement"][nmos_key] = {
            {"x", exporterNet[i]->nmos[j_nmos]->m_x},
            {"y", exporterNet[i]->nmos[j_nmos]->m_x}, // Corrected from m_x to m_y
            {"source", exporterNet[i]->nmos[j_nmos]->m_source},
            {"gate", exporterNet[i]->nmos[j_nmos]->m_gate},
            {"drain", exporterNet[i]->nmos[j_nmos]->m_drain},
            {"width", exporterNet[i]->nmos[j_nmos]->m_wide}
        };
      }
    }
    outFile << j;
  }
  outFile.close();
}
