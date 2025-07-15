
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
            return var_table[i].offset;
    }
    var_table[var_count].name = strdup(name);
    var_table[var_count].offset = -4 * (var_count + 1);
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
struct ASTNode* make_unaryop(char* op, struct ASTNode* operand) {
    struct ASTNode* node = new_node(UNOP);
    node->unop.op = strdup(op);
    node->unop.operand = operand;
    return node;
}

void emit_expr(struct ASTNode* expr) {
    switch (expr->type) {
        case NUMBER:
            printf("    li a0, %d\n", expr->num);
            break;
        case VAR: {
            int offset = get_var_offset(expr->var);
            printf("    lw a0, %d(s0)\n", offset);
            break;
        }
        case UNOP: {
            emit_expr(expr->unop.operand);
            if (strcmp(expr->unop.op, "-") == 0)
                printf("    neg a0, a0\n");
            break;
        }
        case BINOP: {
            emit_expr(expr->binop.left);       // result in a0
            printf("    addi sp, sp, -4\n");
            printf("    sw a0, 0(sp)\n");
            emit_expr(expr->binop.right);      // result in a0
            printf("    lw a1, 0(sp)\n");
            printf("    addi sp, sp, 4\n");

            if (strcmp(expr->binop.op, "+") == 0)
                printf("    add a0, a1, a0\n");
            else if (strcmp(expr->binop.op, "-") == 0)
                printf("    sub a0, a1, a0\n");
            else if (strcmp(expr->binop.op, "*") == 0)
                printf("    mul a0, a1, a0\n");
            else if (strcmp(expr->binop.op, "/") == 0)
                printf("    divu a0, a1, a0\n");
            else if (strcmp(expr->binop.op, "%%") == 0 || strcmp(expr->binop.op, "%") == 0)
                printf("    remu a0, a1, a0\n");
            else if (strcmp(expr->binop.op, "==") == 0) {
                printf("    sub a0, a1, a0\n");
                printf("    seqz a0, a0\n");
            } else if (strcmp(expr->binop.op, "<") == 0)
                printf("    sltu a0, a1, a0\n");
            else if (strcmp(expr->binop.op, ">") == 0)
                printf("    sltu a0, a0, a1\n");
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
            printf("    sw a0, %d(s0)\n", offset);
            break;
        }
        case ASSIGN: {
            int offset = get_var_offset(stmt->assign.name);
            emit_expr(stmt->assign.value);
            printf("    sw a0, %d(s0)\n", offset);
            break;
        }
        case IF: {
            int l1 = label_id++, l2 = label_id++;
            emit_expr(stmt->if_stmt.cond);
            printf("    beqz a0, .L%d\n", l1);
            emit_stmt(stmt->if_stmt.then_branch);
            printf("    j .L%d\n", l2);
            printf(".L%d:\n", l1);
            emit_stmt(stmt->if_stmt.else_branch);
            printf(".L%d:\n", l2);
            break;
        }
        case WHILE: {
            int l1 = label_id++, l2 = label_id++;
            printf(".L%d:\n", l1);
            emit_expr(stmt->while_stmt.cond);
            printf("    beqz a0, .L%d\n", l2);
            emit_stmt(stmt->while_stmt.body);
            printf("    j .L%d\n", l1);
            printf(".L%d:\n", l2);
            break;
        }
        case RETURN:
            emit_expr(stmt->ret.value);
            printf("    li a7, 93\n");
            printf("    ecall\n");
            break;
        default:
            break;
    }
}

void generate_code(struct ASTNode* root) {
    printf(".text\n");
    printf(".global _start\n");
    printf("_start:\n");

    // Prologue
    printf("    addi sp, sp, -8\n");
    printf("    sw ra, 4(sp)\n");
    printf("    sw s0, 0(sp)\n");
    printf("    mv s0, sp\n");
    printf("    addi sp, sp, -512\n");

    emit_stmt(root->func.body);

    // Optional fallback exit
    /*
    printf("    li a0, 0\n");
    printf("    li a7, 93\n");
    printf("    ecall\n");
    */

    printf(".section .data\n");
    printf("divzero_msg: .asciz \"Division by zero!\\n\"\n");
}

