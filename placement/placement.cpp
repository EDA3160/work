//
// Created by Defender on 2024/3/31.
//
#include "placement.h"
#include "database.h"
#include <unordered_map>

Placement::Placement(const std::string& m_gate, const std::vector<mos*>& pmos, const std::vector<mos*>& nmos,
          const std::vector<std::unordered_map<std::string, std::vector<mos*>>> placement_x, const std::vector<std::unordered_map<std::string, std::vector<mos*>>> placement_y) {
  int index = 0;
  if (pmos[0]->m_gate == nmos[0]->m_gate) {
    std::unordered_map<std::string, std::vector<mos*>> same_gate_mos;
    for (auto pm : pmos) {
      same_gate_mos[pm->m_gate].push_back(pm);
    }
    for (auto nm : nmos) {
      same_gate_mos[nm->m_gate].push_back(nm);
    }
  } else {
    std::unordered_map<std::string, std::vector<mos*>> different_gate_mos;
    for (auto pm : pmos) {
      different_gate_mos[pm->m_gate].push_back(pm);
    }
    for (auto nm : nmos) {
      different_gate_mos[nm->m_gate].push_back(nm);
    }
  }
}