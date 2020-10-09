//
// Created by Phili
//

#ifndef INDIV_SRC_CYK_H_
#define INDIV_SRC_CYK_H_

#include <map>
#include <string>
#include <vector>
#include <algorithm>

#include "CFG.h"

class CYK {

  const CFG &G;

  std::vector<std::vector<std::vector<std::string>>> table {{{}}};

  std::string input;

  std::map<std::string, std::vector<std::string>> productions;


  //static std::map<std::string, std::vector<std::string>> Split2String(std::string &in);
  void MakeProductions();

 public:

  CYK(CFG &g, std::string);

  std::vector<std::string> FromRule(const std::string& in);

  static std::vector<std::pair<std::string, std::string>> Split(const std::string& in);

  std::vector<std::string> Prod(const std::vector<std::string> &v1, const std::vector<std::string> &v2);

  void SplitToCount(std::string input, std::vector<std::string> &add, int count);

  bool CheckIfValue(std::string value);
};

#endif //INDIV_SRC_CYK_H_
