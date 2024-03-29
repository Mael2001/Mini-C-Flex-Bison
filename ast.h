#include <string>
#include <list>
#include <map>

using namespace std;

class Expr;
class InitDeclarator;
class Declaration;
class Parameter;
class Statement;
typedef list<Expr *> InitializerElementList;
typedef list<InitDeclarator *> InitDeclaratorList;
typedef list<Declaration *> DeclarationList;
typedef list<Parameter *> ParameterList;
typedef list<Statement *> StatementList;
typedef list<Expr *> ArgumentList;

enum StatementKind
{
    WHILE_STATEMENT,
    EXPRESSION_STATEMENT,
    IF_STATEMENT,
    FOR_STATEMENT,
    BLOCK_STATEMENT,
    RETURN_STATEMENT,
    CONTINUE_STATEMENT,
    BREAK_STATEMENT,
    PRINT_STATEMENT,
    FUNCTION_DEFINITION_STATEMENT,
    GLOBAL_DECLARATION_STATEMENT
};

enum Type
{
    INVALID,
    STRING,
    INT,
    FLOAT,
    VOID,
    INT_ARRAY,
    FLOAT_ARRAY,
    BOOL
};

enum UnaryType
{
    INCREMENT,
    DECREMENT,
    NOT
};

class Statement
{
public:
    int line;
    virtual int evaluateSemantic() = 0;
    virtual StatementKind getKind() = 0;
};

class Expr
{
public:
    int line;
    virtual Type getType() = 0;
};

class Initializer
{
public:
    Initializer(InitializerElementList expressions, int line)
    {
        this->expressions = expressions;
        this->line = line;
    }
    InitializerElementList expressions;
    int line;
};

class Declarator
{
public:
    Declarator(string id, Expr *arrayDeclaration, bool isArray, int line)
    {
        this->id = id;
        this->isArray = isArray;
        this->line = line;
        this->arrayDeclaration = arrayDeclaration;
    }
    string id;
    bool isArray;
    int line;
    Expr *arrayDeclaration;
};

class InitDeclarator
{
public:
    InitDeclarator(Declarator *declarator, Initializer *initializer, int line)
    {
        this->declarator = declarator;
        this->initializer = initializer;
        this->line = line;
    }
    Declarator *declarator;
    Initializer *initializer;
    int line;
};

class Declaration
{
public:
    Declaration(int type, InitDeclaratorList declarations, int line)
    {
        this->type = type;
        this->declarations = declarations;
        this->line = line;
    }
    int type;
    InitDeclaratorList declarations;
    int line;
    int evaluateSemantic();
};

class Parameter
{
public:
    Parameter(int type, Declarator *declarator, bool isArray, int line)
    {
        this->type = type;
        this->declarator = declarator;
        this->line = line;
    }
    int type;
    Declarator *declarator;
    bool isArray;
    int line;
};

class WhileStatement : public Statement
{
public:
    WhileStatement(Expr *Expressions, Statement *Statements, int line)
    {
        this->Expressions = Expressions;
        this->Statements = Statements;
        this->line = line;
    }
    Statement *Statements;
    Expr *Expressions;
    int evaluateSemantic();
    StatementKind getKind()
    {
        return WHILE_STATEMENT;
    }
};
class ExpressionStatement : public Statement
{
public:
    ExpressionStatement(Expr *Expressions, int line)
    {
        this->Expressions = Expressions;
        this->line = line;
    }
    Expr *Expressions;
    int evaluateSemantic();
    StatementKind getKind()
    {
        return EXPRESSION_STATEMENT;
    }
};
class IfStatement : public Statement
{
public:
    IfStatement(Expr *Expressions, StatementList Statements, int line)
    {
        this->Expressions = Expressions;
        this->Statements = Statements;
        this->line = line;
    }
    StatementList Statements;
    Expr *Expressions;
    int evaluateSemantic();
    StatementKind getKind()
    {
        return IF_STATEMENT;
    }
};

class PrintStatement : public Statement
{
public:
    PrintStatement(Expr* expr, int line)
    {
        this->expr = expr;
        this->line = line;
    }
    Expr* expr;
    int evaluateSemantic();
    StatementKind getKind()
    {
        return PRINT_STATEMENT;
    }
};

class ReturnStatement : public Statement
{
public:
    ReturnStatement(Expr* expr,int line)
    {
        this->expr = expr;
        this->line = line;
    }
    Expr* expr;
    int evaluateSemantic();
    StatementKind getKind()
    {
        return RETURN_STATEMENT;
    }
};

class ContinueStatement : public Statement
{
public:
    ContinueStatement(int line)
    {
        this->line = line;
    }
    int evaluateSemantic();
    StatementKind getKind()
    {
        return CONTINUE_STATEMENT;
    }
};

class BreakStatement : public Statement
{
public:
    BreakStatement(int line)
    {
        this->line = line;
    }
    int evaluateSemantic();
    StatementKind getKind()
    {
        return BREAK_STATEMENT;
    }
};

