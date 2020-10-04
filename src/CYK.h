//
// Created by Phili on 02/10/2020.
//

#ifndef INDIV_SRC_CYK_H_
#define INDIV_SRC_CYK_H_

#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include "CFG.h"

typedef std::vector<std::vector<std::string>> table_str;

class CYK {

  const CFG &G;

  table_str table;

  std::string input;

  std::map<std::string, std::vector<std::string>> cont;

  //static std::map<std::string, std::vector<std::string>> Split2String(std::string &in);

 public:

  CYK(CFG &g, std::string);

  std::vector<std::string> FromRule(const std::string& in);

  static std::vector<std::pair<std::string, std::string>> Split(const std::string& in);

  std::vector<std::string> Prod(const std::vector<std::string> &v1, const std::vector<std::string> &v2);
};

#endif //INDIV_SRC_CYK_H_
