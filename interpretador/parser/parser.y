%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "ast_nodes.h"
#include "scope.h"
#include "meta.h"
#include "error.h"
int yylex(void);
void yyerror(const char *s);
%}

/* Define valor semântico (intValue) */
%union {
    char *strValue;
    double doubleValue;
    ASTNode *node;
}

%token <doubleValue> NUM CHAR
%token <strValue> VAR_NAME VAR_TYPE
%token SEMI ";" ATTR "="

%type <node> decl stmt
%type <node> var_decl var_update
%type <node> scope
%type <node> expr

/* Operadores Condicionais*/
%token IF ELSE

/* Operações */
%token PLUS "+" MINUS "-" 
%token TIMES "*" DIVIDE "/" MOD "%"

/* Operações lógicas */
%token EQ "==" NE "!="
%token LT "<" GT ">" LE "<=" GE ">="
%token AND "&&" OR "||" NOT "!"

/* Operadores unarios*/
%token INCR "++" DECR "--"

%token LPAREN "(" RPAREN ")"
%token LBRACK "{" RBRACK "}"

/* Precedência e associatividade */ 
%left PLUS MINUS
%left TIMES DIVIDE MOD
%left EQ NE
%left LT GT LE GE
%left AND OR
%right INCR DECR
%right NOT

%start program

%%

program: 
       | program stmt     { exec_node($2); free_node($2); }
       | program decl     { exec_node($2); free_node($2); }
       | program scope    { exec_node($2); free_node($2); }
       | program expr     { exec_node($2); free_node($2); }
       ;

scope: "{"         { $<node>list = current_list; 
                     current_list = create_node_list(); }[list]
       inner_scope
       "}"         { $$ = current_list; current_list = $<node>list; }
     ;



inner_scope:
           | inner_scope stmt { add_list_node($2); }
           | inner_scope decl { add_list_node($2); }
           | inner_scope 
             "{"         { $<node>list = current_list; 
                           current_list = create_node_list(); }[list]
             inner_scope 
             "}"         { ASTNode *l = current_list;
                           current_list = $<node>list;
                           add_list_node(l); }

stmt: VAR_NAME[name] ";" { $$ = create_var_node(VAR_PRINT, NULL, $name, NULL); }
    ;

decl: var_decl   { $$ = $1; }
    | var_update { $$ = $1; }
    ;

var_decl: VAR_TYPE[type] VAR_NAME[name] ";" {
            $$ = create_var_node(VAR_DECL, $type, $name, NULL);
		      }
        | error VAR_NAME[name] ";" { exit_with_error(DECL_INVALID_TYPE); }
        | VAR_TYPE[type] VAR_NAME[name] "=" expr ";" {
            $$ = create_var_node(VAR_INIT, $type, $name, $expr);
          }
        | error VAR_NAME[name] "=" expr ";" { exit_with_error(INIT_INVALID_TYPE); }
        ;

var_update: VAR_NAME[name] "=" expr ";" {
              $$ = create_var_node(VAR_UPDATE, NULL, $name, $expr);
            }
          ;

expr:
      "(" expr ")"   { $$ = create_expr_node(EXPR_PAR, NULL, $2, NULL); }
    | VAR_NAME "++"  { $$ = create_expr_node(EXPR_INC_POST, $1, NULL, NULL); }   /* x++ */
    | VAR_NAME "--"  { $$ = create_expr_node(EXPR_DEC_POST, $1, NULL, NULL); }   /* x-- */
    | "++" VAR_NAME  { $$ = create_expr_node(EXPR_INC_PREV, $2, NULL, NULL); }   /* ++x */
    | "--" VAR_NAME  { $$ = create_expr_node(EXPR_DEC_PREV, $2, NULL, NULL); }   /* --x */
    | "-" expr       { $$ = create_expr_node(EXPR_NEG, NULL, $2, NULL); }
    | "!" expr       { $$ = create_expr_node(EXPR_NOT, NULL, $2, NULL); }
    | expr "*" expr  { $$ = create_expr_node(EXPR_TIMES, NULL, $1, $3); }
    | expr "/" expr  { $$ = create_expr_node(EXPR_DIV, NULL, $1, $3); }
    | expr "%" expr  { $$ = create_expr_node(EXPR_MOD, NULL, $1, $3); }
    | expr "<" expr  { $$ = create_expr_node(EXPR_LT, NULL, $1, $3); }
    | expr ">" expr  { $$ = create_expr_node(EXPR_GT, NULL, $1, $3); }
    | expr "<=" expr { $$ = create_expr_node(EXPR_LE, NULL, $1, $3); }
    | expr ">=" expr { $$ = create_expr_node(EXPR_GE, NULL, $1, $3); }
    | expr "==" expr { $$ = create_expr_node(EXPR_EQUAL, NULL, $1, $3); }
    | expr "!=" expr { $$ = create_expr_node(EXPR_NEQUAL, NULL, $1, $3); }
    | expr "&&" expr { $$ = create_expr_node(EXPR_AND, NULL, $1, $3); }
    | expr "||" expr { $$ = create_expr_node(EXPR_OR, NULL, $1, $3); }
    | expr "+" expr  { $$ = create_expr_node(EXPR_PLUS, NULL, $1, $3); }
    | expr "-" expr  { $$ = create_expr_node(EXPR_MINUS, NULL, $1, $3); }
    | NUM            { $$ = create_expr_node(EXPR_NUM, &$1, NULL, NULL); }
    | CHAR           { $$ = create_expr_node(EXPR_CHAR, &$1, NULL, NULL); }
    | VAR_NAME       { $$ = create_expr_node(EXPR_VAR, $1, NULL, NULL); }
    | error          { exit_with_error(UNKNOWN_SYMBOL); }
    ;

%%

int main(void) {
  stack_scope();
  int r = yyparse();
  pop_scope();
  return r;
}

void yyerror(const char *s) {
  fprintf(stderr, "[ERRO] Sintaxe inválida na linha %d\n", line);
}
