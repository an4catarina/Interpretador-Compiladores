%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "utils.h"
#include "meta.h"
#include "parser.tab.h"
%}

%option always-interactive

N   [0-9]
NSZ [1-9]
AN  [a-zA-Z0-9_]
AL  [_a-zA-Z]

%%

";" { return SEMI; }

"=" { return ATTR; }

"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return DIVIDE; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACK; }
"}"             { return RBRACK; }
"++"            { return INCR; }
"--"            { return DECR; }
"%"             { return MOD; }

"if"            { return IF; }
"else"          { return ELSE; }

"=="            { return EQ; }
"!="            { return NE; }
"<"             { return LT; }
">"             { return GT; }
"<="            { return LE; }
">="            { return GE; }
"&&"            { return AND; }
"||"            { return OR; }
"!"             { return NOT; }

("int"|"float"|"double"|"char") {
    yylval.strValue = strdup(yytext);
    return VAR_TYPE;
}

{AL}{AN}* {
    yylval.strValue = strdup(yytext);
    return VAR_NAME;
}

[+-]?{N}+(\.{N}+)?  {
    yylval.doubleValue = atof(yytext);
    return NUM;
}

'(\\)?.' {
    yylval.doubleValue = convert_char(yytext);
    return CHAR;
}

[ \t]+    { /* não faz nada */ }

"//".*    { /* Comentário */}

\n        { line++; }

.         { /* printf("Caractere não reconhecido: %s\n", yytext); */ }

%%

int yywrap(void) {
    return 1;
}
