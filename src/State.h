//
// Created by Phili on 28/09/2020.
//

#ifndef INDIV_SRC_STATE_H_
#define INDIV_SRC_STATE_H_

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class State {
  friend class TM;

  class Transition {


  };

  std::string name;

  bool final;

  std::vector<std::unique_ptr<Transition>> trans;

};

#endif //INDIV_SRC_STATE_H_
