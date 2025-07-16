// codegen.c - Rewritten version
#include "codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARS 64
#define TEMP_BASE_OFFSET -520  // below local variables
int temp_offset = TEMP_BASE_OFFSET;


// Define AST node types
typedef enum {
    FUNC, FUNC_CALL, STMT_LIST, PARAM_LIST, EXPR_LIST,
    VAR_DECL, ASSIGN, IF, WHILE, RETURN,
    NUMBER, VAR, BINOP, UNARYOP
} NodeType;

// Define AST structure
struct ASTNode {
    NodeType type;
    union {
        struct { char* name; struct ASTNode* params; struct ASTNode* body; } func;
        struct { char* name; struct ASTNode* args; } func_call;
        struct { struct ASTNode* list; struct ASTNode* stmt; } stmt_list;
        struct { struct ASTNode* list; struct ASTNode* expr; } expr_list;
        struct { char* name; struct ASTNode* value; } var_decl;
        struct { char* name; struct ASTNode* value; } assign;
        struct { struct ASTNode* cond; struct ASTNode* then_branch; struct ASTNode* else_branch; } if_stmt;
        struct { struct ASTNode* cond; struct ASTNode* body; } while_stmt;
        struct { struct ASTNode* value; } ret;
        int num;
        char* var;
        struct { char* op; struct ASTNode* left; struct ASTNode* right; } binop;
        struct { char* op; struct ASTNode* operand; } unaryop;
    };
};

// Variable table for stack layout
static struct { char* name; int offset; } var_table[64];
static int var_count = 0;

int get_var_offset(const char* name) {
    for (int i = 0; i < var_count; i++)
        if (strcmp(var_table[i].name, name) == 0)
            return var_table[i].offset;
    var_table[var_count].name = strdup(name);
    var_table[var_count].offset = -8 * (var_count + 1);
    return var_table[var_count++].offset;
}

static int label_id = 0;


#define new_node(t) ((struct ASTNode*)calloc(1, sizeof(struct ASTNode))); node->type = t

struct ASTNode* make_function(char *name, struct ASTNode* params, struct ASTNode* body) {
    struct ASTNode* node = (struct ASTNode*)calloc(1, sizeof(struct ASTNode));
    node->type = FUNC;
    node->func.name = name;
    node->func.params = params;
    node->func.body = body;
    return node;
}

struct ASTNode* make_function_call(char* name, struct ASTNode* args) {
    struct ASTNode* node = (struct ASTNode*)calloc(1, sizeof(struct ASTNode));
    node->type = FUNC_CALL;
    node->func_call.name = strdup(name);
    node->func_call.args = args;
    return node;
}

struct ASTNode* make_expr_list(struct ASTNode* list, struct ASTNode* expr) {
    struct ASTNode* node = (struct ASTNode*)calloc(1, sizeof(struct ASTNode));
    node->type = EXPR_LIST;
    node->expr_list.list = list;
    node->expr_list.expr = expr;
    return node;
}

struct ASTNode* make_param_list(struct ASTNode* list, struct ASTNode* param) {
    struct ASTNode* node = (struct ASTNode*)calloc(1, sizeof(struct ASTNode));
    node->type = PARAM_LIST;
    node->stmt_list.list = list;
    node->stmt_list.stmt = param;
    return node;
}

struct ASTNode* make_stmt_list(struct ASTNode* list, struct ASTNode* stmt) {
    struct ASTNode* node = (struct ASTNode*)calloc(1, sizeof(struct ASTNode));
    node->type = STMT_LIST;
    node->stmt_list.list = list;
    node->stmt_list.stmt = stmt;
    return node;
}

struct ASTNode* make_var_decl(char* name, struct ASTNode* value) {
    struct ASTNode* node = (struct ASTNode*)calloc(1, sizeof(struct ASTNode));
    node->type = VAR_DECL;
    node->var_decl.name = name;
    node->var_decl.value = value;
    return node;
}

struct ASTNode* make_assignment(char* name, struct ASTNode* value) {
    struct ASTNode* node = (struct ASTNode*)calloc(1, sizeof(struct ASTNode));
    node->type = ASSIGN;
    node->assign.name = name;
    node->assign.value = value;
    return node;
}

struct ASTNode* make_if(struct ASTNode* cond, struct ASTNode* then_branch, struct ASTNode* else_branch) {
    struct ASTNode* node = (struct ASTNode*)calloc(1, sizeof(struct ASTNode));
    node->type = IF;
    node->if_stmt.cond = cond;
    node->if_stmt.then_branch = then_branch;
    node->if_stmt.else_branch = else_branch;
    return node;
}

struct ASTNode* make_while(struct ASTNode* cond, struct ASTNode* body) {
    struct ASTNode* node = (struct ASTNode*)calloc(1, sizeof(struct ASTNode));
    node->type = WHILE;
    node->while_stmt.cond = cond;
    node->while_stmt.body = body;
    return node;
}

