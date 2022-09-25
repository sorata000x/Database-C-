#ifndef CONSTANT_H_
#define CONSTANT_H_

const int MAX_COLUMNS = 256;
const int MAX_ROWS = 100;
const int MAX_BUFFER = 500;

const char ALPHA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char NUMBER[] = "0123456789";
//const char PUNC[] = ".,:;'~!?";
const char STAR[] = "*";
const char QUOTE[] = "\"";
const char OPERATOR[] = "=><";
const char PARENTHESE[] = "()";
const char PUNC[] = ".,:;'~!?";
const char SPACES[] = {' ', '\t', '\n', '\0'};
const char SLASH[] = "/";
const int START_NUMBER = 0;
const int START_ALPHA = 4;
const int START_QUOTE = 6;
const int START_STAR = 10;
const int START_OPERATOR = 12;
const int START_PARENTHESE = 14;
const int START_COMMENT = 16;


const int START_MAKE = 0;
const int START_INSERT = 6;
const int START_SELECT = 12;

//Token Types
const int TOKEN_NUMBER = 1;
const int TOKEN_ALPHA = 2;
const int TOKEN_QUOTE = 3;
const int TOKEN_STAR = 4;
const int TOKEN_OPERATOR = 5;

const int TOKEN_UNKOWN = -1;

#endif // CONSTANT_H_
