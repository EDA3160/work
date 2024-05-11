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
            for (int j_pmos = 0; j_pmos < exporterNet[i]->num_pmos; j_pmos++) {
                j["placement"][exporterNet[i]->pmos[j_pmos]->m_name]["x"] = std::to_string(exporterNet[i]->pmos[j_pmos]->m_x);
                j["placement"][exporterNet[i]->pmos[j_pmos]->m_name]["y"] = "1";
                j["placement"][exporterNet[i]->pmos[j_pmos]->m_name]["source"] = exporterNet[i]->pmos[j_pmos]->m_source;
                j["placement"][exporterNet[i]->pmos[j_pmos]->m_name]["gate"] = exporterNet[i]->pmos[j_pmos]->m_gate;
                j["placement"][exporterNet[i]->pmos[j_pmos]->m_name]["drain"] = exporterNet[i]->pmos[j_pmos]->m_drain;
                j["placement"][exporterNet[i]->pmos[j_pmos]->m_name]["width"] = std::to_string(exporterNet[i]->pmos[j_pmos]->m_wide);
            }
            for (int j_nmos = 0; j_nmos < exporterNet[i]->num_nmos; j_nmos++) {
                j["placement"][exporterNet[i]->nmos[j_nmos]->m_name]["x"] = std::to_string(exporterNet[i]->nmos[j_nmos]->m_x);
                j["placement"][exporterNet[i]->nmos[j_nmos]->m_name]["y"] = "0";
                j["placement"][exporterNet[i]->nmos[j_nmos]->m_name]["source"] = exporterNet[i]->nmos[j_nmos]->m_source;
                j["placement"][exporterNet[i]->nmos[j_nmos]->m_name]["gate"] = exporterNet[i]->nmos[j_nmos]->m_gate;
                j["placement"][exporterNet[i]->nmos[j_nmos]->m_name]["drain"] = exporterNet[i]->nmos[j_nmos]->m_drain;
                j["placement"][exporterNet[i]->nmos[j_nmos]->m_name]["width"] = std::to_string(exporterNet[i]->nmos[j_nmos]->m_wide);
            }
        }

        outFile << j.dump(4); // 4个缩进空格
        outFile << std::endl;
    }
    outFile.close();
}

