#ifndef PROJECT_PLACEMENT_PLACEMENT_H_
#define PROJECT_PLACEMENT_PLACEMENT_H_

#include "database.h"
#include <string>
#include <vector>
#include <unordered_map>

class Placement {
public:
  Placement(const std::string& m_gate, const std::vector<mos*>& pmos, const std::vector<mos*>& nmos,
            const std::vector<std::unordered_map<std::string, std::vector<mos*>>> placement_x, const std::vector<std::unordered_map<std::string, std::vector<mos*>>> placement_y);

private:
  std::string m_gate;
  std::vector<mos*> pmos;
  std::vector<mos*> nmos;

  static std::vector<std::unordered_map<std::string, std::vector<mos*>>> placement_x;
  static std::vector<std::unordered_map<std::string, std::vector<mos*>>> placement_y;




};

#endif // PROJECT_PLACEMENT_PLACEMENT_H_
