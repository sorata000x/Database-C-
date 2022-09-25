#include "parser.h"

Parser::Parser(string str) : _pos(0)
{
    //NOT TESTED

    //convert string to char*
    char arr[300];
    strcpy(arr, str.c_str());
    //set _buffer
    //send char array to stokenizer
    STokenizer stk(arr);
    Token t;
    stk >> t;
    while (stk.more())
    {
        //add token to _str
        _buffer += t.token_str();
        t = Token();
        stk >> t; //tokenize
    }
    make_table();
    build_keyword_list();
}

Parser::Parser(char *arr) : _pos(0)
{
    //WENT THOUGH BASIC TEST

    //set _buffer
    //send char array to stokenizer
    STokenizer stk(arr);
    Token t;
    stk >> t;
    while (stk.more())
    {
        //add token to _str
        _buffer += t.token_str();
        t = Token();
        stk >> t; //tokenize
    }
    make_table();
    build_keyword_list();
}
void Parser::build_keyword_list() //make a map of keyword
{
    //WENT THOUGH BASIC TEST

    //everything else is SYMBOL
    _keyword.insert("make", MAKE);
    _keyword.insert("create", CREATE);
    _keyword.insert("table", TABLE);
    _keyword.insert("insert", INSERT);
    _keyword.insert("into", INTO);
    _keyword.insert("select", SELECT);
    _keyword.insert("fields", FIELDS);
    _keyword.insert("values", VALUES);
    _keyword.insert("from", FROM);
    _keyword.insert("where", WHERE);
    _keyword.insert("*", STAR);
}
mmap_ss Parser::parse_tree() //make a mmap of table
{
    //WENT THOUGH BASIC TEST

    if (get_parse_tree(START_MAKE))
        return _parse_mmap;
    if (get_parse_tree(START_INSERT))
        return _parse_mmap;
    if (get_parse_tree(START_SELECT))
        return _parse_mmap;
    cout << "Invalid input" << endl;
    return _parse_mmap;
}
void Parser::make_table() //state machine
{
    //WENT THOUGH BASIC TEST

    init_table(_table);
    // make table (state 0-5)
    mark_fail(_table, 0);
    mark_success(_table, 5);
    mark_cell(0, _table, MAKE, 1);   // make -> State 1
    mark_cell(0, _table, CREATE, 1);   // create -> State 1
    mark_cell(1, _table, TABLE, 2);  // table -> State 2
    mark_cell(2, _table, SYMBOL, 3); // symbol -> State 3
    mark_cell(3, _table, FIELDS, 4); // values -> State 4
    mark_cell(4, _table, SYMBOL, 5); // symbol -> State 5
    mark_cell(5, _table, SYMBOL, 5); // symbol -> State 5
    //insert into (state 6-11)
    mark_fail(_table, 6);
    mark_success(_table, 11);
    mark_cell(6, _table, INSERT, 7);   // insert -> State 7
    mark_cell(7, _table, INTO, 8);     // into -> State 8
    mark_cell(8, _table, SYMBOL, 9);   // symbol -> State 9
    mark_cell(9, _table, VALUES, 10);  // values -> State 10
    mark_cell(10, _table, SYMBOL, 11); // symbol -> State 11
    mark_cell(11, _table, SYMBOL, 11); // symbol -> State 11
    //select (state 12-19)
    mark_fail(_table, 12);
    mark_success(_table, 17);
    mark_success(_table, 19);
    mark_cell(12, _table, SELECT, 13); // select -> State 13
    mark_cell(13, _table, SYMBOL, 14); // symbol -> State 14
    mark_cell(13, _table, STAR, 15);   // star -> State 15
    mark_cell(14, _table, SYMBOL, 14); // symbol -> State 14
    mark_cell(14, _table, FROM, 16);   // from -> State 16
    mark_cell(15, _table, FROM, 16);   // from -> State 16
    mark_cell(16, _table, SYMBOL, 17); // symbol -> State 17
    mark_cell(17, _table, WHERE, 18);  // where -> State 18
    mark_cell(18, _table, SYMBOL, 19); // symbol -> State 19
    mark_cell(19, _table, SYMBOL, 19); // symbol -> State 19
}
int Parser::get_column(string token)
{
    //WENT THOUGH BASIC TEST

    if (_keyword.contains(token))
        return _keyword.at(token);
    else
        return SYMBOL;
}
bool Parser::get_parse_tree(int start_state) //make up the parser table (mmap)
{
    //WENT THOUGH BASIC TEST

    const int size = _buffer.size();
    string token; //start token
    int column;
    int state = start_state;
    int success_pos = _pos - 1;           // Set last success state to previous one postion
    bool success_parse = false;           // Successcully extrated or not
    while ((state > -1) && (_pos < size)) // loop until reach fail state or end of string
    {
        //get the first token
        token = _buffer[_pos];
        column = get_column(token);
        //go to next state
        state = _table[state][column];
        //record to parse_tree
        switch (state)
        {
        case 2:
            token = _buffer[_pos-1];
            _parse_mmap["command"] += token;
            break;
        case 3:
            _parse_mmap["table_name"] += token;
            break;
        case 5:
            _parse_mmap["col"] += token;
            break;
        case 8:
            _parse_mmap["command"] += string("insert");
            break;
        case 9:
            _parse_mmap["table_name"] += token;
            break;
        case 11:
            _parse_mmap["values"] += token;
            break;
        case 13:
            _parse_mmap["command"] += string("select");
            break;
        case 14:
            _parse_mmap["fields"] += token;
            break;
        case 15:
            _parse_mmap["fields"] += token;
            break;
        case 17:
            _parse_mmap["table_name"] += token;
            break;
        case 18:
            _parse_mmap["where"] += string("yes");
            break;
        case 19:
            _parse_mmap["condition"] += token;
            break;
        }
        if (is_success(_table, state))
        {
            success_pos = _pos; // Mark the last success position
            success_parse = true;
        }
        _pos++;
    }
    _pos = success_pos + 1; // Set position to the next of last success
    if (success_parse)
        return true; // Return successful extract token or not
    //else
    //reset ptree
    _parse_mmap.clear();
    return false;
}
void Parser::set_string(string str)
{
    //WENT THOUGH BASIC TEST

    _buffer.clear();
    char s[300];
    strcpy(s, str.c_str());
    STokenizer stk(s);
    Token t;
    stk >> t;
    while (stk.more())
    {
        //add token to _str
        _buffer += t.token_str();
        t = Token();
        stk >> t; //tokenize
    }
    _pos = 0;
}

int Parser::_table[MAX_ROWS][MAX_COLUMNS];