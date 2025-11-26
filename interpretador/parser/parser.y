%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "ast_nodes.h"
#include "scope.h"
#include "meta.h"
#include "error.h"
#include "func.h"
int yylex(void);
void yyerror(const char *s);

static char *strip_quotes(const char *parser_str) {
  if (parser_str == NULL)
    return NULL;

  size_t len = strlen(parser_str);
  if (len < 2)
    return strdup(parser_str);

  char *str = malloc(len - 1);
  if (!str)
    return NULL;

  strncpy(str, parser_str + 1, len - 2);
  str[len - 2] = '\0';

  return str;
}
%}

/* Define valor semântico (intValue) */
%union {
    char *strValue;
    double doubleValue;
    ASTNode *node;
    ParamList *params;
    Builtins func_type;
}

%token <doubleValue> NUM CHAR
%token <strValue> VAR_NAME VAR_TYPE STRING
%token SEMI ";" ATTR "=" COMMA ","

%type <node> decl stmt cond loop
%type <node> var_decl var_update
%type <node> scope inner_scope
%type <node> expr
%type <node> if_stmt else_stmt
%type <node> while_stmt do_while_stmt
%type <node> for_stmt
%type <node> opt_expr
%type <params> params param_list
%type <func_type> func

/* Operadores Condicionais*/
%token IF "if" ELSE "else"

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

%token WHILE "while"
%token DO "do"

%token FOR "for"
%token BREAK "break"
%token CONTINUE "continue"

%token MAIN

/* Funcões */
%token NODE_TEST_FUNC "test_func"
%token NODE_POW_FUNC "pow"
%token NODE_SQRT_FUNC "sqrt"
%token NODE_PRINTF    "printf"

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
       | program decl ";"   { exec_node($2); free_node($2); }
       | program MAIN scope { exec_node($3); free_node($3); }
       ;

scope: "{" inner_scope "}" { $$ = $2; };

inner_scope: /* empty */          { $$ = create_node_list(); }
           | inner_scope stmt ";" { add_list_node($1, $2); $$ = $1; }
           | inner_scope decl ";" { add_list_node($1, $2); $$ = $1; }
           | inner_scope cond     { add_list_node($1, $2); $$ = $1; }
           | inner_scope { is_loop++; }
             loop        { add_list_node($1, $3); $$ = $1; is_loop--; }
           | inner_scope expr ";" { add_list_node($1, $2); $$ = $1; }
           | inner_scope scope    { add_list_node($1, $2); $$ = $1; }
           ;

stmt: VAR_NAME[name] { $$ = create_var_node(VAR_PRINT, NULL, $name, NULL); }
    | BREAK  {
        if (is_loop)
          $$ = create_break_node();
        else
          exit_with_error(BREAK_OUT_OF_LOOP, parser_line);
      }
    | CONTINUE {
        if (is_loop)
          $$ = create_continue_node();
        else
          exit_with_error(CONTINUE_OUT_OF_LOOP, parser_line);
      }
    ;

cond: if_stmt       { $$ = $1; }
    ;

loop: while_stmt    { $$ = $1; }
    | do_while_stmt { $$ = $1; }
    | for_stmt      { $$ = $1; }
    ;

if_stmt: "if" "(" expr ")" decl ";" else_stmt { $$ = create_if_node($3, $5, $7); }
       | "if" "(" expr ")" stmt ";" else_stmt { $$ = create_if_node($3, $5, $7); }
       | "if" "(" expr ")" scope else_stmt    { $$ = create_if_node($3, $5, $6); }
       ;

else_stmt: { $$ = NULL; }
         | "else" decl ";" { $$ = $2; }
         | "else" stmt ";" { $$ = $2; }
         | "else" scope    { $$ = $2; }
         | "else" if_stmt  { $$ = $2; }
         ;

while_stmt: "while" "(" expr ")" scope    { $$ = create_while_node($3, $5, true); }
          | "while" "(" expr ")" decl ";" { $$ = create_while_node($3, $5, true); }
          | "while" "(" expr ")" stmt ";" { $$ = create_while_node($3, $5, true); }
          ;

do_while_stmt: "do" scope "while" "(" expr ")" ";" { $$ = create_while_node($5, $2, false); }

for_stmt:
      "for" "(" opt_expr ";" opt_expr ";" opt_expr ")" scope { $$ = create_for_node($3, $5, $7, $9); }
    | "for" "(" opt_expr ";" opt_expr ";" opt_expr ")" stmt  { $$ = create_for_node($3, $5, $7, $9); }
    | "for" "(" opt_expr ";" opt_expr ";" opt_expr ")" decl  { $$ = create_for_node($3, $5, $7, $9); }
    | "for" { printf("okay\n"); }
    ;

opt_expr:
      expr { $$ = $1; }
    | decl { $$ = $1; }
    |      { $$ = NULL; }
    ;

