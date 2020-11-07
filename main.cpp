#include <iostream>
#include <fstream>
#include <string>
#include <utility>


#include "src/CFG.h"
#include "src/CYK.h"
#include "src/PDA2CFG.h"

int main(int argc, char *argv[]) {
   std::string temp = argv[1];
   if (argc < 1) {
      std::cout << "no arguments were given" << std::endl;
      return -1;
   }
   if (temp == "cyk") {
      std::ifstream file;
      file.open(argv[2]);
      std::string input = argv[3];
      CFG cfg(file);
      CYK cyk(cfg, input);
      cyk.ToHTML(argv[4]);
      return 1;
   }
   else if("pda2cfg" == temp) {
      std::ifstream file;
      file.open(argv[2]);
      PDA pda(file);
      auto i = PDA2CFG(pda);
      i->print(argv[3]);
      return 2;
   }

   std::cout << "no available algorithm was selected" << std::endl;
   return -1;
}
