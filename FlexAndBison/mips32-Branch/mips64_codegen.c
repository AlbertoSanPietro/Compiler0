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
static int temp_offset = -512;

int get_var_offset(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_table[i].name, name) == 0)
            return var_table[i].offset;
    }
    var_table[var_count].name = strdup(name);
    var_table[var_count].offset = -8 * (var_count + 1);
    return var_table[var_count++].offset;
}

int push_temp() {
    temp_offset -= 8;
    return temp_offset;
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
            printf("    li $a0, %d\n", expr->num);
            break;
        case VAR: {
            int offset = get_var_offset(expr->var);
            printf("    ld $a0, %d($fp)\n", offset);
            break;
        }
        case UNOP: {
            emit_expr(expr->unop.operand);
            if (strcmp(expr->unop.op, "-") == 0) {
                printf("    dneg $a0, $a0\n");
            }
            break;
        }
        case BINOP: {
            emit_expr(expr->binop.left);
            int temp = push_temp();
            printf("    sd $a0, %d($fp)\n", temp); // save left operand
            emit_expr(expr->binop.right);
            printf("    ld $a1, %d($fp)\n", temp); // load left into $a1, right in $a0

            if (strcmp(expr->binop.op, "+") == 0) {
                printf("    daddu $a0, $a1, $a0\n");
            } else if (strcmp(expr->binop.op, "-") == 0) {
                printf("    dsubu $a0, $a1, $a0\n");
            } else if (strcmp(expr->binop.op, "*") == 0) {
                printf("    dmul $a0, $a1, $a0\n");
            } else if (strcmp(expr->binop.op, "/") == 0) {
                printf("    ddiv $a1, $a0\n");
                printf("    mflo $a0\n");
            } else if (strcmp(expr->binop.op, "%") == 0 || strcmp(expr->binop.op, "%%") == 0) {
                printf("    ddiv $a1, $a0\n");
                printf("    mfhi $a0\n");
            } else if (strcmp(expr->binop.op, "<") == 0) {
                printf("    slt $a0, $a1, $a0\n");
            } else if (strcmp(expr->binop.op, ">") == 0) {
                printf("    slt $a0, $a0, $a1\n");
            } else if (strcmp(expr->binop.op, "==") == 0) {
                printf("    seq $a0, $a1, $a0\n");
            } else if (strcmp(expr->binop.op, "!=") == 0) {
                printf("    sne $a0, $a1, $a0\n");
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
            printf("    sd $a0, %d($fp)\n", offset);
            break;
        }
        case ASSIGN: {
            int offset = get_var_offset(stmt->assign.name);
            emit_expr(stmt->assign.value);
            printf("    sd $a0, %d($fp)\n", offset);
            break;
        }
        case IF: {
            int l1 = label_id++, l2 = label_id++;
            emit_expr(stmt->if_stmt.cond);
            printf("    beqz $a0, .L%d\n", l1);
            emit_stmt(stmt->if_stmt.then_branch);
            printf("    b .L%d\n", l2);
            printf(".L%d:\n", l1);
            emit_stmt(stmt->if_stmt.else_branch);
            printf(".L%d:\n", l2);
            break;
        }
        case WHILE: {
            int l1 = label_id++, l2 = label_id++;
            printf(".L%d:\n", l1);
            emit_expr(stmt->while_stmt.cond);
            printf("    beqz $a0, .L%d\n", l2);
            emit_stmt(stmt->while_stmt.body);
            printf("    b .L%d\n", l1);
            printf(".L%d:\n", l2);
            break;
        }
        case RETURN:
            emit_expr(stmt->ret.value);
            printf("    li $v0, 5058\n");
            printf("    syscall\n");
            break;
        default:
            break;
    }
}

void generate_code(struct ASTNode* root) {
    printf(".text\n");
    printf(".globl __start\n");
    printf("__start:\n");
    printf("    daddiu $sp, $sp, -1024\n");
    printf("    move $fp, $sp\n");

    emit_stmt(root->func.body);

    // Print return value in $a0
    printf("    move $a1, $a0\n");
    printf("    li $v0, 1\n");
    printf("    syscall\n");

    printf("    li $v0, 93\n");
    printf("    syscall\n");
}

