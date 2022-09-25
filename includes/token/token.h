#ifndef TOKEN_H_
#define TOKEN_H_

#include <iostream>
#include <vector>
#include "../stack/MyStack.h"
#include "../queue/MyQueue.h"
#include "../stl_utils/vector_utilities.h"

using namespace std;

class Table;

class Token
{
public:
    Token();
    Token(string str, int type);
    friend ostream &operator<<(ostream &outs, const Token &t);
    string type_string();
    string token_str() const;
    virtual int type();
    virtual string get_data() { return ""; }                                   
    virtual void calculate(Stack<Token *> &s, Table &t, vector<string> fes) {} 
    virtual void postfix(Queue<Token *> &out, Stack<Token *> &op) {}           

private:
    string _token;
    int _type;
};

#endif // TOKEN_H_
