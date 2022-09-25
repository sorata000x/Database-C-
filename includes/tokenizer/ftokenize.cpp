#include "ftokenize.h"

#include <iostream>
#include <iomanip>
#include <assert.h>
#include <cstring>

FTokenizer::FTokenizer(char *fname)
{
    _pos = 0;
    _blockPos = 0;
    _more = false;
    _f.open(fname);
    assert(!_f.fail() && "Error Opening File");
}

Token FTokenizer::next_token()
{
    get_new_block();
    Token t;
    _stk >> t; //tokenize
    return t;
}
bool FTokenizer::more() //returns the current value of _more
{
    _more = (_stk.more()) || (!_f.eof());
    return _more;
}
int FTokenizer::pos() //returns the value of _pos
{
    return _pos;
}
int FTokenizer::block_pos() //returns the value of _blockPos
{
    _blockPos = _stk.get_pos();
    return _blockPos;
}
FTokenizer &operator>>(FTokenizer &f, Token &t)
{
    t = f.next_token();
    if (!f.more())
        f._f.close(); // Close the file in the end
    return f;
}

bool FTokenizer::get_new_block() //gets the new block from the file
{
    if ((block_pos() == 0) || (_stk.done() && !_f.eof())) // End of block or Not end of file
    {
        char buffer[MAX_BUFFER + 1]; // contian a block of string
        _f.read(buffer, MAX_BLOCK);  // read new block

        cout << "----- New Block ---------------------[" << _f.gcount() << "]"
             << " bytes" << endl;

        buffer[_f.gcount()] = NULL;

        cout << buffer << endl;

        _pos++; // Go to next block

        // assign new block to string tokenizer
        STokenizer stk(buffer);
        _stk = stk;
        return true;
    };
    return false;
}