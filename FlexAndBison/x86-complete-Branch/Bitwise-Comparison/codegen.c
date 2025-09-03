#include "codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { FUNC, STMT_LIST, VAR_DECL, ASSIGN, IF, WHILE, RETURN, NUMBER, VAR, BINOP, UNARYOP } NodeType;

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
        struct { char* op; struct ASTNode* operand; } unaryop;
    };
};

static int label_id = 0;

// Very basic variable storage on stack (assumes <= 64 vars)
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
    // allocate new slot
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
struct ASTNode* make_unaryop(char* op, struct ASTNode* operand) {
    struct ASTNode* node = new_node(UNARYOP);
    node->unaryop.op = strdup(op);
    node->unaryop.operand = operand;
    return node;
}

void emit_expr(struct ASTNode* expr) {
    switch (expr->type) {
        case NUMBER:
            printf("    mov rax, %d\n", expr->num);
            break;
        case VAR: {
            int offset = get_var_offset(expr->var);
            printf("    mov rax, [rbp%+d]\n", offset);
            break;
        }
        case UNARYOP: {
            emit_expr(expr->unaryop.operand);
            if (strcmp(expr->unaryop.op, "-") == 0) {
                printf("    neg rax\n");
            }
            break;
        }
        case BINOP: {
            emit_expr(expr->binop.left);
            printf("    push rax\n");
            emit_expr(expr->binop.right);
            printf("    pop rbx\n"); // left operand in rbx, right now in rax

            if (strcmp(expr->binop.op, "+") == 0) {
                printf("    add rax, rbx\n");
            } else if (strcmp(expr->binop.op, "-") == 0) {
                printf("    mov rcx, rax\n");
                printf("    mov rax, rbx\n");
                printf("    sub rax, rcx\n");
            } else if (strcmp(expr->binop.op, "*") == 0) {
                printf("    imul rax, rbx\n");
            } else if (strcmp(expr->binop.op, "/") == 0) {
                printf("    cmp rax, 0\n");
                printf("    je .divzero\n");
                printf("    mov rcx, rax\n");
                printf("    mov rax, rbx\n");
                printf("    cqo\n");
                printf("    idiv rcx\n");
            } else if (strcmp(expr->binop.op, "%") == 0) {
                printf("    cmp rax, 0\n");
                printf("    je .divzero\n");
                printf("    mov rcx, rax\n");
                printf("    mov rax, rbx\n");
                printf("    cqo\n");
                printf("    idiv rcx\n");
                printf("    mov rax, rdx\n");
            } else if (strcmp(expr->binop.op, "==") == 0) {
                printf("    cmp rbx, rax\n");
                printf("    sete al\n");
                printf("    movzx rax, al\n");
            } else if (strcmp(expr->binop.op, "!=") == 0) {
                printf("    cmp rbx, rax\n");
                printf("    setne al\n");
                printf("    movzx rax, al\n");
            } else if (strcmp(expr->binop.op, "<") == 0) {
                printf("    cmp rbx, rax\n");
                printf("    setl al\n");
                printf("    movzx rax, al\n");
            } else if (strcmp(expr->binop.op, "<=") == 0) {
                printf("    cmp rbx, rax\n");
                printf("    setle al\n");
                printf("    movzx rax, al\n");
            } else if (strcmp(expr->binop.op, ">") == 0) {
                printf("    cmp rbx, rax\n");
                printf("    setg al\n");
                printf("    movzx rax, al\n");
            } else if (strcmp(expr->binop.op, ">=") == 0) {
                printf("    cmp rbx, rax\n");
                printf("    setge al\n");
                printf("    movzx rax, al\n");
            } else if (strcmp(expr->binop.op, "&") == 0) {
                printf("    and rax, rbx\n");
            } else if (strcmp(expr->binop.op, "|") == 0) {
                printf("    or rax, rbx\n");
            } else if (strcmp(expr->binop.op, "^") == 0) {
                printf("    xor rax, rbx\n");
            } else if (strcmp(expr->binop.op, "<<") == 0) {
                printf("    mov rcx, rax\n");     // shift amount in rcx
                printf("    mov rax, rbx\n");     // value to shift
                printf("    shl rax, cl\n");
            } else if (strcmp(expr->binop.op, ">>") == 0) {
                printf("    mov rcx, rax\n");     // shift amount in rcx
                printf("    mov rax, rbx\n");     // value to shift
                printf("    sar rax, cl\n");      // arithmetic shift
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
            printf("    mov [rbp%+d], rax\n", offset);
            break;
        }
        case ASSIGN: {
            int offset = get_var_offset(stmt->assign.name);
            emit_expr(stmt->assign.value);
            printf("    mov [rbp%+d], rax\n", offset);
            break;
        }
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
        case RETURN:
            emit_expr(stmt->ret.value);
            printf("    mov rdi, rax\n");
            printf("    mov rax, 60\n    syscall\n");
            break;
        default:
            break;
    }
}

void generate_code(struct ASTNode* root) {
    printf("section .text\n");
    printf("global _start\n");
    printf("_start:\n");
    printf("    push rbp\n");
    printf("    mov rbp, rsp\n");
    printf("    sub rsp, 512\n"); // basic stack frame

    emit_stmt(root->func.body);

    // graceful program exit with return 0
    printf("    mov rdi, 0\n");
    printf("    mov rax, 60\n");  // syscall: exit
    printf("    syscall\n");

    // Error handler: division by zero
    printf(".divzero:\n");
    printf("    mov rax, 1\n");               // syscall: write
    printf("    mov rdi, 1\n");               // stdout
    printf("    mov rsi, divzero_msg\n");     // pointer to message
    printf("    mov rdx, divzero_len\n");     // message length
    printf("    syscall\n");
    printf("    mov rdi, 1\n");               // exit(1)
    printf("    mov rax, 60\n");              // syscall: exit
    printf("    syscall\n");

    printf("section .data\n");
    printf("divzero_msg: db \"Division by zero!\", 10\n");
    printf("divzero_len: equ $ - divzero_msg\n");
}

