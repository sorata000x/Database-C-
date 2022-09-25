#ifndef FILE_RECORD_H_
#define FILE_RECORD_H_

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

class FileRecord
{
public:
    //when you construct a Record, it's either empty or it
    //  contains a word
    FileRecord() : recno(-1)
    {
        //WENT THOUGH BASIC TEST

        int row = sizeof(_record) / sizeof(_record[0]);
        //mark every character of first row with null
        for (int i = 0; i < row; i++)
        {
            _record[i][0] = '\0';
        }
    }
    FileRecord(char str[]) : recno(-1)
    {
        //WENT THOUGH BASIC TEST

        int row = sizeof(_record) / sizeof(_record[0]);
        //mark every character of first row with null
        for (int i = 0; i < row; i++)
        {
            _record[i][0] = '\0';
        }
        strncpy(_record[0], str, MAX);
    }
    FileRecord(vector<string> v) : recno(-1)
    {
        //WENT THOUGH BASIC TEST

        int row = sizeof(_record) / sizeof(_record[0]);
        //mark every character of first row with null
        for (int i = 0; i < row; i++)
        {
            _record[i][0] = '\0';
        }
        recno = -1;
        for (int i = 0; i < v.size(); i++)
        {
            strncpy(_record[i], v[i].c_str(), MAX);
        }
    }

    long write(fstream &outs);           //returns the record number
    long read(fstream &ins, long recno); //returns the number of bytes
                                         //      read = MAX, or zero if
                                         //      read passed the end of file

    vector<string> vec(); //custom

    friend ostream &operator<<(ostream &outs,
                               const FileRecord &r);

private:
    static const int MAX = 100;
    int recno;
    char _record[MAX + 1][MAX + 1]; //change to two dimensional array
};

#endif // FILE_RECORD_H_
