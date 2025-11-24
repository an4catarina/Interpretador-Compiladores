#include "ast_rules.h"
#include "ast.h"
#include "ast_nodes.h"
#include "error.h"
#include "func.h"
#include "scope.h"
#include "utils.h"
#include "var.h"
#include <stdio.h>
#include <string.h>

static ExecReturn exec_operator_expr(NodeType type, ASTNode *node);
static ExecReturn exec_variable_expr(NodeType type, ASTNode *node);

ExecReturn exec_var_decl(ASTNode *node) {
  VarNode *data = node->data;
  char *type = data->type;
  char *name = data->name;
  bool success;

  if (strcmp(type, "int") == 0) {
    success = add_var(INT, name, NULL);
  }

  else if (strcmp(type, "float") == 0) {
    success = add_var(FLOAT, name, NULL);
  }

  else if (strcmp(type, "double") == 0) {
    success = add_var(DOUBLE, name, NULL);
  }

  else if (strcmp(type, "char") == 0) {
    success = add_var(VAR_CHAR, name, NULL);
  }

  if (success) {
    printf("[DEBUG] Declaração de variável: %s\n", name);
    return (ExecReturn){EXEC_OK, 0};
  } else {
    exit_with_error(VAR_REDECLARATION, node->line);
    return (ExecReturn){EXEC_FAIL, 0};
  }
}

ExecReturn exec_var_init(ASTNode *node) {
  VarNode *data = node->data;
  char *type = data->type;
  char *name = data->name;
  ExecReturn ret = exec_node(data->value);
  if (ret.status != EXEC_OK)
    return ret;
  double value = ret.value;
  bool success;

  if (strcmp(type, "int") == 0) {
    int i = value;
    success = add_var(INT, name, &i);
  }

  else if (strcmp(type, "float") == 0) {
    float f = value;
    success = add_var(FLOAT, name, &f);
  }

  else if (strcmp(type, "double") == 0) {
    double d = value;
    success = add_var(DOUBLE, name, &d);
  }

  else if (strcmp(type, "char") == 0) {
    char c = value;
    success = add_var(VAR_CHAR, name, &c);
  }

  if (success) {
    printf("[DEBUG] Inicializando a variável: %s\n", name);
    return (ExecReturn){EXEC_OK, 0};
  } else {
    exit_with_error(VAR_REDECLARATION, node->line);
    return (ExecReturn){EXEC_FAIL, 0};
  }
}

ExecReturn exec_var_update(ASTNode *node) {
  VarNode *data = node->data;
  char *name = data->name;
  ExecReturn ret = exec_node(data->value);
  if (ret.status != EXEC_OK)
    return ret;
  double value = ret.value;
  bool success;

  VarList *l = current_scope->var_list;
  Var *var = get_var(name);

  if (var == NULL)
    exit_with_error(UNKNOWN_VAR, node->line);

  switch (var->type) {
  case INT:
    success = update_var(INT, var, &value);
    break;
  case FLOAT:
    success = update_var(FLOAT, var, &value);
    break;
  case DOUBLE:
    success = update_var(DOUBLE, var, &value);
    break;
  case VAR_CHAR:
    success = update_var(VAR_CHAR, var, &value);
    break;
  default:
    return (ExecReturn){EXEC_FAIL, 0};
  }

  if (success) {
    printf("[DEBUG] Atualizando valor da variável: %s\n", name);
    return (ExecReturn){EXEC_OK, 0};
  }
  return (ExecReturn){EXEC_FAIL, 0};
}

ExecReturn exec_expr_node(NodeType type, ASTNode *node) {
  switch (type) {
  case EXPR_NUM ... EXPR_CHAR:
    ExprNode *expr = node->data;
    double *n = expr->value;
    return (ExecReturn){EXEC_OK, *n};
  case EXPR_PLUS ... EXPR_PAR:
    return exec_operator_expr(type, node);
  case EXPR_INC_PREV ... EXPR_VAR:
    return exec_variable_expr(type, node);
  default:
    return (ExecReturn){EXEC_OK, 0};
  }
}

static ExecReturn exec_operator_expr(NodeType type, ASTNode *node) {
  ExprNode *expr = node->data;
  double left = 0;
  double right = 0;
  ExecReturn ret;

  if (expr->left_expr) {
    ret = exec_node(expr->left_expr);
    if (ret.status != EXEC_OK)
      return ret;
    left = ret.value;
  }

  if (expr->right_expr) {
    ret = exec_node(expr->right_expr);
    if (ret.status != EXEC_OK)
      return ret;
    right = ret.value;
  }

  switch (type) {
  case EXPR_PLUS:
    return (ExecReturn){EXEC_OK, left + right};
  case EXPR_MINUS:
    return (ExecReturn){EXEC_OK, left - right};
  case EXPR_TIMES:
    return (ExecReturn){EXEC_OK, left * right};
  case EXPR_DIV:
    if (right == 0) {
      exit_with_error(DIV_BY_ZERO, node->line);
    }
    return (ExecReturn){EXEC_OK, left / right};
  case EXPR_EQUAL:
    return (ExecReturn){EXEC_OK, left == right};
  case EXPR_NEQUAL:
    return (ExecReturn){EXEC_OK, left != right};
  case EXPR_MOD:
    if (right == 0 || (long)left != left || (long)right != right) {
      exit_with_error(MOD_BY_ZERO, node->line);
    }
    return (ExecReturn){EXEC_OK, (long)left % (long)right};
  case EXPR_NEG:
    return (ExecReturn){EXEC_OK, -left};
  case EXPR_LT:
    return (ExecReturn){EXEC_OK, left < right};
  case EXPR_GT:
    return (ExecReturn){EXEC_OK, left > right};
  case EXPR_LE:
    return (ExecReturn){EXEC_OK, left <= right};
  case EXPR_GE:
    return (ExecReturn){EXEC_OK, left >= right};
  case EXPR_AND:
    return (ExecReturn){EXEC_OK, left && right};
  case EXPR_OR:
    return (ExecReturn){EXEC_OK, left || right};
  case EXPR_NOT:
    return (ExecReturn){EXEC_OK, !left};
  case EXPR_PAR:
    return (ExecReturn){EXEC_OK, left};
  default:
    return (ExecReturn){EXEC_OK, 0};
  }
}

