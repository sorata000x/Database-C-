#ifndef CHILD_TOKENS_H_
#define CHILD_TOKENS_H_

#include "token.h"

class TokenStr : public Token
{
public:
    TokenStr(string entry);
    void calculate(Stack<Token *> &s, Table &t, vector<string> fes);
    string get_data();
    void postfix(Queue<Token *> &out, Stack<Token *> &op);
    int type();

private:
    string _data;
    int _type; // priority: 1
};

//Parenthesis
class LParen : public Token
{
public:
    LParen(string entry);
    void calculate(Stack<Token *> &s, Table &t, vector<string> fes);
    void postfix(Queue<Token *> &out, Stack<Token *> &op);
    string get_data();
    int type();

private:
    string _data;
    int _type; // priority: 2
};
class RParen : public Token
{
public:
    RParen(string entry);
    void calculate(Stack<Token *> &s, Table &t, vector<string> fes);
    void postfix(Queue<Token *> &out, Stack<Token *> &op);
    string get_data();
    int type();

private:
    string _data;
    int _type; // priority: 3
};

//Operates
class Relational : public Token
{
public:
    Relational(string entry);
    void calculate(Stack<Token *> &s, Table &t, vector<string> fes);
    void postfix(Queue<Token *> &out, Stack<Token *> &op);
    string get_data();
    int type();

private:
    string _data;
    int _type; // priority: 5
};
class Logical : public Token
{
public:
    Logical(string entry);
    void calculate(Stack<Token *> &s, Table &t, vector<string> fes);
    void postfix(Queue<Token *> &out, Stack<Token *> &op);
    string get_data();
    int type();

private:
    string _data;
    int _type; // priority: 4
};

class ResultSet : public Token
{
public:
    ResultSet(vector<long> entry);
    void calculate(Stack<Token *> &s, Table &t, vector<string> fes) {} //dummy
    string get_data() { return ""; }                                   //dummy
    vector<long> get_data_set();
    void postfix(Queue<Token *> &out, Stack<Token *> &op) {} //dummy
    int type();

private:
    vector<long> data_list;
    int _type; // priority: 0
};

#endif // CHILD_TOKENS_H_
