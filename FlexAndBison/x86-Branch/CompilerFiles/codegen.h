#ifndef CODEGEN_H
#define CODEGEN_H

struct ASTNode;

struct ASTNode* make_function(struct ASTNode* body);
struct ASTNode* make_stmt_list(struct ASTNode* list, struct ASTNode* stmt);
struct ASTNode* make_var_decl(char* name, struct ASTNode* value);
struct ASTNode* make_assignment(char* name, struct ASTNode* value);
struct ASTNode* make_if(struct ASTNode* cond, struct ASTNode* then_branch, struct ASTNode* else_branch);
struct ASTNode* make_while(struct ASTNode* cond, struct ASTNode* body);
struct ASTNode* make_return(struct ASTNode* value);
struct ASTNode* make_number(int value);
struct ASTNode* make_variable(char* name);
struct ASTNode* make_binop(char* op, struct ASTNode* left, struct ASTNode* right);
struct ASTNode* make_unaryop(char* op, struct ASTNode* operand); 
void generate_code(struct ASTNode* root);

#endif

