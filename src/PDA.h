//
// Created by Phili on 01/10/2020.
//

#ifndef PROGRAMEEROPDRACHT2__PDA_H_
#define PROGRAMEEROPDRACHT2__PDA_H_

#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <fstream>

#include "json.hpp"

class PDA {
  friend class PDA_CFG;

  struct State {

    struct Transition {

     std::string input;

      const std::string top;

      const std::vector<std::string> push;

      std::shared_ptr<State> point;

      Transition(std::string in, std::string top, std::vector<std::string> push, std::shared_ptr<State> state)
                : input(std::move(in)), top(std::move(top)), push(std::move(push)), point(std::move(state)){};

    }; //PDA::State::Transition


    const std::string name;

    std::vector<Transition> transitions;

    bool end_state = false;

    explicit State(std::string name) : name(std::move(name)) {};

    void AddTrans(std::string in, std::string stack, std::vector<std::string> top, std::shared_ptr<State> to);

  }; // PDA::State


  std::vector<std::shared_ptr<State>> states; // Q

  std::vector<std::string> alpha_in; // Sigma

  std::vector<std::string> alpha_stack; // Gamma

  inline static std::shared_ptr<State> start; // q0

  inline static std::string start_sym; // Z0

  std::vector<std::string> stack;

 public:

  explicit PDA(std::ifstream &stream);

  void PrintPDA();

  bool Accept(std::string input,
      std::vector<std::string> stack = std::vector<std::string> {start_sym},
      std::shared_ptr<State> curr = start);


}; // PDA

#endif //PROGRAMEEROPDRACHT2__PDA_H_
