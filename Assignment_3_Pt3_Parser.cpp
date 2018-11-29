//----------------------------------------------------------------------------------------------------------------------
// Author: Abrar Rouf
// Assignment_3_Pt1_Parser.cpp modified from parseSKELETON provided by Gerard Ryan
//----------------------------------------------------------------------------------------------------------------------
#include "parse.h"


// WRAPPER FOR PUSHBACK
namespace Parser
{
    bool pushed_back = false;
    Token pushed_token;

    static Token GetNextToken(istream *in, int *line)
    {
        if( pushed_back )
        {
            pushed_back = false;
            return pushed_token;
        }
        return getNextToken(in, line);
    }
    static void PushBackToken(Token& t)
    {
        if (pushed_back) abort();

        pushed_back = true;
        pushed_token = t;
    }
}

static int error_count = 0;

void
ParseError(int line, string msg)
{
    error_count++;
    cout << line << ": " << msg << endl;
}

ParseTree *Prog(istream *in, int *line)
{
    ParseTree *sl = Slist(in, line);
    if (sl == nullptr) ParseError(*line, "No statements in program");
    if(error_count) return nullptr;
    return sl;
}

// Slist is a Statement followed by a Statement List
ParseTree *Slist(istream *in, int *line)
{
    ParseTree *s = Stmt(in, line);
    if(s == nullptr) return nullptr;
    if (Parser::GetNextToken(in, line) != SC)
    {
        ParseError(*line, "Missing semicolon");
        return nullptr;
    }
    return new StmtList(s, Slist(in,line));
}

ParseTree *Stmt(istream *in, int *line)
{
    ParseTree *s;
    Token t = Parser::GetNextToken(in, line);
    switch (t.GetTokenType())
    {
        case IF:
            s = IfStmt(in, line);
            break;

        case PRINT:
            s = PrintStmt(in, line);
            break;

        case DONE:
            return nullptr;

        case ERR:
            ParseError(*line, "Invalid token");
            return nullptr;

        default:
            // put back the token and then see if it's an Expr
            Parser::PushBackToken(t);
            s = Expr(in, line);
            if (s == nullptr)
            {
                ParseError(*line, "Invalid statement");
                return nullptr;
            }
            break;
    }
    return s;
}

ParseTree *IfStmt(istream *in, int *line)
{
    ParseTree *ex = Expr(in, line); //checks if valid expression follows "if" keyword
    if (ex == nullptr)
    {
        ParseError(*line, "Invalid statement");
        return nullptr;
    }
    Token t = Parser::GetNextToken(in, line); //checks if valid expression is followed by "then" keyword
    if (t.GetTokenType() != THEN)
    {
        ParseError(*line, "If statement does not contain \"then\"");
        return nullptr;
    }
    return new IfStatement(t.GetLinenum(), ex, Stmt(in, line));
}

ParseTree *PrintStmt(istream *in, int *line)
{
    ParseTree *ex = Expr(in, line); //checks if valid expression follows "print" keyword
    if (ex == nullptr)
    {
        ParseError(*line, "No expression after \"print\"");
        return nullptr;
    }
    return new PrintStatement(*line, ex);
}

ParseTree *Expr(istream *in, int *line)
{
    ParseTree *t1 = LogicExpr(in, line);
    if (t1 == nullptr) return nullptr;

    Token t = Parser::GetNextToken(in, line);
    if (t != ASSIGN)
    {
        Parser::PushBackToken(t);
        return t1;
    }

    ParseTree *t2 = Expr(in, line); // right assoc
    if(t2 == nullptr)
    {
        ParseError(*line, "Missing expression after operator");
        return nullptr;
    }
    return new Assignment(t.GetLinenum(), t1, t2);
}

ParseTree *LogicExpr(istream *in, int *line)
{
    ParseTree *t1 = CompareExpr(in, line);  //checks if valid comparison expression exists
    if (t1 == nullptr) return nullptr;
    while (true)
    {
        Token t = Parser::GetNextToken(in, line);

        if (t != LOGICAND && t != LOGICOR)
        {
            Parser::PushBackToken(t);
            return t1;
        }

        ParseTree *t2 = CompareExpr(in, line);
        if (t2 == nullptr)
        {
            ParseError(*line, "Missing expression after logical operator");
            return nullptr;
        }

        if (t == LOGICAND)
            t1 = new LogicAndExpr(t.GetLinenum(), t1, t2);
        else
            t1 = new LogicOrExpr(t.GetLinenum(), t1, t2);
    }
}

