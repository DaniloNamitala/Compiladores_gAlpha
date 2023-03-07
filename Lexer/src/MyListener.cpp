# include "antlr4-runtime.h"
# include "map"
# include "../lib/DeskLangBaseListener.h"
#include <iostream>

using namespace antlr4;
using namespace std;

class MyListener: public DeskLangBaseListener {

private:
    map<string, string> tabelaSimbolos;

    void verificaVariaveisNaoDeclaradas(string id){
        if(tabelaSimbolos.find(id) == tabelaSimbolos.end()) {
            cerr << "Variable not declared: " << "variavel " + id + " não declarada" << endl;
            throw_with_nested("Variable not declared: " + id);
        }
    }

    void validaValorDestino(string tipoValor, string tipoDestino, string valor){
        if(!tipoValor.empty()){
            if(!equal(tipoValor.begin(), tipoValor.end(), tipoDestino.begin())){
                cerr << "Invalid assignment: " << "valor " + tipoValor + " não pode ser atribuido a variavel do tipo " + tipoDestino << endl;
            }
        }else {
            if (equal(tipoDestino.begin(), tipoDestino.end(), "INTE") && valor.find('"') != string::npos) {
                cerr << "Invalid assignment: "
                     << "valor " + valor + " não pode ser atribuido a variavel do tipo " + tipoDestino << endl;
            } else if (equal(tipoDestino.begin(), tipoDestino.end(), "REAL") && valor.find('"') != string::npos) {
                cerr << "Invalid assignment: "
                     << "valor " + valor + " não pode ser atribuido a variavel do tipo " + tipoDestino << endl;
            } else if (equal(tipoDestino.begin(), tipoDestino.end(), "INTE") && valor.find(".") != string::npos) {
                cerr << "Invalid assignment: "
                     << "valor " + valor + " não pode ser atribuido a variavel do tipo " + tipoDestino << endl;
            } else if (equal(tipoDestino.begin(), tipoDestino.end(), "REAL") && valor.find(".") != string::npos) {
                cerr << "Invalid assignment: "
                     << "valor " + valor + " não pode ser atribuido a variavel do tipo " + tipoDestino << endl;
            }
        }
    }

public:

    MyListener() {
        tabelaSimbolos = *new map<string, string>();
    }

    void exitNdeclaration(DeskLangParser::NdeclarationContext *context) override {
        string tipo = context->DATATP()->getText();
        string id = context->IDENT()->getText();

        if(tabelaSimbolos.find(id) == tabelaSimbolos.end()) {
            tabelaSimbolos.insert(pair<string, string>(id, tipo));
        } else {
            cerr << "Duplicated variable: " << "variavel " + id + " já declarada" << endl;
        }
    }

    void exitNinput(DeskLangParser::NinputContext *context) override {
        string id = context->IDENT()->getText();
        string valor = context->value()->getText();
        string tipoValor = tabelaSimbolos[valor];
        string tipoDestino = tabelaSimbolos[id];

        verificaVariaveisNaoDeclaradas(id);
        validaValorDestino(tipoValor, tipoDestino, valor);
    }

    map<string, string> getTabelaSimbolos() {
      return tabelaSimbolos;
    }
};