//
// Created by Phili on 01/10/2020.
//

#include "PDA.h"

PDA::PDA(std::ifstream &stream) {
  nlohmann::json j;
  stream >> j;


  for (std::string i : j.at("Alphabet")) {
    this->alpha_in.emplace_back(i);
  }

  for (std::string i : j.at("StackAlphabet")) {
    this->alpha_stack.emplace_back(i);
  }

  std::vector<std::string> temp = {j.at("StartStack")};

  this->start_sym += temp[0];

  for (std::string i : j.at("States")) {
    this->states.push_back(std::make_shared<State>(i));
  }

  for (auto i : this->states) {
    if (i->name == j.at("StartState")) {
      this->start = i;
    }
    for ( auto k : j.at("FinalStates")) {
      if (k == i->name ) {
        i->end_state = true;
      }
    }
    for (auto l : j.at("Transitions")) {
      if (i->name == l.at("from")) {
        for (auto x : this->states) {
            if (x->name == l.at("to")) {
              if (l.at("replacement").empty()) {
                 //std::vector<std::string> tok =
                auto temp = std::make_shared<State::Transition>(l.at("input"), l.at("stacktop"), l.at("replacement"), x);
                i->transitions.emplace_back(l.at("input"), l.at("stacktop"), l.at("replacement"), x);
              }
              else {
                 std::string t;
                for (auto m : l.at("replacement")) {
                  t += m;
                } //f
                i->transitions.emplace_back(State::Transition(l.at("input"), l.at("stacktop"), l.at("replacement"), x));
              }
            }

        }//f
      }

    }//f
  }

}

bool PDA::Accept(std::string input, std::vector<std::string> stack, std::shared_ptr<State> curr) {
  bool accept = false;

  if (input.empty() && curr->end_state) {return true;}

  //input.erase(input.begin());
  for (const auto& i : curr->transitions) {
    if (stack[stack.size()-1] == i.top) {
      if (i.input == std::to_string(input[0])) {
        std::string temp_str = input.erase(0);
        std::vector<std::string> temp_stack = stack;
        if (i.push[0] == "") {
          temp_stack.erase(temp_stack.end());
        }
        else {
          for (auto j = i.push.size()-1; j >= 0; j-- ) {
            temp_stack.erase(temp_stack.end());
            temp_stack.push_back(i.push[j]);
          }
        }
        accept = Accept(temp_str, temp_stack, i.point);
        if (accept) {
          return true;
        }
      }
    }
  }
  return accept;
}

void PDA::PrintPDA() {
      std::fstream out;   out.open("graph.dot", std::ios::out | std::ios::trunc);
      out << "Digraph {" << std::endl <<"rankdir = LR;"<< std::endl;
      for (int x = 0; x < this->states.size(); x++){
         if (this->states[x]->end_state){
            out << this->states[x]->name << "[shape=\"doublecircle\"]"<< std::endl;
         }


         for (auto i : states[x]->transitions){
            out << this->states[x]->name << " -> " << i.point->name
                << " [label=\"" << i.input << "," << i.top << "/" << i.push[0] << "\"]" << std::endl; // todo werkt niet
         }
      }
      out << "\"\" -> " << this->start->name << std::endl << "\"\" [shape = \"plaintext\"]"<< std::endl;
      out << "}";
      out.close();
      system("dot -Tpng graph.dot -o graph.png");


}

void PDA::State::AddTrans(std::string input, std::string stack, std::vector<std::string> push, std::shared_ptr<State> to) {
 auto temp = std::make_shared<State::Transition>(input, stack, push, to);
}