class ForStatement : public Statement
{
public:
    ForStatement(Statement *LeftExpression, Statement *RightExpression, Expr *Expression, Statement *Statements, int line)
    {
        this->LeftExpression = LeftExpression;
        this->RightExpression = RightExpression;
        this->Expression = Expression;
        this->Statements = Statements;
        this->line = line;
    }

    Statement *Statements;
    Statement *LeftExpression;
    Statement *RightExpression;
    Expr *Expression;
    int evaluateSemantic();
    StatementKind getKind()
    {
        return FOR_STATEMENT;
    }
};
class BlockStatement : public Statement
{
public:
    BlockStatement(StatementList statements, DeclarationList declarations, int line)
    {
        this->statements = statements;
        this->declarations = declarations;
        this->line = line;
    }
    StatementList statements;
    DeclarationList declarations;
    int line;
    int evaluateSemantic();
    StatementKind getKind()
    {
        return BLOCK_STATEMENT;
    }
};

class GlobalDeclaration : public Statement
{
public:
    GlobalDeclaration(Declaration *declaration)
    {
        this->declaration = declaration;
    }
    Declaration *declaration;
    int evaluateSemantic();
    StatementKind getKind()
    {
        return GLOBAL_DECLARATION_STATEMENT;
    }
};

class MethodDefinition : public Statement
{
public:
    MethodDefinition(int type, string id, ParameterList params, Statement *statement, int line)
    {
        this->type = type;
        this->id = id;
        this->params = params;
        this->statement = statement;
        this->line = line;
    }

    int type;
    string id;
    ParameterList params;
    Statement *statement;
    int line;
    int evaluateSemantic();
    StatementKind getKind()
    {
        return FUNCTION_DEFINITION_STATEMENT;
    }
};

class IntExpr : public Expr
{
public:
    IntExpr(int value, int line)
    {
        this->value = value;
        this->line = line;
    }
    int value;
    Type getType();
};

class FloatExpr : public Expr
{
public:
    FloatExpr(float value, int line)
    {
        this->value = value;
        this->line = line;
    }
    float value;
    Type getType();
};

class BinaryExpr : public Expr
{
public:
    BinaryExpr(Expr *expr1, Expr *expr2, int line)
    {
        this->expr1 = expr1;
        this->expr2 = expr2;
        this->line = line;
    }
    Expr *expr1;
    Expr *expr2;
    int line;
};

#define IMPLEMENT_BINARY_EXPR(name)                                                        \
    class name##Expr : public BinaryExpr                                                   \
    {                                                                                      \
    public:                                                                                \
        name##Expr(Expr *expr1, Expr *expr2, int line) : BinaryExpr(expr1, expr2, line) {} \
        Type getType();                                                                    \
    };

class UnaryExpr : public Expr
{
public:
    UnaryExpr(int type, Expr *expr, int line)
    {
        this->type = type;
        this->expr = expr;
        this->line = line;
    }
    int type;
    Expr *expr;
    int line;
    Type getType();
};

class PostIncrementExpr : public Expr
{
public:
    PostIncrementExpr(Expr *expr, int line)
    {
        this->expr = expr;
        this->line = line;
    }
    Expr *expr;
    int line;
    Type getType();
};

class PostDecrementExpr : public Expr
{
public:
    PostDecrementExpr(Expr *expr, int line)
    {
        this->expr = expr;
        this->line = line;
    }
    Expr *expr;
    int line;
    Type getType();
};

class IdExpr : public Expr
{
public:
    IdExpr(string id, int line)
    {
        this->id = id;
        this->line = line;
    }
    string id;
    int line;
    Type getType();
};

class ArrayExpr : public Expr
{
public:
    ArrayExpr(IdExpr *id, Expr *expr, int line)
    {
        this->id = id;
        this->expr = expr;
        this->line = line;
    }
    IdExpr *id;
    Expr *expr;
    int line;
    Type getType();
};

class MethodInvocationExpr : public Expr
{
public:
    MethodInvocationExpr(IdExpr *id, ArgumentList args, int line)
    {
        this->id = id;
        this->args = args;
        this->line = line;
    }
    IdExpr *id;
    ArgumentList args;
    int line;
    Type getType();
};

class StringExpr : public Expr
{
public:
    StringExpr(string value, int line)
    {
        this->value = value;
        this->line = line;
    }
    string value;
    int line;
    Type getType();
};

IMPLEMENT_BINARY_EXPR(Add);
IMPLEMENT_BINARY_EXPR(Sub);
IMPLEMENT_BINARY_EXPR(Mul);
IMPLEMENT_BINARY_EXPR(Div);
IMPLEMENT_BINARY_EXPR(Eq);
IMPLEMENT_BINARY_EXPR(Neq);
IMPLEMENT_BINARY_EXPR(Gte);
IMPLEMENT_BINARY_EXPR(Lte);
IMPLEMENT_BINARY_EXPR(Gt);
IMPLEMENT_BINARY_EXPR(Lt);
IMPLEMENT_BINARY_EXPR(LogicalAnd);
IMPLEMENT_BINARY_EXPR(LogicalOr);
IMPLEMENT_BINARY_EXPR(Assign);
IMPLEMENT_BINARY_EXPR(PlusAssign);
IMPLEMENT_BINARY_EXPR(MinusAssign);
