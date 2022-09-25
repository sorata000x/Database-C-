#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "stokenize.h"

STokenizer::STokenizer() : _pos(0)
{
    make_table(_table);
}
STokenizer::STokenizer(char str[]) : _pos(0)
{
    set_string(str);
    make_table(_table);
}
bool STokenizer::done()
{
    bool done = _pos >= strlen(_buffer);
    return done; // True if reach end of string
}
bool STokenizer::more()
{
    bool more = _pos <= strlen(_buffer);
    return more; // True if not reach end of string
}

STokenizer &operator>>(STokenizer &s, Token &t)
{
    string token;
    if (s.get_token(START_NUMBER, token))
    {
        t = Token(token, TOKEN_NUMBER);
        return s;
    }
    if (s.get_token(START_ALPHA, token))
    {
        t = Token(token, TOKEN_ALPHA);
        return s;
    }
    if (s.get_token(START_QUOTE, token))
    {
        t = Token(token, TOKEN_QUOTE);
        return s;
    }
    if (s.get_token(START_STAR, token))
    {
        t = Token(token, TOKEN_STAR);
        return s;
    }
    if (s.get_token(START_OPERATOR, token))
    {
        t = Token(token, TOKEN_OPERATOR);
        return s;
    }
    if (s.get_token(START_PARENTHESE, token))
    {
        t = Token(token, TOKEN_OPERATOR);
        return s;
    }
    if (s.get_token(START_COMMENT, token)) //print out comment
    {
        cout << token << endl;
        if (s.more())
            s >> t;
        return s;
    }
    // if token is UNKNOWN (or SPACE), SKIP IT
    s._pos++;
    if (s.more())
        s >> t;
    return s;
}

void STokenizer::set_string(char str[])
{
    strcpy(_buffer, str);
}

int STokenizer::get_pos() // NEW, for file tokenizer
{
    return _pos;
}

//create table for all the tokens we will recognize
//                      (e.g. doubles, words, etc.)
void STokenizer::make_table(int _table[][MAX_COLUMNS])
{
    init_table(_table);

    // NUMBER (0-3)
    mark_fail(_table, 0);
    mark_success(_table, 1);
    mark_fail(_table, 2);
    mark_success(_table, 3);
    mark_cells(0, _table, NUMBER, 1); // '0'-'9' -> State 1
    mark_cell(0, _table, '.', 2);     // '.' -> State 2
    mark_cells(1, _table, NUMBER, 1); // '0'-'9' -> State 1
    mark_cell(1, _table, '.', 2);     // '.' -> State 2
    mark_cells(2, _table, NUMBER, 3); // '0'-'9' -> State 3
    mark_cells(3, _table, NUMBER, 3); // '0'-'9' -> State 3

    // ALPHABET (4-5)
    mark_fail(_table, 4);
    mark_success(_table, 5);
    mark_cells(4, _table, ALPHA, 5); // 'a'-'Z' -> State 5
    mark_cells(5, _table, ALPHA, 5); // 'a'-'Z' -> State 5

    // QUOTE (6-8)
    mark_fail(_table, 6);
    mark_fail(_table, 7);
    mark_success(_table, 8);
    mark_cells(6, _table, QUOTE, 7);
    mark_cells(7, _table, ALPHA, 7);
    mark_cells(7, _table, SPACES, 7);
    mark_cells(7, _table, PUNC, 7);
    mark_cells(7, _table, QUOTE, 8);

    // STAR (10-11)
    mark_fail(_table, 10);
    mark_success(_table, 11);
    mark_cells(10, _table, STAR, 11);

    //OPERATOR (12-13)
    mark_fail(_table, 12);
    mark_success(_table, 13);
    mark_cells(12, _table, OPERATOR, 13);
    mark_cells(13, _table, OPERATOR, 13);

    //PARENTHESE (14-15)
    mark_fail(_table, 14);
    mark_success(_table, 15);
    mark_cells(14, _table, PARENTHESE, 15);
}

//extract the longest string that match
//     one of the acceptable token types
bool STokenizer::get_token(int start_state, string &token)
{
    assert((start_state > -1) && "State have to be above -1");

    const int size = strlen(_buffer); // get size of string
    int start_pos = _pos;             // Mark start position
    char t[MAX_BUFFER] = " ";         // hold token char
    int success_pos = _pos - 1;       // Set last success state to previous one postion
    bool success_extra = false;       // Successcully extrated or not

    if (_buffer[_pos] < 0) // UNKNOWN token
        return success_extra;

    //handle comment
    if (start_state == START_COMMENT)
    {
        if (_buffer[_pos] == '/' && _buffer[_pos + 1] == '/') // if the first two chars are '//'
        {
            int i = _pos;
            int j = 0;
            if (_buffer[i - 1] == '\n')
            {
            }
            while (_buffer[i] != '\n' && _buffer[i] != '\0')
            {
                t[j] = _buffer[i];
                i++;
                j++;
            }
            _pos = i;
            token = t;
            return true;
        }
        else
            return false;
    }

    int state = _table[start_state][_buffer[_pos]]; // Go to next state

    while ((state > -1) && (_pos < size))
    { // loop until reach fail state or end of string
        if (is_success(_table, state))
        {
            success_pos = _pos; // Mark the last success position
            success_extra = true;
        }
        _pos++;
        state = _table[state][_buffer[_pos]]; // Go to next state
    }

    char snip;
    int j = 0;
    for (int i = 0; i <= (success_pos - start_pos); i++)
    { // Fill with success char
        snip = _buffer[start_pos + i];
        if (snip != '\"') //drop quotation marks
        {
            t[j] = snip;
            j++;
        }
    }

    _pos = success_pos + 1; // Set position to the next of last success
    token = t;              // Set token
    return success_extra;   // Return successful extract token or not
}
//---------------------------------

int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];