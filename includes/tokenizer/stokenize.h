#ifndef STOKENIZE_H_
#define STOKENIZE_H_

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../token/token.h"
#include "state_machine_functions.h"
#include "constant.h"

class STokenizer
{
public:
    STokenizer();
    STokenizer(char str[]);
    bool done(); //true: there are no more tokens
    bool more(); //true: there are more tokens
    //

    //---------------
    //extract one token (very similar to the way cin >> works)
    friend STokenizer &operator>>(STokenizer &s, Token &t);

    //set a new string as the input string
    void set_string(char str[]);

    int get_pos(); // NEW, for file tokenizer

private:
    //create table for all the tokens we will recognize
    //                      (e.g. doubles, words, etc.)
    void make_table(int _table[][MAX_COLUMNS]);

    //extract the longest string that match
    //     one of the acceptable token types
    bool get_token(int start_state, string &token);
    //---------------------------------
    char _buffer[MAX_BUFFER]; // Can only contain MAX_BUFFER-2 string (will out of boundary)
    int _pos;                 //current position in the string
    static int _table[MAX_ROWS][MAX_COLUMNS];
};

#endif // STOKENIZE_H_
