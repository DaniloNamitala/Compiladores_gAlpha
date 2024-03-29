grammar DeskLang;

@header{
 #include "antlr4-runtime.h"
}

program: globalstatement EOF #Nprogram;
functioncall: IDENT AP value? FP #Nfunctioncall;
block: KWBEGIN statement KWEND #Nblock;
function: DATATP? KWDO IDENT AP declaration? FP block #Nfunction;
globalstatement: (statement | function)* #Nglobalstatement;
output: KWOUT VALATRIB value #Noutput;
input: IDENT VALATRIB ( KWIN | value ) #Ninput;
retorno: KWRETURN value #Nretorno;
instruction: (input | output | retorno) #Ninstruction;
constant: (INTECONST | REALCONST | CHARCONST | BOOLCONST) #Nconstant;
value: (constant | IDENT | expr | logicalexpr | functioncall )#Nvalue;
logicalexpr: (AP logicalexpr FP logicalexpr2 | constant LOGOP value logicalexpr2| IDENT LOGOP value logicalexpr2| expr LOGOP value logicalexpr2) #Nlogicalexpr;
logicalexpr2: (LOGOP value logicalexpr2|) #Nlogicalexpr2 ;
expr:( AP expr FP expr2 | constant ARITOP value expr2 | IDENT ARITOP value expr2 | AP logicalexpr FP logicalexpr2 ARITOP value expr2
      | constant LOGOP value logicalexpr2 ARITOP value expr2 | IDENT LOGOP value logicalexpr2 ARITOP value expr2) #Nexpr;
expr2:  (ARITOP value expr2 | LOGOP value logicalexpr2 ARITOP value expr2|) #Nexpr2 ;
statement: (declaration | condition | loop | instruction)+ #Nstatement;
condition: KWIF value block (KWELSE block)? #Ncondition;
declaration: IDENT TPATRIB DATATP (VALATRIB value)? #Ndeclaration;
loop: KWWHILE value block #Nloop;

fragment LETRA: [a-zA-Z];
fragment NUMERO: [0-9];

KWIF: 'SE';
KWELSE: 'SENAO';
KWWHILE: 'ENQUANTO';
KWDO: 'FAZ';
KWIN: 'ENTRADA';
KWOUT: 'SAIDA';
KWBEGIN: 'INICIO';
KWEND: 'FIM';
KWRETURN: 'RETORNA';
BOOLCONST: ('VDD'|'FAL');
DATATP: ('REAL'|'INTE'|'BOOL'|'CHAR');
ARITOP: ('MAIS'|'MENOS'|'MULT'|'DIVI'|'MOD');
LOGOP: ('>'|'<'|'>='|'<='|'=='|'<>');
INTECONST: NUMERO+;
REALCONST: NUMERO+'.'NUMERO+;
CHARCONST: '"'(~('"'))*'"';
VALATRIB: '=';
TPATRIB: ':';
DELIM: ',';
IDENT: LETRA(LETRA|NUMERO)*;
AP: '(';
FP: ')';
WS : [ \t\r\n]+ -> skip ;