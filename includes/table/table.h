#ifndef TABLE_H_
#define TABLE_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include "typedefs.h"                    //vectorstr
#include "../binary_files/file_record.h" //binary file
#include "../binary_files/utilities.h"   //file functions
#include "../bplustree/map.h"            //map
#include "../bplustree/multimap.h"       //mmap
#include "../stack/MyStack.h"            //stack
#include "../queue/MyQueue.h"            //queue
#include "../token/child_tokens.h"       //child tokens
using namespace std;

class Table
{
public:
    // Constructor
    Table();
    Table(char *fname);             //existing file
    Table(char *fi, vectorstr fes); //creat new file
    // Modifier
    void insert_into(vectorstr data);
    void set_select_recons(vector<long> selectnos); //set _select_recons for selected table
    // Accessor
    Table select_all(vectorstr fes);                                 //select all records in the selected fields
    Table select(vectorstr fes, string fe, string op, string datum); //one condition
    Table select(vectorstr fes, vectorstr cond);                     //take infix condition
    Table select(vectorstr fes, Queue<Token *> post);                //take postfix condition
    vector<long> select_recnos();                                    //set record numbers for select table
    vectorstr get_fields();                                          //get list of fields name
    // Print
    void print_table(ostream &outs) const;
    friend ostream &operator<<(ostream &outs, const Table &print_me);
    // Debug tool
    void print_table_tree();

private:
    char table_name[50];
    char info[50];                     //table_name_info: contains fields name
    char sql[50];                      //table_name_sql: contains records
    vector<MMap<string, long>> fields; //indices vector of mmap
    vectorstr field_name_vec;
    Map<string, int> field_name; //stores field names and its column
    int serial;                  //global serial number
    vector<long> _select_recnos; //last selected record numbers
    int count;                   //how many records in the table

    Table make_table(vectorstr fes);                  //make selected table
    Queue<Token *> post_order_queue(vectorstr input); //convert infix to postfix
    vector<Token *> convert_token(vectorstr input);   //convert (vector of) string to token
};

#endif // TABLE_H_
