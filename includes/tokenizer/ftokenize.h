#ifndef FTOKENIZE_H_
#define FTOKENIZE_H_

#include <iostream>
#include <iomanip>
#include <assert.h>
#include <fstream>
#include <string>
#include "../tokenizer/stokenize.h"

class FTokenizer
{
public:
    const int MAX_BLOCK = MAX_BUFFER;
    FTokenizer(char *fname);
    Token next_token();
    bool more();     //returns the current value of _more
    int pos();       //returns the value of _pos
    int block_pos(); //returns the value of _blockPos
    friend FTokenizer &operator>>(FTokenizer &f, Token &t);

private:
    bool get_new_block(); //gets the new block from the file
    bool get_new_line();
    std::ifstream _f; //file being tokenized
    STokenizer _stk;  //The STokenizer object to tokenize current block
    int _pos;         //Current position in the file
    int _blockPos;    //Current position in the current block
    bool _more;       //false if last token of the last block
                      //  has been processed and now we are at
                      //  the end of the last block.
};

#endif // FTOKENIZE_H_
