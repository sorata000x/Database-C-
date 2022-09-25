#include "child_tokens.h"
#include "../table/table.h"

//TokenStr
TokenStr::TokenStr(string entry) : _data(entry), _type(1) {}
void TokenStr::calculate(Stack<Token *> &s, Table &t, vector<string> fes)
{
    s.push(this);
}
string TokenStr::get_data() { return _data; }
void TokenStr::postfix(Queue<Token *> &out, Stack<Token *> &op) { out.push(this); }
int TokenStr::type() { return _type; }

//Parentheses
//  LParen
LParen::LParen(string entry) : _data(entry), _type(2) {}
void LParen::calculate(Stack<Token *> &s, Table &t, vector<string> fes) {}
void LParen::postfix(Queue<Token *> &out, Stack<Token *> &op) 
{
    op.push(this);
}
string LParen::get_data() { return _data; }
int LParen::type() { return _type; }
//  RParen
RParen::RParen(string entry) : _data(entry), _type(3) {}
void RParen::calculate(Stack<Token *> &s, Table &t, vector<string> fes) {}
void RParen::postfix(Queue<Token *> &out, Stack<Token *> &op)
{
    while (op.top()->type() != 2 && !op.empty())
    {
        out.push(op.pop());
    }
    if (op.top()->type() == 2)
    {
        op.pop();
    }
    else
        cout << "ERROR: parentheses mismatched" << endl;
}
string RParen::get_data() { return _data; }
int RParen::type() { return _type; }

//Operator
//  Relational
Relational::Relational(string entry) : _data(entry), _type(5) {}
void Relational::calculate(Stack<Token *> &s, Table &t, vector<string> fes)
{
    //pop two elements from the stack (expected both be TokenStr)
    //and send them with op to select, get the result set and push it back to the stack
    string first;
    string second;
    first = static_cast<TokenStr *>(s.pop())->get_data();
    second = static_cast<TokenStr *>(s.pop())->get_data();
    t.select(fes, second, _data, first);
    vector<long> vec = t.select_recnos();
    s.push(new ResultSet(vec));
}
void Relational::postfix(Queue<Token *> &out, Stack<Token *> &op)
{
    if (!op.empty())
    {
        while (op.top()->type() == 5)
        {
            out.push(op.pop());
        }
    }
    op.push(this);
}
string Relational::get_data() { return _data; }
int Relational::type() { return _type; }
//  Logic
Logical::Logical(string entry) : _data(entry), _type(4) {}
void Logical::calculate(Stack<Token *> &s, Table &t, vector<string> fes)
{
    //pop two elements from the stack (expected both be ResultSet)
    //perform the and/or here OR see if there is similar func in table
    //after perform the operation, push it back to the stack as a new ResultSet
    vector<long> first = static_cast<ResultSet *>(s.pop())->get_data_set();
    vector<long> second = static_cast<ResultSet *>(s.pop())->get_data_set();
    vector<long> result;
    if (_data == "and")
    {
        result = vector_instersection(first, second);
    }
    else if (_data == "or")
    {
        result = vector_union(first, second);
    }
    s.push(new ResultSet(result));
}
void Logical::postfix(Queue<Token *> &out, Stack<Token *> &op)
{
    while (!op.empty())
    {
        //pop item at the top of stack and push to output queue if
        //item at the top of stack has higher or same precedence then input item
        //NOTE: AND has higher precedence than OR
        if (op.top()->type() > 4 || op.top()->get_data() == "and")
            out.push(op.pop());
        else
            break;
    }
    op.push(this);
}
string Logical::get_data()
{
    return _data;
}
int Logical::type()
{
    return _type;
}

//ResultSet
ResultSet::ResultSet(vector<long> entry) : data_list(entry), _type(0) {}
vector<long> ResultSet::get_data_set() { return data_list; }
int ResultSet::type() { return _type; }