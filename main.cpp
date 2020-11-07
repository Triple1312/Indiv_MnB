#include <iostream>

#include "src/CFG.h"
#include "src/CYK.h"
#include "src/PDA2CFG.h"
#include <fstream>

int main() {
   std::ifstream file;
   file.open("examples/PDA.json");
   PDA pda(file);
   auto i = PDA2CFG(pda);
   CFG cfg(file);
   CYK cyk(cfg, "aab");
   cyk.ToHTML();
}
