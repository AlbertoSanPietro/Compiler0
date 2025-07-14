#include "codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { FUNC, STMT_LIST, VAR_DECL, ASSIGN, IF, WHILE, RETURN, NUMBER, VAR, BINOP, UNOP } NodeType;

struct ASTNode {
    NodeType type;
    union {
        struct { struct ASTNode* body; } func;
        struct { struct ASTNode* list, *stmt; } stmt_list;
        struct { char* name; struct ASTNode* value; } var_decl;
        struct { char* name; struct ASTNode* value; } assign;
        struct { struct ASTNode* cond, *then_branch, *else_branch; } if_stmt;
        struct { struct ASTNode* cond, *body; } while_stmt;
        struct { struct ASTNode* value; } ret;
        int num;
        char* var;
        struct { char* op; struct ASTNode* left, *right; } binop;
        struct { char* op; struct ASTNode* operand; } unop;
    };
};

static int label_id = 0;

static struct {
    char* name;
    int offset;
} var_table[64];
static int var_count = 0;

int get_var_offset(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_table[i].name, name) == 0)
            return i;
    }
    var_table[var_count].name = strdup(name);
    var_table[var_count].offset = var_count;
    return var_count++;
}

#define new_node(t) ((struct ASTNode*)calloc(1, sizeof(struct ASTNode))); node->type = t

struct ASTNode* make_function(struct ASTNode* body) {
    struct ASTNode* node = new_node(FUNC);
    node->func.body = body;
    return node;
}
struct ASTNode* make_stmt_list(struct ASTNode* list, struct ASTNode* stmt) {
    struct ASTNode* node = new_node(STMT_LIST);
    node->stmt_list.list = list;
    node->stmt_list.stmt = stmt;
    return node;
}
struct ASTNode* make_var_decl(char* name, struct ASTNode* value) {
    struct ASTNode* node = new_node(VAR_DECL);
    node->var_decl.name = name;
    node->var_decl.value = value;
    return node;
}
struct ASTNode* make_assignment(char* name, struct ASTNode* value) {
    struct ASTNode* node = new_node(ASSIGN);
    node->assign.name = name;
    node->assign.value = value;
    return node;
}
struct ASTNode* make_if(struct ASTNode* cond, struct ASTNode* then_branch, struct ASTNode* else_branch) {
    struct ASTNode* node = new_node(IF);
    node->if_stmt.cond = cond;
    node->if_stmt.then_branch = then_branch;
    node->if_stmt.else_branch = else_branch;
    return node;
}
struct ASTNode* make_while(struct ASTNode* cond, struct ASTNode* body) {
    struct ASTNode* node = new_node(WHILE);
    node->while_stmt.cond = cond;
    node->while_stmt.body = body;
    return node;
}
struct ASTNode* make_return(struct ASTNode* value) {
    struct ASTNode* node = new_node(RETURN);
    node->ret.value = value;
    return node;
}
struct ASTNode* make_number(int value) {
    struct ASTNode* node = new_node(NUMBER);
    node->num = value;
    return node;
}
struct ASTNode* make_variable(char* name) {
    struct ASTNode* node = new_node(VAR);
    node->var = name;
    return node;
}
struct ASTNode* make_binop(char* op, struct ASTNode* left, struct ASTNode* right) {
    struct ASTNode* node = new_node(BINOP);
    node->binop.op = strdup(op);
    node->binop.left = left;
    node->binop.right = right;
    return node;
}
struct ASTNode* make_unaryop(char* op, struct ASTNode* operand) {
    struct ASTNode* node = new_node(UNOP);
    node->unop.op = strdup(op);
    node->unop.operand = operand;
    return node;
}

