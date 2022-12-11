
// Generated from DeskLang.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"




class  DeskLangLexer : public antlr4::Lexer {
public:
  enum {
    IF = 1, ELSE = 2, WHILE = 3, DO = 4, IN = 5, OUT = 6, BEGIN = 7, END = 8, 
    RETURN = 9, BOOLCONST = 10, DATATP = 11, ARITOP = 12, LOGOP = 13, INTECONST = 14, 
    REALCONSNT = 15, CHARCONST = 16, VALATRIB = 17, TPATRIB = 18, DELIM = 19, 
    IDENT = 20, WS = 21
  };

  DeskLangLexer(antlr4::CharStream *input);
  ~DeskLangLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

