#include "codegen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*  
typedef enum { FUNC, STMT_LIST, VAR_DECL, ASSIGN, IF, WHILE, RETURN, NUMBER, VAR, BINOP, UNARYOP, PARAM_LIST, FUNC_CALL, EXPR_LIST } NodeType;

struct ASTNode {
    NodeType type;
    union {
        struct {
            char* name;
            struct ASTNode* params;
            struct ASTNode* body;
        } func;

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
*/ 

typedef enum {
    FUNC,         // Function definition
    FUNC_CALL,    // Function call
    STMT_LIST,    // Compound statements
    PARAM_LIST,   // Function parameters
    EXPR_LIST,    // Function arguments (comma-separated expressions)
    VAR_DECL,     // Variable declaration
    ASSIGN,       // Assignment
    IF,           // If-else
    WHILE,        // While loop
    RETURN,       // Return statement
    NUMBER,       // Integer literal
    VAR,          // Variable reference
    BINOP,        // Binary operation
    UNARYOP       // Unary operation
} NodeType;

struct ASTNode {
    NodeType type;

    union {
        // FUNC
        struct {
            char* name;
            struct ASTNode* params; // PARAM_LIST
            struct ASTNode* body;   // STMT_LIST
        } func;

        // FUNC_CALL
        struct {
            char* name;
            struct ASTNode* args;   // EXPR_LIST
        } func_call;

        // STMT_LIST and PARAM_LIST
        struct {
            struct ASTNode* list;
            struct ASTNode* stmt;
        } stmt_list;

        // EXPR_LIST
        struct {
            struct ASTNode* list;
            struct ASTNode* expr;
        } expr_list;

        // VAR_DECL
        struct {
            char* name;
            struct ASTNode* value;
        } var_decl;

        // ASSIGN
        struct {
            char* name;
            struct ASTNode* value;
        } assign;

        // IF
        struct {
            struct ASTNode* cond;
            struct ASTNode* then_branch;
            struct ASTNode* else_branch;
        } if_stmt;

        // WHILE
        struct {
            struct ASTNode* cond;
            struct ASTNode* body;
        } while_stmt;

        // RETURN
        struct {
            struct ASTNode* value;
        } ret;

        // NUMBER
        int num;

        // VAR
        char* var;

        // BINOP
        struct {
            char* op;
            struct ASTNode* left;
            struct ASTNode* right;
        } binop;

        // UNARYOP
        struct {
            char* op;
            struct ASTNode* operand;
        } unaryop;
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

struct ASTNode* make_function(char *name, struct ASTNode* params, struct ASTNode* body) {
    struct ASTNode* node = new_node(FUNC);
    node->func.name = name;
    node->func.params = params;
    node->func.body = body;
    return node;
}

struct ASTNode* make_function_call(char* name, struct ASTNode* args) {
    struct ASTNode* node = new_node(FUNC_CALL);
    node->func_call.name = strdup(name);
    node->func_call.args = args;
    return node;
}

struct ASTNode* make_expr_list(struct ASTNode* list, struct ASTNode* expr) {
    struct ASTNode* node = new_node(EXPR_LIST);
    node->expr_list.list = list;
    node->expr_list.expr = expr;
    return node;
}


struct ASTNode* make_param_list(struct ASTNode* list, struct ASTNode* param) {
    struct ASTNode* node = new_node(PARAM_LIST);
    node->stmt_list.list = list;
    node->stmt_list.stmt = param;
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
            } else if (strcmp(expr->unaryop.op, "~")== 0) {
                printf("    not rax\n");
            } else if (strcmp(expr->unaryop.op, "!") == 0) {
                printf("    cmp rax, 0\n");
                printf("    sete al\n");
                printf("    movzx rax, al\n");
            }
            break;
        }
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
        default:
            break;
    }
}
int emit_stmt(struct ASTNode* stmt) {
    if (!stmt) return 0;

    switch (stmt->type) {
        case STMT_LIST: {
            int r1 = emit_stmt(stmt->stmt_list.list);
            int r2 = emit_stmt(stmt->stmt_list.stmt);
            return r1 || r2;
        }
        case VAR_DECL: {
            int offset = get_var_offset(stmt->var_decl.name);
            emit_expr(stmt->var_decl.value);
            printf("    mov [rbp%+d], rax\n", offset);
            return 0;
        }
        case ASSIGN: {
            int offset = get_var_offset(stmt->assign.name);
            emit_expr(stmt->assign.value);
            printf("    mov [rbp%+d], rax\n", offset);
            return 0;
        }
        case IF: {
            int l1 = label_id++, l2 = label_id++;
            emit_expr(stmt->if_stmt.cond);
            printf("    cmp rax, 0\n    je .L%d\n", l1);
            int then_has_ret = emit_stmt(stmt->if_stmt.then_branch);
            printf("    jmp .L%d\n.L%d:\n", l2, l1);
            int else_has_ret = emit_stmt(stmt->if_stmt.else_branch);
            printf(".L%d:\n", l2);
            return then_has_ret && else_has_ret;  // both branches must return
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
            if (stmt->ret.value)
                emit_expr(stmt->ret.value);  // result in rax
            else
                printf("    mov rax, 0\n");  // default return value
            printf("    leave\n");
            printf("    ret\n");
            return 1;
        default:
            return 0;
    }
}


void generate_code(struct ASTNode* root) {
    static int emitted_runtime = 0; // Prevents duplicate _start and divzero code

    int is_main = strcmp(root->func.name, "main") == 0;

    // Emit _start only once, and only for main
    if (!emitted_runtime && is_main) {
        emitted_runtime = 1;

        // Text section and program entry point
        printf("section .text\n");
        printf("global _start\n");
        printf("_start:\n");
        printf("    call main\n");         // Call main()
        printf("    mov rdi, rax\n");      // Move return value from main into rdi
        printf("    mov rax, 60\n");       // syscall: exit
        printf("    syscall\n");
    }

    // Emit function label
    printf("%s:\n", root->func.name);
    printf("    push rbp\n");
    printf("    mov rbp, rsp\n");
    printf("    sub rsp, 512\n"); // Simple stack frame

    // Load parameters into local stack slots
    static const char* param_regs[] = { "rdi", "rsi", "rdx", "rcx", "r8", "r9" };
    int param_index = 0;

    struct ASTNode* param = root->func.params;
    while (param && param_index < 6) {
        struct ASTNode* var_decl = param->stmt_list.stmt;
        int offset = get_var_offset(var_decl->var_decl.name);
        printf("    mov [rbp%+d], %s\n", offset, param_regs[param_index++]);
        param = param->stmt_list.list;
    }

    // Emit function body and check if a return was encountered
    int has_return = emit_stmt(root->func.body);

    // Emit default epilogue only if no explicit return was present
    if (!has_return) {
        printf("    mov rax, 0\n");  // Default return value
        printf("    leave\n");
        printf("    ret\n");
    }

    // Emit divzero handler and data section (only once, after main)
    if (emitted_runtime == 1 && is_main) {
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

        emitted_runtime = 2; // mark runtime as fully emitted
    }
}

