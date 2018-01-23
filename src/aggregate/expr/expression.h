#ifndef RS_AGG_EXPRESSION_H_
#define RS_AGG_EXPRESSION_H_
#include <redisearch.h>
#include <value.h>

typedef enum {
  RSExpr_Literal,
  RSExpr_Property,
  RSExpr_Op,
  RSExpr_Function,
} RSExprType;

struct RSExpr;
typedef struct {
  unsigned char op;
  struct RSExpr *left;
  struct RSExpr *right;
} RSExprOp;

typedef struct {
  size_t len;
  struct RSExpr *args[];
} RSArgList;

typedef struct {
  const char *name;
  RSArgList *args;
} RSFunction;

typedef struct RSExpr {
  union {
    RSExprOp op;
    RSValue literal;
    RSFunction func;
    RSKey property;
  };
  RSExprType t;
} RSExpr;

RSArgList *RS_NewArgList(RSExpr *e);
RSExpr *RS_NewStringLiteral(char *str, size_t len);
RSExpr *RS_NewNumberLiteral(double n);
RSExpr *RS_NewOp(unsigned char op, RSExpr *left, RSExpr *right);
RSExpr *RS_NewFunc(char *str, size_t len, RSArgList *args);
RSExpr *RS_NewProp(char *str, size_t len);
void RSExpr_Free(RSExpr *expr);
#endif