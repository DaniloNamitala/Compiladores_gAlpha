grammar DeskLang;

fragment C: [a-zA-Z];
fragment D: [0-9];

IF: 'SE';
ELSE: 'SENAO';
WHILE: 'ENQUANTO';
DO: 'FAZ';
IN: 'ENTRADA';
OUT: 'SAIDA';
BEGIN: 'INICIO';
END: 'END';
RETURN: 'RETORNA';
BOOLCONST: ('VDD'|'FAL');
DATATP: ('REAL'|'INTE'|'BOOL'|'CHAR');
ARITOP: ('MAIS'|'MENOS'|'MULT'|'DIVI');
LOGOP: ('>'|'<'|'>='|'<='|'=='|'<>');
INTECONST: D+;
REALCONSNT: D+'.'D+;
CHARCONST: '"'(.~'"')*'"';
VALATRIB: '=';
TPATRIB: ':';
DELIM: ',';
IDENT: '_'?D(D|C)*;

WS: [ \n\r\t]* ->skip;