%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "utils.h"
#include "meta.h"
#include "func.h"
#include "parser.tab.h"
#include "error.h"
%}

%option always-interactive

N   [0-9]
NSZ [1-9]
AN  [a-zA-Z0-9_]
AL  [_a-zA-Z]

%%

";" { return SEMI; }
"," { return COMMA; }

"=" { return ATTR; }

"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return DIVIDE; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"{"             { return LBRACK; }
"}"             { return RBRACK; }
"["             { return LBRACKET; }
"]"             { return RBRACKET; }
"++"            { return INCR; }
"--"            { return DECR; }
"%"             { return MOD; }
"while"         { return WHILE; }
"do"            { return DO; }

"if"            { return IF; }
"else"          { return ELSE; }

"for"           { return FOR; }
"break"         { return BREAK; }
"continue"      { return CONTINUE; }

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

"test_func"    { return NODE_TEST_FUNC; }
"pow"          { return NODE_POW_FUNC;  }
"sqrt"         { return NODE_SQRT_FUNC; }
"printf"       { return NODE_PRINTF; }

\"([^\"\\]|\\.)*\" {
    yylval.strValue = strdup(yytext);
    return STRING;
}

{AL}{AN}* {
    yylval.strValue = strdup(yytext);
    return VAR_NAME;
}

{N}+(\.{N}+)?  {
    yylval.doubleValue = atof(yytext);
    return NUM;
}

'(\\)?.' {
    yylval.doubleValue = convert_char(yytext);
    return CHAR;
}

[ \t]+    { /* ignora */ }

"//".*    { /* ignora */ }

"int main()" {
               if (!main_declared) {
                 main_declared = 1;
                 return MAIN;
               } else {
                 exit_with_error(MULTIPLE_MAINS, parser_line);
               }
             }

\n        { parser_line++; }

.

%%

int yywrap(void) {
    return 1;
}