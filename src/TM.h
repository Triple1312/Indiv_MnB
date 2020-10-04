//
// Created by Phili on 28/09/2020.
//

#ifndef INDIV_SRC_TM_H_
#define INDIV_SRC_TM_H_

#include <fstream>
#include <vector>
#include <memory>

#include <json.hpp>

#include "State.h"


class TM {

  std::shared_ptr<State> Start;

  std::vector<std::string> input_alpha;

  std::vector<std::string> tape_alpha;

  std::vector<std::shared_ptr<State>> states;

  class Tape {
    unsigned int pointer;
    std::vector<std::string> strip;

    void Left();

    void Right();
  };


 public:
  explicit TM(std::ifstream &stream);
};

#endif //INDIV_SRC_TM_H_
