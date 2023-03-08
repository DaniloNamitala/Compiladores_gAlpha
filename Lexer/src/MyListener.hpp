#include "antlr4-runtime.h"
#include "SymbolTable.hpp"
#include "../lib/DeskLangBaseListener.h"
#include <iostream>

using namespace antlr4;
using namespace std;

class MyListener: public DeskLangBaseListener {
private:
    SymbolTable<string, string>* currentScope;

    void verificaVariaveisNaoDeclaradas(string id, int8_t line){
        if(!currentScope->symbolExists(id)) {
            cerr << "Line " << line << ": Variable not declared: " << "variavel " + id + " não declarada neste escopo" << endl;
            throw_with_nested("Variable not declared: " + id);
        }
    }

    void validaValorDestino(string tipoValor, string tipoDestino, string valor, int8_t line){
        if(!tipoValor.empty()){
            if(!equal(tipoValor.begin(), tipoValor.end(), tipoDestino.begin())){
                cerr << "Line " << line << ": Invalid assignment: " << "valor " + tipoValor + " não pode ser atribuido a variavel do tipo " + tipoDestino << endl;
            }
        }else {
            if (equal(tipoDestino.begin(), tipoDestino.end(), "INTE") && valor.find('"') != string::npos) {
                cerr << "Line " << line << ": Invalid assignment: "
                     << "valor " + valor + " não pode ser atribuido a variavel do tipo " + tipoDestino << endl;
            } else if (equal(tipoDestino.begin(), tipoDestino.end(), "REAL") && valor.find('"') != string::npos) {
                cerr << "Line " << line << ": Invalid assignment: "
                     << "valor " + valor + " não pode ser atribuido a variavel do tipo " + tipoDestino << endl;
            } else if (equal(tipoDestino.begin(), tipoDestino.end(), "INTE") && valor.find(".") != string::npos) {
                cerr << "Line " << line << ": Invalid assignment: "
                     << "valor " + valor + " não pode ser atribuido a variavel do tipo " + tipoDestino << endl;
            } else if (equal(tipoDestino.begin(), tipoDestino.end(), "REAL") && valor.find(".") != string::npos) {
                cerr << "Line " << line << ": Invalid assignment: "
                     << "valor " + valor + " não pode ser atribuido a variavel do tipo " + tipoDestino << endl;
            }
        }
    }

public:

    MyListener() {
        currentScope = new SymbolTable<string, string>(NULL);
    }

    void exitNdeclaration(DeskLangParser::NdeclarationContext *context) override {
        string tipo = context->DATATP()->getText();
        string id = context->IDENT()->getText();

        if(!currentScope->symbolExists(id)) {
            currentScope->addSymbol(id, tipo);
        } else {
            cerr << "Line " << context->getStart()->getLine() << ": Duplicated variable: " << "variavel " + id + " já declarada neste escopo" << endl;
        }
    }

    void exitNinput(DeskLangParser::NinputContext *context) override {
        string id = context->IDENT()->getText();
        string valor = context->value()->getText();
        verificaVariaveisNaoDeclaradas(id, context->getStart()->getLine());
        string tipoValor = currentScope->get(valor);
        string tipoDestino = currentScope->get(id);
        validaValorDestino(tipoValor, tipoDestino, valor, context->getStart()->getLine());
    }

    void enterNblock(DeskLangParser::NblockContext *context) override {
        currentScope = currentScope->createSubSope();
    }

    void exitNblock(DeskLangParser::NblockContext *context) override {
        SymbolTable<string, string>* old = currentScope;
        currentScope = currentScope->superScope();
        delete old;
    }
};