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
static int stack_offset = 0;

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
    if (expr->type == NUMBER) {
        printf("    mov rax, %d\n", expr->num);
    } else if (expr->type == BINOP) {
        emit_expr(expr->binop.left);
        printf("    push rax\n");
        emit_expr(expr->binop.right);
        printf("    pop rbx\n");

        if (strcmp(expr->binop.op, "+") == 0) printf("    add rax, rbx\n");
        else if (strcmp(expr->binop.op, "-") == 0) printf("    sub rbx, rax\n    mov rax, rbx\n");
        else if (strcmp(expr->binop.op, "*") == 0) printf("    imul rax, rbx\n");
        else if (strcmp(expr->binop.op, "/") == 0) {
            printf("    mov rdx, 0\n    xchg rax, rbx\n    div rbx\n");
        } else if (strcmp(expr->binop.op, "%") == 0) {
            printf("    mov rdx, 0\n    xchg rax, rbx\n    div rbx\n    mov rax, rdx\n");
        } else if (strcmp(expr->binop.op, "==") == 0) {
            printf("    cmp rbx, rax\n    sete al\n    movzx rax, al\n");
        }
    }
}

void emit_stmt(struct ASTNode* stmt) {
    if (!stmt) return;
    switch (stmt->type) {
        case RETURN:
            emit_expr(stmt->ret.value);
            printf("    mov rdi, rax\n");
            printf("    mov rax, 60\n    syscall\n");  // exit syscall
            break;
        case STMT_LIST:
            emit_stmt(stmt->stmt_list.list);
            emit_stmt(stmt->stmt_list.stmt);
            break;
        case IF: {
            int l1 = label_id++, l2 = label_id++;
            emit_expr(stmt->if_stmt.cond);
            printf("    cmp rax, 0\n    je .L%d\n", l1);
            emit_stmt(stmt->if_stmt.then_branch);
            printf("    jmp .L%d\n.L%d:\n", l2, l1);
            emit_stmt(stmt->if_stmt.else_branch);
            printf(".L%d:\n", l2);
            break;
        }
        case WHILE: {
            int l1 = label_id++, l2 = label_id++;
            printf(".L%d:\n", l1);
            emit_expr(stmt->while_stmt.cond);
            printf("    cmp rax, 0\n    je .L%d\n", l2);
            emit_stmt(stmt->while_stmt.body);
            printf("    jmp .L%d\n.L%d:\n", l1, l2);
            break;
        }
        default: break;
    }
}

void generate_code(struct ASTNode* root) {
    printf("section .text\n");
    printf("global _start\n");
    printf("_start:\n");
    emit_stmt(root->func.body);
}