struct ASTNode* make_return(struct ASTNode* value) {
    struct ASTNode* node = (struct ASTNode*)calloc(1, sizeof(struct ASTNode));
    node->type = RETURN;
    node->ret.value = value;
    return node;
}

struct ASTNode* make_number(int value) {
    struct ASTNode* node = (struct ASTNode*)calloc(1, sizeof(struct ASTNode));
    node->type = NUMBER;
    node->num = value;
    return node;
}

struct ASTNode* make_variable(char* name) {
    struct ASTNode* node = (struct ASTNode*)calloc(1, sizeof(struct ASTNode));
    node->type = VAR;
    node->var = name;
    return node;
}

struct ASTNode* make_binop(char* op, struct ASTNode* left, struct ASTNode* right) {
    struct ASTNode* node = (struct ASTNode*)calloc(1, sizeof(struct ASTNode));
    node->type = BINOP;
    node->binop.op = strdup(op);
    node->binop.left = left;
    node->binop.right = right;
    return node;
}

struct ASTNode* make_unaryop(char* op, struct ASTNode* operand) {
    struct ASTNode* node = (struct ASTNode*)calloc(1, sizeof(struct ASTNode));
    node->type = UNARYOP;
    node->unaryop.op = strdup(op);
    node->unaryop.operand = operand;
    return node;
}


