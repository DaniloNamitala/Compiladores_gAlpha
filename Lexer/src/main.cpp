#include <iostream>
#include <fstream>
#include "antlr4-runtime.h"
#include "../lib/DeskLangLexer.h"
#include "../lib/DeskLangParser.h"
#include "MyListener.hpp"

using namespace std;
using namespace antlr4;

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    cerr << "Missing Input File\n";
    return 1;
  }

  char *filename = argv[1];

  ifstream file(filename);

  ANTLRInputStream* stream = new ANTLRInputStream(file);
  DeskLangLexer* lexer = new DeskLangLexer(stream);
  CommonTokenStream* tokens = new CommonTokenStream(lexer);
  DeskLangParser* parser = new DeskLangParser(tokens);

  MyListener* listener = new MyListener(parser);
  tree::ParseTree* inicio = parser->program();
  tree::ParseTreeWalker* walker = new tree::ParseTreeWalker();
  walker->walk(listener, inicio);
  return 0;
}
