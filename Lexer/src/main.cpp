#include <iostream>
#include <fstream>
#include "antlr4-runtime.h"
#include "../lib/DeskLangLexer.h"
#include "../lib/DeskLangParser.h"
#include "MyListener.cpp"

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

  ANTLRInputStream stream(file);
  DeskLangLexer lexer(&stream);

  CommonTokenStream tokens(&lexer);
  DeskLangParser parser(&tokens);

  MyListener listener = *new MyListener();

  parser.removeParseListeners();
  parser.addParseListener(&listener);

  cout << parser.program()->toStringTree() << endl;

  // while(!lexer.hitEOF) {
  //   auto token = lexer.nextToken();
  //   cout << "Token: " + token->toString() << endl;
  //   cout << "   Lexema: " + token->getText() << endl;
  //   cout << "   Classe: " + lexer.getVocabulary().getDisplayName(token->getType()) << endl;
  // }

  return 0;
}
