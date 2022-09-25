#include "table.h"

//public
// Constructor
Table::Table() : count(0) {}
Table::Table(char *fname) : count(0) //existing file
{
    //WENT THOUGH BASIC TEST

    strcpy(table_name, fname); //set table name
    //rebuild the index structures
    //  set field
    fstream f;
    FileRecord r;
    //info = (file name)_info
    strcpy(info, fname);
    strcat(info, "_info");
    //read field names and construct field_name map&vector
    open_fileRW(f, info);
    r.read(f, 0);
    vectorstr vec = r.vec();
    for (int i = 0; i < vec.size(); i++)
    {
        field_name.insert(vec[i], i);
        field_name_vec += vec[i];
        MMap<string, long> mmap;
        fields += mmap;
    }
    f.close();
    //  set records
    //sql = (file name)_info
    strcpy(sql, fname);
    strcat(sql, "_sql");
    //read records and construct record mmap
    open_fileRW(f, sql);
    int i = 0;
    long bytes = r.read(f, i);
    while (bytes > 0)
    {
        for (int j = 0; j < r.vec().size(); j++)
        {
            fields[j].insert(r.vec()[j], i);
        }
        i++;
        bytes = r.read(f, i);
        count++;
    }
    f.close();
}
Table::Table(char *fname, vectorstr fes) : count(0) //creat new file
{
    //WENT THOUGH BASIC TEST

    strcpy(table_name, fname); //set table name
    //info = (file name)_info
    strcpy(info, fname);
    strcat(info, "_info");
    //write field names into file info
    fstream f;
    open_fileW(f, info);
    FileRecord r(fes);
    r.write(f);
    f.close();
    //create index structures: one index (mmap) for each field
    int j = 0;
    for (auto i : fes)
    {
        field_name.insert(i, j);
        field_name_vec += i;
        j++;
    }
    //prepare for insert
    //sql = (file name)_info
    strcpy(sql, fname);
    strcat(sql, "_sql");
    open_fileW(f, sql);
    f.close();
}
// Modifier
void Table::insert_into(vectorstr data)
{
    //WENT THOUGH BASIC TEST

    //first write data into file
    fstream f;
    open_fileRW(f, sql);
    //build file record object, write value list into the binary file
    FileRecord r(data);
    int recno = r.write(f);
    //build the index structure
    //write gives the recno, insert each field with the recon into the index structure (mmap)
    for (int i = 0; i < data.size(); i++)
    {
        if (i >= fields.size())
            fields += MMap<string, long>();
        fields[i].insert(data[i], recno);
    }
    count++;
    f.close();
}
void Table::set_select_recons(vector<long> selectnos)
{
    //WENT THOUGH BASIC TEST

    _select_recnos = selectnos;
}
// Accessor
Table Table::select_all(vectorstr fes)
{
    //WENT THOUGH BASIC TEST

    //check if selected field exists, give warning if not exist
    bool contain = is_subset(field_name_vec, fes);
    if (!contain)
        cout << "WARNING: selected field does not exist." << endl;
    //select all record numbers
    _select_recnos.clear();
    for (long i = 0; i < count; i++)
        _select_recnos += i;
    return make_table(fes);
}
Table Table::select(vectorstr fes, string fe, string op, string datum)
{
    //WENT THOUGH BASIC TEST

    int pos = field_name.get(fe); //get the pos of corresponding field
    //store record numbers (according to condition)
    _select_recnos.clear();
    if (op == "=")
    {
        _select_recnos = fields[pos][datum];
    }
    else if (op == ">")
    {
        for (auto i = fields[pos].upper_bound(datum); i != fields[pos].end(); ++i)
        {
            _select_recnos += (*i).value_list;
        }
    }
    else if (op == "<")
    {
        for (auto i = fields[pos].begin(); i != fields[pos].lower_bound(datum); ++i)
        {
            _select_recnos += (*i).value_list;
        }
    }
    else if (op == ">=")
    {
        for (auto i = fields[pos].lower_bound(datum); i != fields[pos].end(); ++i)
        {
            _select_recnos += (*i).value_list;
        }
    }
    else if (op == "<=")
    {
        for (auto i = fields[pos].begin(); i != fields[pos].upper_bound(datum); ++i)
        {
            _select_recnos += (*i).value_list;
        }
    }

    return make_table(fes);
}
Table Table::select(vectorstr fes, vectorstr cond)
{
    //WENT THOUGH BASIC TEST

    Queue<Token *> q = post_order_queue(cond); //convert infix to postfix condition
    Table t = select(fes, q);                  //get the table from select postfix condition
    return t;
}
Table Table::select(vectorstr fes, Queue<Token *> post)
{
    //WENT THOUGH BASIC TEST

    if (post.empty()) //handle empty condition
    {
        cout << "WARNING: condition is empty" << endl;
        _select_recnos.clear(); //no condition so no record number
        return make_table(fes); //make a empty selected table
    }
    Stack<Token *> s;
    Token *t;
    for (; !post.empty();)
    {
        t = post.pop();
        t->calculate(s, *this, fes); //calculate resultset and put it in s
    }
    //there should only be one result set in s at this point
    _select_recnos = static_cast<ResultSet *>(s.pop())->get_data_set(); //set resultset
    return make_table(fes);
}
vector<long> Table::select_recnos()
{
    //WENT THOUGH BASIC TEST

    return _select_recnos;
}
vectorstr Table::get_fields()
{
    //WENT THOUGH BASIC TEST

    return field_name_vec;
}
// Print
void Table::print_table(ostream &outs = cout) const
{
    //WENT THOUGH BASIC TEST

    if (field_name.empty())
    {
        cout << "Table is empty." << endl;
        return;
    }
    //First row
    cout << "Table name: " << table_name << ", records: " << count << endl;
    //Second row
    cout << setw(15) << "record";
    fstream f;
    FileRecord r;
    open_fileRW(f, info);
    r.read(f, 0);
    cout << setw(15) << r << endl;
    f.close();
    //Following rows
    int i = 0;
    open_fileRW(f, sql);
    long bytes = r.read(f, i);
    while (bytes > 0)
    {
        cout << setw(15) << i << r << endl;
        i++;
        bytes = r.read(f, i);
    }
    cout << endl;
    f.close();
}
ostream &operator<<(ostream &outs, const Table &print_me)
{
    //WENT THOUGH BASIC TEST

    print_me.print_table(outs);
    return outs;
}
// Debug tool
void Table::print_table_tree()
{
    for (int i = 0; i < fields.size(); ++i)
    {
        cout << fields[i] << endl;
    }
}

