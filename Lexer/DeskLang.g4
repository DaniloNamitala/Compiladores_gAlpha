grammar DeskLang;

//lexer grammar DeskLang;

fragment LETRA: [a-zA-Z];
fragment NUMERO: [0-9];

KWIF: 'SE';
KWELSE: 'SENAO';
KWWHILE: 'ENQUANTO';
KWDO: 'FAZ';
KWIN: 'ENTRADA';
KWOUT: 'SAIDA';
KWBEGIN: 'INICIO';
KWEND: 'END';
KWRETURN: 'RETORNA';
BOOLCONST: ('VDD'|'FAL');
DATATP: ('REAL'|'INTE'|'BOOL'|'CHAR');
ARITOP: ('MAIS'|'MENOS'|'MULT'|'DIVI'|'MOD');
LOGOP: ('>'|'<'|'>='|'<='|'=='|'<>');
INTECONST: NUMERO+;
REALCONST: NUMERO+'.'NUMERO+;
CHARCONST: '"'(.~'"')*'"';
VALATRIB: '=';
TPATRIB: ':';
DELIM: ',';
IDENT: LETRA(LETRA|NUMERO)*;
AP: '(';
FP: ')';
WS : [ \t\r\n]+ -> skip ;

program: globalstatement+;
functioncall: IDENT AP value? FP;
function: DATATP? KWDO IDENT AP declaration FP KWBEGIN statement KWEND;
globalstatement: statement | function;
output: KWOUT VALATRIB value;
input: IDENT VALATRIB KWIN;
instruction: input | output;
constant: INTECONST | REALCONST | CHARCONST;
value: constant | IDENT | expr | logicalexpr;
logicalexpr: AP logicalexpr FP logicalexpr2 | constant LOGOP value logicalexpr2| IDENT LOGOP value logicalexpr2| expr LOGOP value logicalexpr2;
logicalexpr2: LOGOP value logicalexpr2| ;
expr: AP expr FP expr2 | constant ARITOP value expr2 | IDENT ARITOP value expr2 | AP logicalexpr FP logicalexpr2 ARITOP value expr2
      | constant LOGOP value logicalexpr2 ARITOP value expr2 | IDENT LOGOP value logicalexpr2 ARITOP value expr2;
expr2:  ARITOP value expr2 |LOGOP value logicalexpr2 ARITOP value expr2| ;
statement: declaration | condition | loop | instruction;
condition: KWIF value KWBEGIN statement KWEND (KWELSE KWBEGIN statement KWEND)?;
declaration: IDENT TPATRIB DATATP (VALATRIB value)?;
loop: KWWHILE value KWBEGIN statement KWEND;