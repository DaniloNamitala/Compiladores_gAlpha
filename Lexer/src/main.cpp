#include <iostream>
#include <fstream>
#include "antlr4-runtime.h"
#include "../lib/DeskLangLexer.h"

using namespace std;
using namespace antlr4;

int main(int argc, char** argv) {
  if (argc < 2) {
    cerr << "Missing Input File\n";
    return 1;
  }

  char* filename = argv[1];
  ifstream file(filename);
  ANTLRInputStream stream(file);
  DeskLangLexer lexer(&stream);

  while(!lexer.hitEOF) {
    cout << lexer.getToken()->toString() << endl;
  }
  return 0;
}