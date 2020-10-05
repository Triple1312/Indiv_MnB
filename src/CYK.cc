//
// Created by Phili
//

#include "CYK.h"

CYK::CYK(CFG &g, std::string input) : G(g) {
  std::map<std::string, std::vector<std::string>> rip;

  /// dit blokje berekent de Rules voor de basis chars ///
  std::vector<std::string> temp; // input char
  MakeProductions();
  SplitToCount(input, temp, 1);
  //this->table[0] = temp;
  for (auto l = 0; l < temp.size()-1; l++) {
     this->table[0][l].push_back(temp[l]);
    rip[temp[l]] = FromRule(temp[l]);
    auto hi = rip[temp[l]];
    this->table[1][l]= hi;
  }

  this->input = input;
  for (int i = 2; i <= input.size(); i++) {
    temp.clear();
    SplitToCount(input, temp, i);
    for ( auto j = 0; j < temp.size(); j++) {
      for ( auto k : Split(temp[j]) ) {
        rip[temp[j]] = Prod(rip[k.first], rip[k.second]);
        this->table[i][j] = rip[temp[j]];
      }
    }
  }
  std::cout << "niet gecrasht" << std::endl;
}

/// Function that splits strings into strings with length count
/// \param and input string that needs to be split , every cycle of the function I remove the first char
/// \param the vector of strings where I add all the possible spit strings with length count
/// \param the length of the split strings
void CYK::SplitToCount(std::string input, std::vector<std::string>& add, int count) {
  std::string str;
  for (int i = 0; i < count; i++) {
    str += input[i];
  }
  add.push_back(str);
  if (str[str.size()-1] == input[input.size()-1] ){
    return;
  }
  else {
    input.erase(0, 1);
    SplitToCount(input, add, count);
    return;
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
  if (in.empty()) {return temp;}
  for ( const auto& i : this->productions ) {
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

inline std::string RemSpaces(std::string &in) {
   std::string ret;
   for ( auto c : in ) {
      if (c != ' ') {
         ret.push_back(c);
      }
   }
   return ret;
}

void CYK::MakeProductions() {
   for ( auto i : this->G.prodctions) {
      for ( auto j : i.second) {
         this->productions[i.first].push_back(RemSpaces(j));
      }
   }
}
