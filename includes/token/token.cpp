#include "token.h"
#include "../tokenizer/constant.h"

Token::Token()
{
    _type = TOKEN_UNKOWN;
}

Token::Token(string str, int type)
{
    _token = str;
    _type = type;
}

ostream &operator<<(ostream &outs, const Token &t)
{
    outs << "|" << t.token_str() << "|" << endl; // Print token
    return outs;
}

int Token::type()
{
    return _type;
}

string Token::type_string()
{
    if (_type == TOKEN_NUMBER)
    {
        return "NUMBER";
    }
    if (_type == TOKEN_ALPHA)
    {
        return "ALPHA";
    }
    if (_type == TOKEN_QUOTE)
    {
        return "QUOTE";
    }
    if (_type == TOKEN_STAR)
    {
        return "STAR";
    }
    if (_type == TOKEN_OPERATOR)
    {
        return "OPERATOR";
    }
    return "UNKNOWN";
}

string Token::token_str() const
{
    return _token;
}