void emit_expr(struct ASTNode* expr) {
    switch (expr->type) {
        case NUMBER:
            printf("    AND R0, R0, #0\n    ADD R0, R0, #%d\n", expr->num);
            break;
        case VAR: {
            int offset = get_var_offset(expr->var);
            printf("    LD R0, VAR%d\n", offset);
            break;
        }
        case UNOP: {
            emit_expr(expr->unop.operand);
            if (strcmp(expr->unop.op, "-") == 0) {
                printf("    NOT R0, R0\n    ADD R0, R0, #1\n");
            }
            break;
        }
        case BINOP: {
            emit_expr(expr->binop.left);
            printf("    STR R0, TMP\n");
            emit_expr(expr->binop.right);
            printf("    LDR R1, TMP\n");
            if (strcmp(expr->binop.op, "+") == 0) {
                printf("    ADD R0, R1, R0\n");
            } else if (strcmp(expr->binop.op, "-") == 0) {
                printf("    NOT R0, R0\n    ADD R0, R0, #1\n    ADD R0, R1, R0\n");
            } else if (strcmp(expr->binop.op, "%") == 0 || strcmp(expr->binop.op, "%%") == 0) {
                int loop = label_id++, end = label_id++;
                printf("    STR R0, MODDIV\n");
                printf("    STR R1, MODSRC\n");
                printf("MODLOOP%d:\n", loop);
                printf("    LDR R0, MODSRC\n");
                printf("    LDR R1, MODDIV\n");
                printf("    NOT R1, R1\n");
                printf("    ADD R1, R1, #1\n");
                printf("    ADD R2, R0, R1\n");
                printf("    BRn MODEND%d\n", end);
                printf("    STR R2, MODSRC\n");
                printf("    BR MODLOOP%d\n", loop);
                printf("MODEND%d:\n", end);
                printf("    LDR R0, MODSRC\n");
                label_id++;
            } else if (strcmp(expr->binop.op, "==") == 0) {
                printf("    NOT R2, R0\n    ADD R2, R2, #1\n    ADD R2, R2, R1\n    BRz TRUE%d\n    AND R0, R0, #0\n    BR DONE%d\nTRUE%d:\n    AND R0, R0, #0\n    ADD R0, R0, #1\nDONE%d:\n", label_id, label_id, label_id, label_id);
                label_id++;
            } else if (strcmp(expr->binop.op, "<") == 0) {
                printf("    NOT R0, R0\n    ADD R0, R0, #1\n    ADD R2, R1, R0\n    BRn TRUE%d\n    AND R0, R0, #0\n    BR DONE%d\nTRUE%d:\n    AND R0, R0, #0\n    ADD R0, R0, #1\nDONE%d:\n", label_id, label_id, label_id, label_id);
                label_id++;
            } else if (strcmp(expr->binop.op, ">") == 0) {
                printf("    NOT R1, R1\n    ADD R1, R1, #1\n    ADD R2, R0, R1\n    BRn TRUE%d\n    AND R0, R0, #0\n    BR DONE%d\nTRUE%d:\n    AND R0, R0, #0\n    ADD R0, R0, #1\nDONE%d:\n", label_id, label_id, label_id, label_id);
                label_id++;
            }
            break;
        }
        default:
            break;
    }
}

void emit_stmt(struct ASTNode* stmt) {
    if (!stmt) return;
    switch (stmt->type) {
        case STMT_LIST:
            emit_stmt(stmt->stmt_list.list);
            emit_stmt(stmt->stmt_list.stmt);
            break;
        case VAR_DECL: {
            int offset = get_var_offset(stmt->var_decl.name);
            emit_expr(stmt->var_decl.value);
            printf("    ST R0, VAR%d\n", offset);
            break;
        }
        case ASSIGN: {
            int offset = get_var_offset(stmt->assign.name);
            emit_expr(stmt->assign.value);
            printf("    ST R0, VAR%d\n", offset);
            break;
        }
        case IF: {
            int l1 = label_id++, l2 = label_id++;
            emit_expr(stmt->if_stmt.cond);
            printf("    BRz L%d\n", l1);
            emit_stmt(stmt->if_stmt.then_branch);
            printf("    BR L%d\nL%d:\n", l2, l1);
            emit_stmt(stmt->if_stmt.else_branch);
            printf("L%d:\n", l2);
            break;
        }
        case WHILE: {
            int l1 = label_id++, l2 = label_id++;
            printf("L%d:\n", l1);
            emit_expr(stmt->while_stmt.cond);
            printf("    BRz L%d\n", l2);
            emit_stmt(stmt->while_stmt.body);
            printf("    BR L%d\nL%d:\n", l1, l2);
            break;
        }
        case RETURN:
            emit_expr(stmt->ret.value);
            printf("    HALT\n");
            break;
        default:
            break;
    }
}

void generate_code(struct ASTNode* root) {
    printf(".ORIG x3000\n");
    emit_stmt(root->func.body);
    printf("    HALT\n");

    for (int i = 0; i < var_count; i++) {
        printf("VAR%d .FILL #0\n", i);
    }
    printf("TMP .BLKW 1\n");
    printf("MODSRC .BLKW 1\n");
    printf("MODDIV .BLKW 1\n");
    printf(".END\n");
}

