#include "file_record.h"

long FileRecord::write(fstream &outs)
{
    //WENT THOUGH BASIC TEST

    //r.write(f); //take the Record r and write it into file f
    //  and return the record number of this Record

    //write to the end of the file.
    outs.seekg(0, outs.end);

    long pos = outs.tellp(); //retrieves the current position of the
                             //      file pointer

    int row = sizeof(_record) / sizeof(_record[0]);
    int col;
    for (int i = 0; i < row; i++)
    {
        col = sizeof(_record[i]);
        //outs.write(&record[0], sizeof(record));
        outs.write(_record[i], col);
    }
    return pos / sizeof(_record); //record number
}

long FileRecord::read(fstream &ins, long recno)
{
    //WENT THOUGH BASIC TEST

    //returns the number of bytes read.
    //    r.read(f, 6);
    //    cout<<r<<endl;
    long pos = recno * sizeof(_record);
    ins.seekg(pos, ios_base::beg);

    int row = sizeof(_record) / sizeof(_record[0]);
    int col;
    for (int i = 0; i < row; i++)
    {
        col = sizeof(_record[i]);
        //ins.read(&_record[0], sizeof(_record))
        ins.read(_record[i], col);

        //don't you want to mark the end of  the cstring with null?
        //_record[] => [zero'\0'trash trash trash trash]
        //don't need the null character, but for those of us with OCD and PTSD:
        _record[i][ins.gcount()] = '\0';
    }
    //ins.read(_record[0], sizeof(_record[0]));

    return ins.gcount();
}

vector<string> FileRecord::vec()
{
    //WENT THOUGH BASIC TEST

    int i = 0;
    vector<string> vec;
    while (_record[i][0] != '\0')
    {
        vec.push_back(_record[i]);
        i++;
    }
    return vec;
}

ostream &operator<<(ostream &outs,
                    const FileRecord &r)
{
    //WENT THOUGH BASIC TEST

    int i = 0;
    while (r._record[i][0] != '\0')
    {
        outs << setw(15) << r._record[i];
        i++;
    }

    return outs;
}