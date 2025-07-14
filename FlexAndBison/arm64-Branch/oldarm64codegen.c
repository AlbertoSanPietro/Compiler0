#include "codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { FUNC, STMT_LIST, VAR_DECL, ASSIGN, IF, WHILE, RETURN, NUMBER, VAR, BINOP } NodeType;

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
            return var_table[i].offset;
    }
    var_table[var_count].name = strdup(name);
    var_table[var_count].offset = -8 * (var_count + 1);
    return var_table[var_count++].offset;
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

void emit_expr(struct ASTNode* expr) {
    switch (expr->type) {
        case NUMBER:
            printf("    mov x0, #%d\n", expr->num);
            break;
        case VAR: {
            int offset = get_var_offset(expr->var);
            printf("    ldr x0, [x29, #%d]\n", offset);
            break;
        }
       case BINOP: {
    emit_expr(expr->binop.left);   // x0 = left
    printf("    str x0, [sp, #-16]!\n");
    emit_expr(expr->binop.right);  // x0 = right
    printf("    ldr x1, [sp], #16\n");  // x1 = left (restored)

    if (strcmp(expr->binop.op, "+") == 0) {
        printf("    add x0, x1, x0\n");
    } else if (strcmp(expr->binop.op, "-") == 0) {
        printf("    sub x0, x1, x0\n");
    } else if (strcmp(expr->binop.op, "*") == 0) {
        printf("    mul x0, x1, x0\n");
    } else if (strcmp(expr->binop.op, "/") == 0) {
        printf("    udiv x0, x1, x0\n");
    } else if (strcmp(expr->binop.op, "%%") == 0 || strcmp(expr->binop.op, "%") == 0) {
        printf("    udiv x2, x1, x0\n");       // x2 = x1 / x0
        printf("    msub x0, x2, x0, x1\n");   // x0 = x1 - (x2 * x0)
    } else if (strcmp(expr->binop.op, "==") == 0) {
        printf("    cmp x1, x0\n");
        printf("    cset x0, eq\n");
    } else if (strcmp(expr->binop.op, "<") == 0) {
        printf("    cmp x1, x0\n");
        printf("    cset x0, lt\n");
    } else if (strcmp(expr->binop.op, ">") == 0) {
        printf("    cmp x1, x0\n");
        printf("    cset x0, gt\n");
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
            printf("    str x0, [x29, #%d]\n", offset);
            break;
        }
        case ASSIGN: {
            int offset = get_var_offset(stmt->assign.name);
            emit_expr(stmt->assign.value);
            printf("    str x0, [x29, #%d]\n", offset);
            break;
        }
        case IF: {
            int l1 = label_id++, l2 = label_id++;
            emit_expr(stmt->if_stmt.cond);
            printf("    cbz x0, .L%d\n", l1);
            emit_stmt(stmt->if_stmt.then_branch);
            printf("    b .L%d\n.L%d:\n", l2, l1);
            emit_stmt(stmt->if_stmt.else_branch);
            printf(".L%d:\n", l2);
            break;
        }
        case WHILE: {
            int l1 = label_id++, l2 = label_id++;
            printf(".L%d:\n", l1);
            emit_expr(stmt->while_stmt.cond);
            printf("    cbz x0, .L%d\n", l2);
            emit_stmt(stmt->while_stmt.body);
            printf("    b .L%d\n.L%d:\n", l1, l2);
            break;
        }
        case RETURN:
            emit_expr(stmt->ret.value);
            printf("    mov x8, #93\n");
            printf("    svc #0\n");
            break;
        default:
            break;
    }
}

void generate_code(struct ASTNode* root) {
    printf(".text\n");
    printf(".global _start\n");
    printf("_start:\n");
    printf("    stp x29, x30, [sp, #-16]!\n");
    printf("    mov x29, sp\n");
    printf("    sub sp, sp, #512\n");

    emit_stmt(root->func.body);

   /*
    printf("    mov x0, #0\n");
    printf("    mov x8, #93\n");
    printf("    svc #0\n");
    */

    printf(".section .data\n");
    printf("divzero_msg: .asciz \"Division by zero!\\n\"\n");
}
