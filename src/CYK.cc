//
// Created by Phili on 02/10/2020.
//

#include "CYK.h"

CYK::CYK(CFG &g, std::string input) : G(g) {
  std::map<std::string, std::vector<std::string>> rip;
  this->input = input;
  for (int i = 0; i < input.size() -1; i++) {

  }

}

std::vector<std::pair<std::string, std::string>> CYK::Split(const std::string& in) {
  std::vector<std::pair<std::string, std::string>> pairs;
  if (in.size() == 1) {
    return {{in, ""}};
  }
  for (int i = 0; i < in.size()-1; i++) {
    pairs.emplace_back(in.substr(0, i+1), in.substr(i+1, in.size() ) );
  }
  return pairs;
}

std::vector<std::string> CYK::FromRule(const std::string& in) {
  std::vector<std::string> temp;
  for ( const auto& i : this->G.prodctions ) {
    for ( const auto& j : i.second ) {
      if ( in == j ) {
        temp.emplace_back( i.first );
      }
    }
  }
  return temp;
}

std::vector<std::string> CYK::Prod(const std::vector<std::string>& v1, const std::vector<std::string>& v2) {
  std::vector<std::string> temp;
  for (const auto& i : v1 ) {
    for ( const auto& j : v2 ) {
      temp.emplace_back(i+j);
    }
  }
  return temp;
}