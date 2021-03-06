//
// Created by Phili on 15/10/2020.
//

#include "PDA2CFG.h"

std::shared_ptr<CFG> PDA2CFG(PDA& pda) {
   // I wanted to use a smart pointer , but it doesnt work with private constrctors
   PDA_CFG* pda_cfg = new PDA_CFG(pda);
   auto temp = pda_cfg->cfg;
   delete pda_cfg;
   return temp;
}

std::shared_ptr<CFG> PDA2CFG(std::ifstream &stream) {
   PDA pda(stream);
   return PDA2CFG(pda);
}

std::vector<std::string> PDA_CFG::calc_betweens(std::vector<std::string> stack, std::vector<std::string> &betweens, PDA &pda) {
   std::vector<std::string> temp;
   if (stack[0] == "e" || stack[0].empty()) {
      return std::vector<std::string>({""});
   }
   if ( stack.size() <= 1) {
      return betweens;
   }
   for ( auto i : betweens) {
      for ( auto j : pda.states) {
         temp.emplace_back(i + stack[0] + j->name + "][" + j->name);
      }
   }
   betweens = temp;
   stack.erase(stack.begin());
   if (!stack.empty()) {
      return calc_betweens(stack, betweens, pda);
   }
   return temp;
}


void PDA_CFG::rip(PDA::State::Transition &tr) {

}


PDA_CFG::PDA_CFG(PDA &pda){

   std::vector<std::string> state_names;
   for ( auto n : pda.states ) {
      state_names.emplace_back(n->name);
   }

   std::vector<std::string> between;
   for (auto s : pda.states) {
      between.emplace_back( s->name + "][" + s->name);
   }
   this->cfg->prodctions["S"] = {};

   for ( auto i : pda.states) {
      for (auto j : i->transitions) {
         /// maak cfg representatie van volgende Transition
         for ( auto l : state_names ) {
            std::string from = "[" + i->name + j.top + l + "]";
            if (j.top == pda.start_sym) {this->cfg->prodctions["S"].push_back(from);}
            std::vector<std::string> temp = {j.input + "[" + j.point->name};
            if (j.input == "e" || j.input.empty()) {
               //if (j.push.empty() || j.push[0] == "e" || j.push[0].empty()){continue;} //todo
               if (l == j.point->name) {
                  this->cfg->prodctions[from].push_back("e");
               }
               continue;
            }
            if (j.push.empty() || j.push[0] == "e" || j.push[0].empty()) {
               if (l == j.point->name) {
                  this->cfg->prodctions[from].push_back(j.input);
               }
               continue;
            }
            for (auto b : calc_betweens(j.push, temp, pda )) {
               if (b.empty()) {
                  this->cfg->prodctions[from].push_back(j.input);
               }
               else {
                  this->cfg->prodctions[from].push_back(  b + j.push[j.push.size()-1] + l + ']');
               }
            }
         }

      }
   }
   std::cout << "idk";
}

std::shared_ptr<CFG> PDA_CFG::generate() {

   return std::shared_ptr<CFG>();
}