// Emit expression assembly
void emit_expr(struct ASTNode* expr) {
    if (!expr) return;
    switch (expr->type) {
        case NUMBER:
            printf("    mov rax, %d\n", expr->num);
            break;
        case VAR:
            printf("    mov rax, [rbp%+d]\n", get_var_offset(expr->var));
            break;
        case UNARYOP:
            emit_expr(expr->unaryop.operand);
            if (strcmp(expr->unaryop.op, "-") == 0) printf("    neg rax\n");
            else if (strcmp(expr->unaryop.op, "~") == 0) printf("    not rax\n");
            else if (strcmp(expr->unaryop.op, "!") == 0) {
                printf("    cmp rax, 0\n    sete al\n    movzx rax, al\n");
            }
            break;
               case BINOP: {
    emit_expr(expr->binop.left);
    printf("    push rax\n");
    emit_expr(expr->binop.right);
    printf("    pop rbx\n"); // rbx = left, rax = right

    if (strcmp(expr->binop.op, "+") == 0) {
        printf("    add rbx, rax\n");
        printf("    mov rax, rbx\n");
    } else if (strcmp(expr->binop.op, "-") == 0) {
        printf("    mov rcx, rax\n");   // rcx = right
        printf("    mov rax, rbx\n");   // rax = left
        printf("    sub rax, rcx\n");   // rax = left - right
    } else if (strcmp(expr->binop.op, "*") == 0) {
        printf("    imul rbx, rax\n");
        printf("    mov rax, rbx\n");
    } else if (strcmp(expr->binop.op, "/") == 0) {
        printf("    cmp rax, 0\n");
        printf("    je .divzero\n");
        printf("    mov rcx, rax\n");   // rcx = right
        printf("    mov rax, rbx\n");   // rax = left
        printf("    cqo\n");
        printf("    idiv rcx\n");
    } else if (strcmp(expr->binop.op, "%%") == 0) {
        printf("    cmp rax, 0\n");
        printf("    je .divzero\n");
        printf("    mov rcx, rax\n");   // rcx = right
        printf("    mov rax, rbx\n");   // rax = left
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
        printf("    and rbx, rax\n");
        printf("    mov rax, rbx\n");
    } else if (strcmp(expr->binop.op, "|") == 0) {
        printf("    or rbx, rax\n");
        printf("    mov rax, rbx\n");
    } else if (strcmp(expr->binop.op, "^") == 0) {
        printf("    xor rbx, rax\n");
        printf("    mov rax, rbx\n");
    } else if (strcmp(expr->binop.op, "<<") == 0) {
        printf("    mov rcx, rax\n");   // rcx = shift amount (right)
        printf("    mov rax, rbx\n");   // rax = value to shift (left)
        printf("    shl rax, cl\n");
    } else if (strcmp(expr->binop.op, ">>") == 0) {
        printf("    mov rcx, rax\n");
        printf("    mov rax, rbx\n");
        printf("    sar rax, cl\n");
    } else if (strcmp(expr->binop.op, "&&") == 0) {
       int lbl_false = label_id++;
       int lbl_end = label_id++;
    
       emit_expr(expr->binop.left);        // result in rax
       printf("    cmp rax, 0\n");
       printf("    je .L%d\n", lbl_false); // if left is 0, result is false
    
       emit_expr(expr->binop.right);       // evaluate right side
       printf("    cmp rax, 0\n");
       printf("    je .L%d\n", lbl_false); // if right is 0, result is false
    
       printf("    mov rax, 1\n");
       printf("    jmp .L%d\n", lbl_end);
    
       printf(".L%d:\n", lbl_false);
       printf("    mov rax, 0\n");
    
       printf(".L%d:\n", lbl_end);
    } else if (strcmp(expr->binop.op, "||") == 0) {
       int lbl_true = label_id++;
       int lbl_end = label_id++;
    
       emit_expr(expr->binop.left);
       printf("    cmp rax, 0\n");
       printf("    jne .L%d\n", lbl_true); // if left is true, skip right
    
       emit_expr(expr->binop.right);
       printf("    cmp rax, 0\n");
       printf("    jne .L%d\n", lbl_true); // if right is true, result is true
    
       printf("    mov rax, 0\n");
       printf("    jmp .L%d\n", lbl_end);
    
       printf(".L%d:\n", lbl_true);
       printf("    mov rax, 1\n");
    
       printf(".L%d:\n", lbl_end);
    }
    break;
        }
       case FUNC_CALL: {
    static const char* regs[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
    struct ASTNode* args[6];
    int n = 0;

    // Gather arguments in reverse order (because of call order semantics)
    for (struct ASTNode* a = expr->func_call.args; a && n < 6; a = a->expr_list.list)
        args[n++] = a->expr_list.expr;

    // Emit expressions for arguments and push them on stack
    for (int i = n - 1; i >= 0; i--) {
        emit_expr(args[i]);
        printf("    push rax\n");
    }

    // Pop into argument registers
    for (int i = 0; i < n; i++) {
        printf("    pop %s\n", regs[i]);
    }

    // Perform the call
    printf("    call %s\n", expr->func_call.name);

    break;
}

        default: break;
    }
}

// Emit statement assembly
int emit_stmt(struct ASTNode* stmt) {
    if (!stmt) return 0;
    switch (stmt->type) {
        case STMT_LIST:
            return emit_stmt(stmt->stmt_list.list) || emit_stmt(stmt->stmt_list.stmt);
        case VAR_DECL:
        case ASSIGN:
            emit_expr(stmt->type == VAR_DECL ? stmt->var_decl.value : stmt->assign.value);
            printf("    mov [rbp%+d], rax\n", get_var_offset(stmt->type == VAR_DECL ? stmt->var_decl.name : stmt->assign.name));
            return 0;
        case IF: {
            int l1 = label_id++, l2 = label_id++;
            emit_expr(stmt->if_stmt.cond);
            printf("    cmp rax, 0\n    je .L%d\n", l1);
            int then_ret = emit_stmt(stmt->if_stmt.then_branch);
            printf("    jmp .L%d\n.L%d:\n", l2, l1);
            int else_ret = emit_stmt(stmt->if_stmt.else_branch);
            printf(".L%d:\n", l2);
            return then_ret && else_ret;
        }
        case WHILE: {
            int l1 = label_id++, l2 = label_id++;
            printf(".L%d:\n", l1);
            emit_expr(stmt->while_stmt.cond);
            printf("    cmp rax, 0\n    je .L%d\n", l2);
            emit_stmt(stmt->while_stmt.body);
            printf("    jmp .L%d\n.L%d:\n", l1, l2);
            return 0;
        }
        case RETURN:
            if (stmt->ret.value) emit_expr(stmt->ret.value);
            else printf("    xor rax, rax\n");
            printf("    leave\n    ret\n");
            return 1;
        default:
            return 0;
    }
}

// Generate full code from AST
void generate_code(struct ASTNode* root) {
     // Reset variable table for this function
    var_count = 0;
    static int initialized = 0;
    int is_main = strcmp(root->func.name, "main") == 0;

    if (!initialized && is_main) {
        initialized = 1;
        printf("section .text\n    global _start\n_start:\n");
        printf("    call main\n    mov rdi, rax\n    mov rax, 60\n    syscall\n");
    }

    printf("%s:\n    push rbp\n    mov rbp, rsp\n    sub rsp, 512\n", root->func.name);

    static const char* param_regs[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
    int i = 0;
    for (struct ASTNode* p = root->func.params; p && i < 6; p = p->stmt_list.list) {
        struct ASTNode* decl = p->stmt_list.stmt;
        printf("    mov [rbp%+d], %s\n", get_var_offset(decl->var_decl.name), param_regs[i++]);
    }

    if (!emit_stmt(root->func.body)) {
        printf("    xor rax, rax\n    leave\n    ret\n");
    }

    if (initialized && is_main) {
        printf(".divzero:\n");
        printf("    mov rax, 1\n    mov rdi, 1\n    mov rsi, divzero_msg\n    mov rdx, divzero_len\n    syscall\n");
        printf("    mov rdi, 1\n    mov rax, 60\n    syscall\n");
        printf("section .data\n    divzero_msg: db \"Division by zero!\\n\"\n    divzero_len: equ $ - divzero_msg\n");
    }
}


