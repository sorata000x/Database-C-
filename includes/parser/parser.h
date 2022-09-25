#ifndef PARSER_H_
#define PARSER_H_

#include "../table/typedefs.h"
#include "../token/token.h"
#include "../tokenizer/stokenize.h"
#include "../bplustree/map.h"

class Parser
{
public:
    Parser(string str);
    Parser(char *str); //constructor that takes a input string
    //Modifier
    void set_string(string s);
    //Accessor
    mmap_ss parse_tree();
    int get_column(string token);
    bool get_parse_tree(int start_state);
    void build_keyword_list();
    void make_table();
    //bool fail();
private:
    vector<string> _buffer;
    int _pos; //current position in _buffer
    static int _table[MAX_ROWS][MAX_COLUMNS];
    mmap_ss _parse_mmap;
    Map<string, int> _keyword;
    enum KEYWORDS
    {
        SUCCESS,
        SYMBOL,
        MAKE,
        CREATE,
        TABLE,
        INSERT,
        INTO,
        SELECT,
        FIELDS,
        VALUES,
        FROM,
        WHERE,
        STAR,
    };
};

#endif // PARSER_H_