static ExecReturn exec_variable_expr(NodeType type, ASTNode *node) {
  ExprNode *expr = node->data;
  char *name = expr->value;

  Var *var = get_var(name);
  double value = get_var_value(name, node->line);

  double d = 0;

  switch (type) {
  case EXPR_INC_PREV:
    d = ++value;
    update_var(DOUBLE, var, &value);
    break;
  case EXPR_INC_POST:
    d = value++;
    update_var(DOUBLE, var, &value);
    break;
  case EXPR_DEC_PREV:
    d = --value;
    update_var(DOUBLE, var, &value);
    break;
  case EXPR_DEC_POST:
    d = value--;
    update_var(DOUBLE, var, &value);
    break;
  case EXPR_VAR:
    d = value;
    break;
  default:
    break;
  }

  return (ExecReturn){EXEC_OK, d};
}

ExecReturn exec_node_list(ListNode *node) {
  ListNode *n = node;
  ExecReturn ret = {EXEC_OK, 0};

  stack_scope();

  while (n != NULL) {
    if (n->node) {
      ret = exec_node(n->node);
      if (ret.status == EXEC_BREAK) {
        printf("[DEBUG] Break na linha %d\n", n->node->line);
        break;
      }
      if (ret.status == EXEC_CONTINUE) {
        printf("[DEBUG] Continue na linha %d\n", n->node->line);
        break;
      }
      if (ret.status == EXEC_FAIL) {
        break;
      }
    }
    n = n->next;
  }

  pop_scope();

  return ret;
}

static int to_bool(double v) { return v != 0.0; }

ExecReturn exec_while_node(ASTNode *node) {
  WhileNode *w = node->data;
  ExecReturn ret;
  while (to_bool(exec_node(w->condition).value)) {
    ret = exec_node(w->body);
    if (ret.status == EXEC_BREAK)
      break;
    if (ret.status == EXEC_CONTINUE)
      continue;
    if (ret.status == EXEC_FAIL)
      return ret;
  }
  return (ExecReturn){EXEC_OK, 0};
}

ExecReturn exec_do_while_node(ASTNode *node) {
  WhileNode *d = node->data;
  ExecReturn ret;
  do {
    ret = exec_node(d->body);
    if (ret.status == EXEC_BREAK)
      break;
    if (ret.status == EXEC_CONTINUE)
      continue;
    if (ret.status == EXEC_FAIL)
      return ret;
  } while (to_bool(exec_node(d->condition).value));
  return (ExecReturn){EXEC_OK, 0};
}

ExecReturn exec_if_node(ASTNode *node) {
  if (!node || node->type != NODE_IF)
    return (ExecReturn){EXEC_FAIL, 0};

  ASTNodeIf *ifn = (ASTNodeIf *)node->data;
  if (!ifn || !ifn->condition)
    return (ExecReturn){EXEC_FAIL, 0};

  ExecReturn condition_result = exec_node(ifn->condition);
  if (condition_result.status != EXEC_OK)
    return condition_result;

  if (condition_result.value) {
    return exec_node(ifn->if_body);
  } else if (ifn->else_body != NULL) {
    return exec_node(ifn->else_body);
  }

  return (ExecReturn){EXEC_OK, 0};
}

ExecReturn exec_for_node(ASTNode *node) {
  if (!node || node->type != NODE_FOR)
    return (ExecReturn){EXEC_FAIL, 0};

  ForNode *f = (ForNode *)node->data;
  if (f->init) {
    ExecReturn ret = exec_node(f->init);
    if (ret.status != EXEC_OK)
      return ret;
  }
  while (1) {
    if (f->condition) {
      ExecReturn cond_ret = exec_node(f->condition);
      if (cond_ret.status != EXEC_OK)
        return cond_ret;
      if (!to_bool(cond_ret.value))
        break;
    }
    if (f->body) {
      ExecReturn body_ret = exec_node(f->body);
      if (body_ret.status == EXEC_BREAK)
        break;
      if (body_ret.status == EXEC_CONTINUE) {
        if (f->step) {
          ExecReturn step_ret = exec_node(f->step);
          if (step_ret.status != EXEC_OK)
            return step_ret;
        }
        continue;
      }
      if (body_ret.status == EXEC_FAIL)
        return body_ret;
    }
    if (f->step) {
      ExecReturn step_ret = exec_node(f->step);
      if (step_ret.status != EXEC_OK)
        return step_ret;
    }
  }
  return (ExecReturn){EXEC_OK, 0};
}

ExecReturn exec_func_node(ASTNode *node) {
  if (node == NULL || node->data == NULL)
    return (ExecReturn){EXEC_FAIL, 0};

  FuncNode *data = node->data;

  double value = run_builtin_func(data->func, data->params, node->line);

  return (ExecReturn){EXEC_OK, value};
}
