//
// Created by Phili on 15/10/2020.
//

#ifndef INDIV_SRC_PDA2CFG_H_
#define INDIV_SRC_PDA2CFG_H_

#include <memory>

#include "CFG.h"
#include "PDA.h"

std::shared_ptr<CFG> PDA2CFG(PDA& pda);

class PDA_CFG {

  friend class CFG;
  friend std::shared_ptr<CFG> PDA2CFG(PDA& pda);

  std::shared_ptr<CFG> cfg = std::make_shared<CFG>();

  PDA_CFG(PDA& pda);

  void rip(PDA::State::Transition &tr);

  std::shared_ptr<CFG> generate();

  std::vector<std::string> calc_betweens(std::vector<std::string> stack, std::vector<std::string> &betweens, PDA &pda);
};


//std::shared_ptr<CFG> PDA2CFG(PDA& pda);

std::shared_ptr<CFG> PDA2CFG(std::ifstream &stream);



#endif //INDIV_SRC_PDA2CFG_H_
