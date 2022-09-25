#ifndef UTILITIES_H_
#define UTILITIES_H_

#include <iostream>
#include <fstream>
#include "file_record.h"
using namespace std;

//utility functions
bool file_exists(const char filename[]);

void open_fileRW(fstream &f, const char filename[]) throw(char *);
void open_fileW(fstream &f, const char filename[]);
// void confuse_me();
// void simple_test();

#endif // UTILITIES_H_