ParseTree *CompareExpr(istream *in, int *line)
{
    ParseTree *t1 = AddExpr(in, line);  //checks if valid AddExpr exists
    if (t1 == nullptr) return nullptr;
    while (true)
    {
        Token t = Parser::GetNextToken(in, line);

        if( t != EQ && t != NEQ && t != GT && t != GEQ && t != LT && t != LEQ)
        {
            Parser::PushBackToken(t);
            return t1;
        }

        ParseTree *t2 = AddExpr(in, line);
        if (t2 == nullptr)
        {
            ParseError(*line, "Missing expression after comparison operator");
            return nullptr;
        }

        if (t == EQ)
            t1 = new EqExpr(t.GetLinenum(), t1, t2);
        else if (t == NEQ)
            t1 = new NEqExpr(t.GetLinenum(), t1, t2);
        else if (t == GT)
            t1 = new GtExpr(t.GetLinenum(), t1, t2);
        else if (t == GEQ)
            t1 = new GEqExpr(t.GetLinenum(), t1, t2);
        else if (t == LT)
            t1 = new LtExpr(t.GetLinenum(), t1, t2);
        else t1 = new LEqExpr(t.GetLinenum(), t1, t2);
    }
}

ParseTree *AddExpr(istream *in, int *line)
{
    ParseTree *t1 = MulExpr(in, line);
    if (t1 == nullptr) return nullptr;

    while (true)
    {
        Token t = Parser::GetNextToken(in, line);

        if( t != PLUS && t != MINUS )
        {
            Parser::PushBackToken(t);
            return t1;
        }

        ParseTree *t2 = MulExpr(in, line);
        if (t2 == nullptr)
        {
            ParseError(*line, "Missing expression after operator");
            return nullptr;
        }

        if( t == PLUS )
            t1 = new PlusExpr(t.GetLinenum(), t1, t2);
        else
            t1 = new MinusExpr(t.GetLinenum(), t1, t2);
    }
}

ParseTree *MulExpr(istream *in, int *line)
{
    ParseTree *t1 = Factor(in, line);   //checks if valid factor exists
    if (t1 == nullptr) return nullptr;
    while (true)
    {
        Token t = Parser::GetNextToken(in, line);

        if (t != STAR && t != SLASH)
        {
            Parser::PushBackToken(t);
            return t1;
        }

        ParseTree *t2 = Factor(in, line);
        if (t2 == nullptr)
        {
            ParseError(*line, "Missing factor after operator");
            return nullptr;
        }

        if (t == STAR)
            t1 = new TimesExpr(t.GetLinenum(), t1, t2);
        else
            t1 = new DivideExpr(t.GetLinenum(), t1, t2);
    }
}

ParseTree *Factor(istream *in, int *line)
{
    bool neg = false;
    Token t = Parser::GetNextToken(in, line);

    if (t == MINUS) neg = true;
    else Parser::PushBackToken(t);

    ParseTree *p1 = Primary(in, line);
    if (p1 == nullptr)
    {
        ParseError(*line, "Missing primary");
        return nullptr;
    }

    if (neg)
    {
        // handle as -1 * Primary
        return new TimesExpr(t.GetLinenum(), new IConst(t.GetLinenum(), -1), p1);
    }
    else return p1;
}

ParseTree *Primary(istream *in, int *line)
{
    Token t = Parser::GetNextToken(in, line);
    if (t == IDENT) return new Ident(t);
    else if (t == ICONST) return new IConst(t);
    else if (t == SCONST) return new SConst(t);
    else if (t == TRUE) return new BoolConst(t, true);
    else if (t == FALSE) return new BoolConst(t, false);
    else if (t == LPAREN)
    {
        ParseTree *ex = Expr(in, line); //checks if valid expression follows left parenthesis
        if (ex == nullptr) return nullptr;
        t = Parser::GetNextToken(in, line); //checks if right parenthesis follows valid expression
        if (t != RPAREN)
        {
            ParseError(*line, "No right parenthesis after parenthesized expression");
            return nullptr;
        }
        return ex;
    }
    else return nullptr;
}
