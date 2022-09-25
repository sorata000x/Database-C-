#include "sql.h"

SQL::SQL() : batch(false) {}
SQL::SQL(char *fname) : batch(true) //batch constructor
{
    //open file
    std::ifstream file;
    file.open(fname);
    assert(!file.fail() && "Error Opening File");

    //read file line by line
    /*
     * print out entire line if there is // infront
     * excute as command line otherwise
     */
    string line;
    int i = 0;
    while (getline(file, line))
    {
        if (line.size() >= 2)
        {
            if (line.at(0) == '/' && line.at(1) == '/') //print if line has // in front
            {
                cout << line << endl;
            }
            else
            {
                cout << "[" << i << "] " << line << endl; //print input command
                command(line);                            //input command
                i++;
            }
        }
    }
    cout << "------- END OF BATCH PROCESS -------" << endl;
    file.close();
}
Table SQL::command(string comd)
{
    //WENT THOUGH BASIC TEST
    //TESTED IN MAIN

    //send command to parser and get a mmap of command
    Parser parser(comd);
    mmap_ss mmap;
    mmap = parser.parse_tree();
    //interpret command and input it into table
    string command = mmap["command"][0];
    string table_name = mmap["table_name"][0];
    char table_name_char[50];
    strcpy(table_name_char, table_name.c_str());
    if (command == "make" || command == "create") //make, table_name, col
    {
        vectorstr col = mmap["col"];
        table = Table(table_name_char, col); //new file
    }
    else if (command == "insert") //insert, table_name, values
    {
        table = Table(table_name_char); //existing file
        vectorstr values = mmap["values"];
        table.insert_into(values);
    }
    else if (command == "select") //select, table_name, fields (, where, condition)
    {
        table = Table(table_name_char); //existing file
        bool where = mmap.contains("where");
        vectorstr fields;
        if (mmap["fields"][0] == "*") //select all fields
            fields = table.get_fields();
        else
            fields = mmap["fields"];
        if (where) //with conditions
        {
            vectorstr conditions = mmap["condition"];
            table = table.select(fields, conditions);
        }
        else //no conditions
            table = table.select_all(fields);
        if (batch) //print the table if in batch mode
            cout << table << endl;
    }
    return table;
}
vector<long> SQL::select_recnos() { return table.select_recnos(); }