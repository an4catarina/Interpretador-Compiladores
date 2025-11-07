#include "ast_rules.h"
#include "ast.h"
#include "ast_nodes.h"
#include "error.h"
#include "meta.h"
#include "scope.h"
#include "utils.h"
#include "var.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool exec_var_decl(VarNode *node)
{
  char *type = node->type;
  char *name = node->name;

  if (strcmp(type, "int") == 0)
  {
    return add_var(INT, name, NULL);
  }

  else if (strcmp(type, "float") == 0)
  {
    return add_var(FLOAT, name, NULL);
  }

  else if (strcmp(type, "double") == 0)
  {
    return add_var(DOUBLE, name, NULL);
  }

  else if (strcmp(type, "char") == 0)
  {
    return add_var(VAR_CHAR, name, NULL);
  }

  return false;
}

bool exec_var_init(VarNode *node)
{
  char *type = node->type;
  char *name = node->name;
  double value = exec_expr_node(node->value->type, node->value);

  if (strcmp(type, "int") == 0)
  {
    int i = value;
    return add_var(INT, name, &i);
  }

  else if (strcmp(type, "float") == 0)
  {
    float f = value;
    return add_var(FLOAT, name, &f);
  }

  else if (strcmp(type, "double") == 0)
  {
    double d = value;
    return add_var(DOUBLE, name, &d);
  }

  else if (strcmp(type, "char") == 0)
  {
    char c = value;
    return add_var(VAR_CHAR, name, &c);
  }

  return false;
}

bool exec_var_update(VarNode *node)
{
  char *name = node->name;
  double value = exec_expr_node(node->value->type, node->value);

  VarList *l = current_scope->var_list;
  Var *var = get_var(name);

  if (var == NULL)
    return false;

  switch (var->type)
  {
  case INT:
    return update_var(INT, var, &value);
    break;
  case FLOAT:
    return update_var(FLOAT, var, &value);
    break;
  case DOUBLE:
    return update_var(DOUBLE, var, &value);
    break;
  case VAR_CHAR:
    return update_var(VAR_CHAR, var, &value);
    break;
  default:
    return false;
    break;
  }

  return false;
}

double exec_expr_node(NodeType type, ASTNode *node)
{
  double d = 0;
  double l = 0;
  double r = 0;

  ExprNode *expr = node->data;

  if (type == EXPR_NUM || type == EXPR_CHAR)
  {
    double *n = expr->value;
    d = *n;
  }
  else if (type >= EXPR_PLUS && type <= EXPR_PAR)
  {
    l = exec_expr_node(expr->left_expr->type, expr->left_expr);
    if (expr->right_expr != NULL)
      r = exec_expr_node(expr->right_expr->type, expr->right_expr);

    switch (type)
    {
    case EXPR_PLUS:
      d = l + r;
      break;
    case EXPR_MINUS:
      d = l - r;
      break;
    case EXPR_TIMES:
      d = l * r;
      break;
    case EXPR_DIV:
      if (r == 0)
      {
        exit_with_error(DIV_BY_ZERO, node->line);
      }
      else
      {
        d = l / r;
      }
      break;
    case EXPR_EQUAL:
      d = l == r;
      break;
    case EXPR_NEQUAL:
      d = l != r;
      break;
    case EXPR_MOD:
      if (r == 0 || (long)l != l || (long)r != r)
      {
        exit_with_error(MOD_BY_ZERO, node->line);
      }
      else
      {
        d = (long)l % (long)r;
      }
      break;
    case EXPR_NEG:
      d = -l;
      break;
    case EXPR_EQ:
      d = l == r;
      break;
    case EXPR_NE:
      d = l != r;
      break;
    case EXPR_LT:
      d = l < r;
      break;
    case EXPR_GT:
      d = l > r;
      break;
    case EXPR_LE:
      d = l <= r;
      break;
    case EXPR_GE:
      d = l >= r;
      break;
    case EXPR_AND:
      d = l && r;
      break;
    case EXPR_OR:
      d = l || r;
      break;
    case EXPR_NOT:
      d = !l;
      break;
    case EXPR_PAR:
      d = l;
      break;
    default:
      break;
    }
  }
  else
  {
    char *name = expr->value;
    double value = get_var_value(name, node->line);
    Var *var = get_var(name);

    switch (type)
    {
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
    default:
      d = value;
      break;
    }
  }

  return d;
}

double exec_node_list(ListNode *node)
{
  ListNode *n = node;
  double r = 0;

  VarNode *vn;
  ListNode *ln;

  stack_scope();

  while (n != NULL)
  {
    exec_node(n->node);
    n = n->next;
  }

  pop_scope();

  return r;
}

static int to_bool(double v) { return v != 0.0; }

void exec_while_node(ASTNode *node)
{
  WhileNode *w = node->data;
  while (to_bool(exec_node(w->condition)))
  {
    exec_node(w->body);
  }
}

void exec_do_while_node(ASTNode *node)
{
  WhileNode *d = node->data;
  do
  {
    exec_node(d->body);
  } while (to_bool(exec_node(d->condition)));
}

double exec_if_node(ASTNode *node)
{
  if (!node || node->type != IF_STMT)
    return 0;

  ASTNodeIf *ifn = (ASTNodeIf *)node->data;
  if (!ifn || !ifn->condition)
    return 0;

  double condition_result = exec_node(ifn->condition);

  if (condition_result)
  {
    return exec_node(ifn->if_body);
  }
  else if (ifn->else_body != NULL)
  {
    return exec_node(ifn->else_body);
  }

  return 0;
}

void exec_for_node(ASTNode *node)
{
  if (!node || node->type != NODE_FOR)
    return;

  ForNode *f = (ForNode *)node->data;
  if (f->init)
    exec_node(f->init);
  while (1)
  {
    if (f->condition && !to_bool(exec_node(f->condition)))
      break;
    if (f->body)
      exec_node(f->body);
    if (f->step)
      exec_node(f->step);
  }
}
