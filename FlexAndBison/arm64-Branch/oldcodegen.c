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
            printf("\tmov x0, #%d\n", expr->num);
            break;
        case VAR: {
            int offset = get_var_offset(expr->var);
            printf("\tldr x0, [x29, #%d]\n", offset);
            break;
        }
        case BINOP: {
            emit_expr(expr->binop.left);
            printf("\tstr x0, [sp, #-16]!\n");
            emit_expr(expr->binop.right);
            printf("\tldr x1, [sp], #16\n");

            if (strcmp(expr->binop.op, "+") == 0)
                printf("\tadd x0, x1, x0\n");
            else if (strcmp(expr->binop.op, "-") == 0)
                printf("\tsub x0, x1, x0\n");
            else if (strcmp(expr->binop.op, "%") == 0) {
                printf("\tmov x2, x1\n");
                printf("\tmov x1, x0\n");
                printf("\tbl __aeabi_idivmod\n");
                printf("\tmov x0, x1\n"); // remainder is in x1
            }
            break;
        }
        default:
            break;
    }
}

void emit_stmt(struct ASTNode* stmt);

void emit_stmt_list(struct ASTNode* node) {
    if (!node) return;
    emit_stmt_list(node->stmt_list.list);
    emit_stmt(node->stmt_list.stmt);
}

void emit_stmt(struct ASTNode* stmt) {
    switch (stmt->type) {
        case VAR_DECL:
        case ASSIGN: {
            emit_expr(stmt->var_decl.value);
            int offset = get_var_offset(stmt->var_decl.name);
            printf("\tstr x0, [x29, #%d]\n", offset);
            break;
        }
        case IF: {
            int id = label_id++;
            emit_expr(stmt->if_stmt.cond);
            printf("\tcmp x0, #0\n");
            printf("\tbeq .Lelse%d\n", id);
            emit_stmt(stmt->if_stmt.then_branch);
            printf("\tb .Lendif%d\n", id);
            printf(".Lelse%d:\n", id);
            if (stmt->if_stmt.else_branch)
                emit_stmt(stmt->if_stmt.else_branch);
            printf(".Lendif%d:\n", id);
            break;
        }
        case WHILE: {
            int id = label_id++;
            printf(".Lbegin%d:\n", id);
            emit_expr(stmt->while_stmt.cond);
            printf("\tcmp x0, #0\n");
            printf("\tbeq .Lend%d\n", id);
            emit_stmt(stmt->while_stmt.body);
            printf("\tb .Lbegin%d\n", id);
            printf(".Lend%d:\n", id);
            break;
        }
        case RETURN:
            emit_expr(stmt->ret.value);
            break;
        default:
            break;
    }
}

void emit_function(struct ASTNode* node) {
    printf("\t.text\n");
    printf("\t.globl _start\n");
    printf("_start:\n");
    printf("\tstp x29, x30, [sp, #-16]!\n");
    printf("\tmov x29, sp\n");
    printf("\tsub sp, sp, #512\n");
    emit_stmt_list(node->func.body);
    printf("\tmov x8, #93\n");
    printf("\tsvc #0\n");
}

void generate_code(struct ASTNode* node) {
    emit_function(node);
}
