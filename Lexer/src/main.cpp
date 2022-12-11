#include <iostream>
#include <fstream>
#include "antlr4-runtime.h"
#include "../lib/DeskLang.h"

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
  DeskLang lexer(&stream);

  while(!lexer.hitEOF) {
    auto token = lexer.nextToken();
    cout << "Token: " + token->toString() << endl;
    cout << "   Lexema: " + token->getText() << endl;
    cout << "   Classe: " + lexer.getVocabulary().getDisplayName(token->getType()) << endl;
  }
  return 0;
}