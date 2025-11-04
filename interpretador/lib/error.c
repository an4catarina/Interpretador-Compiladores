#include "error.h"
#include <stdio.h>
#include <stdlib.h>

void exit_with_error(const ErrorType e, int line) {
  switch (e) {
  case SYNTAX_ERROR:
    fprintf(stderr, "[ERRO] Sintaxe inválida na linha %d\n", line);
    break;
  case DECL_INVALID_TYPE:
    fprintf(stderr,
            "[ERRO] Declaração de variável de tipo inválido na linha %d\n",
            line);
    break;
  case INIT_INVALID_TYPE:
    fprintf(stderr,
            "[ERRO] Inicialização de variável de tipo inválido na linha %d\n",
            line);
    break;
  case UNKNOWN_SYMBOL:
    fprintf(stderr, "[ERRO] Símbolo ou operação desconhecidos na linha %d\n",
            line);
    break;
  case UNKNOWN_VAR:
    fprintf(stderr, "[ERRO] Uso de variável desconhecida na linha %d\n", line);
    break;
  case VAR_REDECLARATION:
    fprintf(stderr, "[ERRO] Redeclaração de variável na linha %d\n", line);
    break;
  case DIV_BY_ZERO:
    fprintf(stderr, "[ERRO] Divisão por 0 na linha %d\n", line);
    break;
  case MOD_BY_ZERO:
    fprintf(stderr, "[ERRO] Operação de módulo com 0 na linha %d\n", line);
    break;
  }
  exit(1);
}
