//
// Created by Phili on 02/10/2020.
//

#ifndef INDIV_SRC_CFG_H_
#define INDIV_SRC_CFG_H_

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "../libs/json.hpp"

class CFG {

  friend class CYK;
  friend class PDA_CFG;

  // als we ervan uitgaan dat een var meerdere chars kunnen zijn //
  std::vector<std::string> vars;

  std::vector<std::string> terminals;

  std::string start;

  std::unordered_map<std::string, std::vector<std::string>> prodctions;

 public:
  explicit CFG(std::ifstream &file);

  void print();

  void print(std::string file_name);

  CFG() = default;
};

#endif  //INDIV_SRC_CFG_H_