//private
Table Table::make_table(vectorstr fes) //make table for select
{
    //WENT THOUGH BASIC TEST

    fstream f;
    FileRecord r;
    open_fileRW(f, sql);
    vector<vectorstr> new_record;
    vectorstr vec;
    int finum; //field number

    //read the data at selected record number and store in new_record
    for (auto i : _select_recnos)
    {
        r.read(f, i);
        vec.clear();
        for (auto j : fes)
        {
            finum = field_name[j];
            vec += r.vec()[finum];
        }
        new_record += vec;
    }
    f.close();

    //make a new file for selected table
    char sel_t[50] = "_select_table_";
    strcat(sel_t, table_name);
    open_fileW(f, sel_t);
    //insert new records into the new selected table
    Table t(sel_t, fes);
    for (auto i : new_record)
    {
        t.insert_into(i);
    }
    t.set_select_recons(_select_recnos);
    return t;
}
Queue<Token *> Table::post_order_queue(vectorstr input)
{
    //WENT THOUGH BASIC TEST

    //using shunting yard algorithm
    Queue<Token *> out_queue;
    Stack<Token *> op_stack;
    vector<Token *> vec = convert_token(input);
    for (auto i : vec)
    {
        i->postfix(out_queue, op_stack);
    }
    while (!op_stack.empty())
    {
        if (op_stack.top()->type() == 2 || op_stack.top()->type() == 3)
        {
            cout << "ERROR: mistached parentheses" << endl;
        }
        out_queue.push(op_stack.pop());
    }
    return out_queue;
}
vector<Token *> Table::convert_token(vectorstr input)
{
    //WENT THOUGH BASIC TEST

    vector<Token *> vec;
    for (auto i : input)
    {
        if (i == "=" || i == ">" || i == "<" || i == ">=" || i == "<=")
        {
            vec.push_back(new Relational(i));
        }
        else if (i == "and" || i == "or")
        {
            vec.push_back(new Logical(i));
        }
        else if (i == "(")
        {
            vec.push_back(new LParen(i));
        }
        else if (i == ")")
        {
            vec.push_back(new RParen(i));
        }
        else
        {
            vec.push_back(new TokenStr(i));
        }
    }
    return vec;
}