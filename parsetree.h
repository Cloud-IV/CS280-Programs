//----------------------------------------------------------------------------------------------------------------------
// Author: Abrar Rouf
// parsetree.h modified from parsetreeSKELETON-HEADER provided by Gerard Ryan
//----------------------------------------------------------------------------------------------------------------------
#ifndef PARSETREE_H_
#define PARSETREE_H_

#include <vector>
#include <map>
#include <sstream>
#include <iostream>
#include "tokens.h"

using namespace std;

// NodeType represents all possible types
enum NodeType {ERRTYPE, INTTYPE, STRTYPE, IDENTYPE, BOOLTYPE};

// a "forward declaration" for a class to hold values
class Value;

class ParseTree {
    int			linenum;
    ParseTree	*left;
    ParseTree	*right;

public:
    explicit ParseTree(int linenum, ParseTree *l = nullptr, ParseTree *r = nullptr)
            : linenum(linenum), left(l), right(r) {}

    virtual ~ParseTree()
    {
        delete left;
        delete right;
    }

    int GetLinenum() const {return linenum;}

    virtual NodeType GetType() const {return ERRTYPE;}

    int leafCount() const   //recursive method that handles counting leaves of tree during traversal
    {
        int lCount = 0;
        if (left != nullptr) lCount += left -> leafCount();
        if (right != nullptr) lCount += right -> leafCount();
        if (left == nullptr && right == nullptr) lCount++;
        return lCount;
    }

    int stringCount(int (ParseTree::*f)())  //recursive method that handles counting encountered strings during traversal
    {                                       //by using a virtual method
        int sCount = 0;
        if (left != nullptr) sCount += left -> stringCount(f);
        if (right != nullptr) sCount += right -> stringCount(f);
        return sCount + (this -> isString());
    }

    int identCount(int (ParseTree::*f)())   //same as above method but for counting encountered identifiers
    {
        int iCount = 0;
        if (left != nullptr) iCount += left -> identCount(f);
        if (right != nullptr) iCount += right -> identCount(f);
        return iCount + (this -> isIdent());
    }

    string identFreq(string (ParseTree::*f)())  //same as above method but for retrieving lexemes of encountered identifiers
    {
        string idents;
        if (left != nullptr) idents += left -> identFreq(f);
        if (right!= nullptr) idents += right -> identFreq(f);
        return idents + (this -> getID());
    }

    virtual int isString() {return 0;}  //returns 0 if node is not a string
    virtual int isIdent() {return 0;}   //returns 0 if node is not an identifier
    virtual string getID() {return "";} //returns empty string if node is not an identifier
    // other methods
};

class StmtList : public ParseTree {

public:
    StmtList(ParseTree *l, ParseTree *r) : ParseTree(0, l, r) {}

};

class IfStatement : public ParseTree {
public:
    IfStatement(int line, ParseTree *ex, ParseTree *stmt) : ParseTree(line, ex, stmt) {}
};

class Assignment : public ParseTree {
public:
    Assignment(int line, ParseTree *lhs, ParseTree *rhs) : ParseTree(line, lhs, rhs) {}
};

class PrintStatement : public ParseTree {
public:
    PrintStatement(int line, ParseTree *e) : ParseTree(line, e) {}
};

class PlusExpr : public ParseTree {
public:
    PlusExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class MinusExpr : public ParseTree {
public:
    MinusExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class TimesExpr : public ParseTree {
public:
    TimesExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class DivideExpr : public ParseTree {
public:
    DivideExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class LogicAndExpr : public ParseTree {
public:
    LogicAndExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class LogicOrExpr : public ParseTree {
public:
    LogicOrExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class EqExpr : public ParseTree {
public:
    EqExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class NEqExpr : public ParseTree {
public:
    NEqExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class LtExpr : public ParseTree {
public:
    LtExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class LEqExpr : public ParseTree {
public:
    LEqExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class GtExpr : public ParseTree {
public:
    GtExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class GEqExpr : public ParseTree {
public:
    GEqExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line,l,r) {}
};

class IConst : public ParseTree {
    int val;

public:
    IConst(int l, int i) : ParseTree(l), val(i) {}
    explicit IConst(Token& t) : ParseTree(t.GetLinenum()) {val = stoi(t.GetLexeme());}

    NodeType GetType() const override {return INTTYPE;}
};

class BoolConst : public ParseTree {
    bool val;

public:
    BoolConst(Token& t, bool val) : ParseTree(t.GetLinenum()), val(val) {}

    NodeType GetType() const override {return BOOLTYPE;}
};

class SConst : public ParseTree {
    string val;

public:
    explicit SConst(Token& t) : ParseTree(t.GetLinenum()) {val = t.GetLexeme();}

    NodeType GetType() const override {return STRTYPE;}

    int isString() override {return 1;}
};

class Ident : public ParseTree {
    string id;

public:
    explicit Ident(Token& t) : ParseTree(t.GetLinenum()), id(t.GetLexeme()) {}

    NodeType GetType() const override {return IDENTYPE;}

    int isIdent() override {return 1;}  //returns 1 for virtual function

    string getID() override {return id  + " ";} //returns lexeme of identifier for virtual function
};

#endif /* PARSETREE_H_ */
