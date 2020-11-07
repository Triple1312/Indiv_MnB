//
// Created by Phili on 02/10/2020.
//

#include "CFG.h"

CFG::CFG(std::ifstream &file) {
  nlohmann::json j;
  file >> j;

  this->start = j.at("Start");

  for ( auto i : j.at("Terminals") ) {
    terminals.push_back(i);
  }

  for ( auto j : j.at("Variables") ) {
    vars.push_back(j);
  }

  for ( auto k : j.at("Productions") ) {
    std::string head = k.at("head");
    std::string body;
    if ( k.at("body").empty() ) {
      body += "e";
    }
    for ( auto l : k.at("body") ) {
      body += l; body += " ";
    }
    prodctions[head].push_back(body);
  }

}

void CFG::print() {
  std::stringstream start;
  std::stringstream next;
  for (auto i : prodctions) {
    std::stringstream os;
    os << i.first << " -> ";
    std::copy(i.second.begin(), i.second.end()-1, std::ostream_iterator<std::string>(os, " | "));

    if (i.second.size() > 1) {   // or (!v.empty())
      os << *(i.second.end() - 1);
    }
    if ( i.first == this->start ) {
      start << os.str();
    }else {
      next << os.str() << std::endl;
    }
  }
  std::cout << start.str() << std::endl;
  std::cout << next.str() << std::endl;
}

void CFG::print(std::string file_name) {
   std::ofstream file(file_name);
   //file.open(file_name, std::ios::trunc);
   for (auto b : this->prodctions["S"]) {
      file << "S" << " -> " << b << std::endl;
   }

   for ( auto i : this->prodctions) {
      if (i.first == "S" ){continue;}
      for (auto j : i.second) {
         file << i.first << " -> " << j << std::endl;
      }
   }
   file.close();
}