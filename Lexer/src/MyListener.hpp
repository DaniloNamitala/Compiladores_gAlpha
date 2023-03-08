#include "antlr4-runtime.h"
#include "SymbolTable.hpp"
#include "../lib/DeskLangBaseListener.h"
#include <iostream>

using namespace antlr4;
using namespace std;

class MyListener: public DeskLangBaseListener {
private:
    SymbolTable<string, string>* currentScope;
    SymbolTable<string, string>* functionTable;
    DeskLangParser* parser;


    void verificaFuncoesNaoDeclaradas(string id, int8_t line){
        if (!functionTable->symbolExists(id)) {
            cerr << "Line " << line << ": function not declared: " << "variavel " + id + " não declarada neste escopo" << endl;
        }
    }

    void verificaVariaveisNaoDeclaradas(string id, int8_t line){
        if(!currentScope->symbolExists(id)) {
            cerr << "Line " << line << ": Variable not declared: " << "variavel " + id + " não declarada neste escopo" << endl;
            throw_with_nested("Variable not declared: " + id);
        }
    }

    void validaValorDestino(string tipoValor, string tipoDestino, int8_t line){
        if(!equal(tipoValor.begin(), tipoValor.end(), tipoDestino.begin())){
            cerr << "Line " << line << ": Invalid assignment: " << "valor " + tipoValor + " não pode ser atribuido a variavel do tipo " + tipoDestino << endl;
        }
    }

    string getValueType(DeskLangParser::ValueContext* value) {
        DeskLangParser::NvalueContext* ctx = (DeskLangParser::NvalueContext*)value;
        if (ctx->constant() != NULL) {
            DeskLangParser::NconstantContext* constantCtx = (DeskLangParser::NconstantContext*)ctx->constant();
            return getConstantype(constantCtx);
        } else if (ctx->IDENT() != NULL) {
            string id = ctx->IDENT()->getText();
            verificaVariaveisNaoDeclaradas(id, ctx->getStart()->getLine());
            return getVarType(id);
        } else if (ctx->logicalexpr() != NULL) {
            return "BOOL";
        } else if (ctx->functioncall() != NULL){
            string id = ((DeskLangParser::NfunctioncallContext*)ctx->functioncall())->IDENT()->getText();
            verificaFuncoesNaoDeclaradas(id, ctx->getStart()->getLine());
            return getFunctionType(id);
        } else {
            return "REAL";
        }
        return "";
    }

    string getConstantype(DeskLangParser::NconstantContext* ctx) {
        auto tokenType = ctx->getStart()->getType();
        switch (tokenType){
            case DeskLangLexer::INTECONST:
                return "INTE";
                break;
            case DeskLangLexer::REALCONST:
                return "REAL";
                break;
            case DeskLangLexer::BOOLCONST:
                return "BOOL";
                break;
            case DeskLangLexer::CHARCONST:
                return "CHAR";
                break;
            default:
                return "";
                break;
        }
    }

    string getFunctionType(string id) {
        auto type = functionTable->get(id);
        return type;
    }

    string getVarType(string id) {
        auto type = currentScope->get(id);
        return type;
    }

public:
    MyListener(DeskLangParser* parser) {
        this->parser = parser;
        currentScope = new SymbolTable<string, string>(NULL);
        functionTable = new SymbolTable<string, string>(NULL);
    }

    void exitNdeclaration(DeskLangParser::NdeclarationContext *context) override {
        string tipo = context->DATATP()->getText();
        string id = context->IDENT()->getText();
        
        if (context->value() != NULL) {
            string valueType = getValueType(context->value());
            validaValorDestino(valueType, tipo, context->getStart()->getLine());
        }

        if(!currentScope->symbolExists(id)) {
            currentScope->addSymbol(id, tipo);
        } else {
            cerr << "Line " << context->getStart()->getLine() << ": Duplicated variable: " << "variavel " + id + " já declarada neste escopo" << endl;
        }
    }

    void exitNinput(DeskLangParser::NinputContext *context) override {
        string id = context->IDENT()->getText();
        verificaVariaveisNaoDeclaradas(id, context->getStart()->getLine());
        if (context->KWIN() != NULL) return;
        
        auto valor = context->value();
        string tipoDestino = getVarType(id);
        string tipoValor = getValueType(valor);
        validaValorDestino(tipoValor, tipoDestino, context->getStart()->getLine());
    }

    void enterNblock(DeskLangParser::NblockContext *context) override {
        currentScope = currentScope->createSubSope();
    }

    void exitNblock(DeskLangParser::NblockContext *context) override {
        SymbolTable<string, string>* old = currentScope;
        currentScope = currentScope->superScope();
        delete old;
    }

    void exitNfunctioncall(DeskLangParser::NfunctioncallContext* context) override { 
        string id = context->IDENT()->getText();
        verificaFuncoesNaoDeclaradas(id, context->getStart()->getLine());
    }

    void exitNfunction(DeskLangParser::NfunctionContext* context) override {
        string id = context->IDENT()->getText();
        string type = (context->DATATP() != NULL)? context->DATATP()->getText() : "";
        if (functionTable->symbolExists(id)) {
            cerr << "Line " << context->getStart()->getLine() << ": Duplicated function: " << "variavel " + id + " já declarada neste escopo" << endl;
        } else {
            functionTable->addSymbol(id, type);
        }
    }
};