#include <iostream>

#include "src/CFG.h"
#include "src/CYK.h"
#include <fstream>

int main() {
   std::ifstream file;
   file.open("examples/CFG.json");
   CFG cfg(file);
   CYK cyk(cfg, "baaba");
}
