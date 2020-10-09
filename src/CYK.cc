//
// Created by Phili
//

#include "CYK.h"

CYK::CYK(CFG &g, std::string input) : G(g) {
  std::map<std::string, std::vector<std::string>> rip;
  //this->input = input;

  /// dit blokje berekent de Rules voor de basis chars ///
  std::vector<std::string> temp; // input char
  MakeProductions();
  SplitToCount(input, temp, 1);

  /// preallocation so I can input in subvectors without pushing a vector ///
  this->table.resize(input.size() +1 );
  for (int i = 0; i < input.size()+1; i++) {
     table[i].resize(input.size());
  }
  //this->table[0] = temp;
  for (auto l = 0; l < temp.size(); l++) {
     //table[1][l] = {};
     this->table[0][l].push_back(temp[l]);
    rip[temp[l]] = FromRule(temp[l]);
    auto hi = rip[temp[l]];
     //this->table[1][l];
    this->table[1][l] = hi;
    std::cout << "idk";
  }

  this->input = input;
  for (int i = 2; i <= input.size(); i++) {
    temp.clear();
    SplitToCount(input, temp, i);
    for ( auto j = 0; j < temp.size(); j++) {
      for ( auto k : Split(temp[j]) ) {
         for (auto m : Prod(rip[k.first], rip[k.second])) {
            rip[temp[j]].emplace_back(m);
         }
         //https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
         sort( rip[temp[j]].begin(), rip[temp[j]].end() );
         rip[temp[j]].erase( unique( rip[temp[j]].begin(), rip[temp[j]].end() ), rip[temp[j]].end() );
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
  if (str.size()-1 == input.size()-1 ){
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
  std::vector<std::string> vec;
  for (const auto& i : v1 ) {
    for ( const auto& j : v2 ) {
       for ( auto k : this->productions) {
          for (auto l : k.second) {
             if (l == i+j) {
                vec.emplace_back(k.first);
             }
          }
       }
    }
  }
  return vec;
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

void CYK::ToHTML() {
   std::ofstream out_file;
   out_file.open("CYK.html");
   out_file.clear();
   out_file << "<!DOCTYPE html>\n"
               "<html>\n"
               "<head>\n"
               "    <style>\n"
               "        table, td{\n"
               "            border: 1px solid black;\n"
               "            border-collapse: collapse;\n"
               "            text-align: center;\n"
               "        }\n"
               "        td {\n"
               "            padding: 20px;\n"
               "        }\n"
               "    </style>\n"
               "</head>\n"
               "<body> \n"
               "\n"
               "<table>\n";
   for (int i = 0; i < table.size()-1  ; i++) {
      out_file << "<tr>\n";
      for (int j = 0; j <= i ; j++) {

         std::string temp_str;
         for (auto m : table[table.size() -1 -i][j]) {
            temp_str += m += ",";
         }
         //temp_str.erase(temp_str.end());

         out_file << "<td>" << temp_str << "</td>\n";
      }
      out_file << "</tr\n>";
   }

   out_file << "<tr>\n";
   for (auto i : table[0]) {
     out_file << "<th>" << i[0] << "</th>\n";
   }
   out_file << "</tr>\n";


   out_file << "</table>\n"
               "</body>\n"
               "</html>";
   out_file << std::flush;
   out_file.close();
}
