//
// Created by Phili on 28/09/2020.
//

#include "TM.h"

TM::TM(std::ifstream &stream) {
  nlohmann::json j;
  stream >> j;


}

void TM::Tape::Left() {
  if (this->strip.size() - 1 > pointer) {
    pointer++;
  }
  else {
    std::cout << "can't move anymore left" << std::endl;
  }
}

void TM::Tape::Right() {
  if (0 < pointer) {
    pointer--;
  }
  else {
    std::cout << "can't move anymore right" << std::endl;
  }
}