decl: var_decl   { $$ = $1; }
    | var_update { $$ = $1; }
    ;

var_decl: VAR_TYPE[type] VAR_NAME[name] {
            $$ = create_var_node(VAR_DECL, $type, $name, NULL);
		      }
        | error VAR_NAME[name] { exit_with_error(DECL_INVALID_TYPE, parser_line); }
        | VAR_TYPE[type] VAR_NAME[name] "=" expr {
            $$ = create_var_node(VAR_INIT, $type, $name, $expr);
          }
        | error VAR_NAME[name] "=" expr { exit_with_error(INIT_INVALID_TYPE, parser_line); }
        ;

var_update: VAR_NAME[name] "=" expr {
              $$ = create_var_node(VAR_UPDATE, NULL, $name, $expr);
            }
          ;

expr:
      "(" expr ")"    { $$ = create_expr_node(EXPR_PAR, NULL, $2, NULL); }
    | VAR_NAME "++"   { $$ = create_expr_node(EXPR_INC_POST, $1, NULL, NULL); }
    | VAR_NAME "--"   { $$ = create_expr_node(EXPR_DEC_POST, $1, NULL, NULL); }
    | "++" VAR_NAME   { $$ = create_expr_node(EXPR_INC_PREV, $2, NULL, NULL); }
    | "--" VAR_NAME   { $$ = create_expr_node(EXPR_DEC_PREV, $2, NULL, NULL); }
    | "-" expr        { $$ = create_expr_node(EXPR_NEG, NULL, $2, NULL); }
    | "!" expr        { $$ = create_expr_node(EXPR_NOT, NULL, $2, NULL); }
    | expr "*" expr   { $$ = create_expr_node(EXPR_TIMES, NULL, $1, $3); }
    | expr "/" expr   { $$ = create_expr_node(EXPR_DIV, NULL, $1, $3); }
    | expr "%" expr   { $$ = create_expr_node(EXPR_MOD, NULL, $1, $3); }
    | expr "<" expr   { $$ = create_expr_node(EXPR_LT, NULL, $1, $3); }
    | expr ">" expr   { $$ = create_expr_node(EXPR_GT, NULL, $1, $3); }
    | expr "<=" expr  { $$ = create_expr_node(EXPR_LE, NULL, $1, $3); }
    | expr ">=" expr  { $$ = create_expr_node(EXPR_GE, NULL, $1, $3); }
    | expr "==" expr  { $$ = create_expr_node(EXPR_EQUAL, NULL, $1, $3); }
    | expr "!=" expr  { $$ = create_expr_node(EXPR_NEQUAL, NULL, $1, $3); }
    | expr "&&" expr  { $$ = create_expr_node(EXPR_AND, NULL, $1, $3); }
    | expr "||" expr  { $$ = create_expr_node(EXPR_OR, NULL, $1, $3); }
    | expr "+" expr   { $$ = create_expr_node(EXPR_PLUS, NULL, $1, $3); }
    | expr "-" expr   { $$ = create_expr_node(EXPR_MINUS, NULL, $1, $3); }
    | func "(" params ")" { $$ = create_func_node($1, $3); }
    | NUM             { $$ = create_expr_node(EXPR_NUM, &$1, NULL, NULL); }
    | CHAR            { $$ = create_expr_node(EXPR_CHAR, &$1, NULL, NULL); }
    | VAR_NAME        { $$ = create_expr_node(EXPR_VAR, $1, NULL, NULL); }
    ;

func: "test_func" { $$ = TEST_FUNC; }
    | "pow"       { $$ = POW_FUNC; }
    | "sqrt"      { $$ = SQRT_FUNC; }
    | "printf"    { $$ = PRINTF; }
    ;

params: /* empty */         { $$ = create_param_list(); }
      | param_list          { $$ = $1; }
      ;

param_list: NUM      { $$ = create_param_list(); add_param($$, &$1, DOUBLE); }
          | CHAR     { $$ = create_param_list(); add_param($$, &$1, VAR_CHAR); }
          | VAR_NAME { $$ = create_param_list(); add_param($$, $1, VAR); }
          | STRING   {
              $$ = create_param_list();
              char *s = strip_quotes($1);
              free($1);
              add_param($$, s, VAR);
            }
          | param_list "," NUM      { add_param($1, &$3, DOUBLE); $$ = $1; }
          | param_list "," CHAR     { add_param($1, &$3, VAR_CHAR); $$ = $1; }
          | param_list "," VAR_NAME { add_param($1, $3, VAR);       $$ = $1; }
          | param_list "," STRING   {
              char *s = strip_quotes($3);
              free($3);
              add_param($1, s, VAR);
              $$ = $1;
            }
          ;

%%

int main(void) {
  stack_scope();
  int r = yyparse();
  pop_scope();
  return r;
}

void yyerror(const char *s) {
  exit_with_error(SYNTAX_ERROR, parser_line);
}
