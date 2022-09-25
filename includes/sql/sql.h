#ifndef SQL_H_
#define SQL_H_

#include <iostream>
#include <fstream>
#include <string>
#include "../table/table.h"
#include "../parser/parser.h"
#include "../tokenizer/ftokenize.h"

using namespace std;

class SQL
{
public:
    SQL();
    SQL(char *fname); //batch constructor
    Table command(string comd);
    vector<long> select_recnos(); //selected record numbers

private:
    Table table;
    bool batch;
};

#endif // SQL_H_
