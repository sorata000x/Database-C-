# Database

Name: Aiden Chen <br>

### Description
- A database program that reads from a text file in csv format
  to form a table and allows user to find records that matches
  the input information.

### Features
- Implemented:
  - Database classes which response to commands or file of commands, write records into files and build tables according to select command.
- Partly implemented:
  - None
- Bugs
  - No known bugs

### Reflections

- This part went pretty smoothly

### Notes

- Give functions different stamps in different status:
  - //INCOMPLETE
  - //NOT USED
  - //NOT TESTED
  - //UNTOUCHED
  - //DUMMY
  - //BUGGED
  - //WENT THOUGH BASIC TEST
  - //WENT THOUGH TESTB
  - //TESTED
  - //COMPLETE
- Note: this is for me to keep track of every functions

### Output

##### basic_test.cpp output:

<pre>
----------running basic_test.cpp---------


[==========] Running 1 test from 1 test suite.
[----------] Global test environment set-up.
[----------] 1 test from SQL_BASIC
[ RUN      ] SQL_BASIC.SQLBasic
>make table employee fields  last,       first,         dep,      salary, year
basic_test: table created.

>make table employee fields  last,       first,         dep,      salary, year
Table name: employee, records: 0
         record           last          first            dep         salary           year


>insert into employee values Blow,       Joe,           CS,       100000, 2018
Table name: employee, records: 1
         record           last          first            dep         salary           year
              0           Blow            Joe             CS         100000           2018


>insert into employee values Blow,       JoAnn,         Physics,  200000, 2016
Table name: employee, records: 2
         record           last          first            dep         salary           year
              0           Blow            Joe             CS         100000           2018
              1           Blow          JoAnn        Physics         200000           2016


>insert into employee values Johnson,    Jack,          HR,       150000, 2014
Table name: employee, records: 3
         record           last          first            dep         salary           year
              0           Blow            Joe             CS         100000           2018
              1           Blow          JoAnn        Physics         200000           2016
              2        Johnson           Jack             HR         150000           2014


>insert into employee values Johnson,    "Jimmy",     Chemistry,140000, 2018
Table name: employee, records: 4
         record           last          first            dep         salary           year
              0           Blow            Joe             CS         100000           2018
              1           Blow          JoAnn        Physics         200000           2016
              2        Johnson           Jack             HR         150000           2014
              3        Johnson          Jimmy      Chemistry         140000           2018


>make table student fields  fname,          lname,    major,    age
Table name: student, records: 0
         record          fname          lname          major            age


>insert into student values Flo,            Yao,        Art,    20
Table name: student, records: 1
         record          fname          lname          major            age
              0            Flo            Yao            Art             20


>insert into student values Bo,                      Yang,      CS,             28
Table name: student, records: 2
         record          fname          lname          major            age
              0            Flo            Yao            Art             20
              1             Bo           Yang             CS             28


>insert into student values "Sammuel L.", Jackson,      CS,             40
Table name: student, records: 3
         record          fname          lname          major            age
              0            Flo            Yao            Art             20
              1             Bo           Yang             CS             28
              2     Sammuel L.        Jackson             CS             40


>insert into student values "Billy",         Jackson,   Math,   27
Table name: student, records: 4
         record          fname          lname          major            age
              0            Flo            Yao            Art             20
              1             Bo           Yang             CS             28
              2     Sammuel L.        Jackson             CS             40
              3          Billy        Jackson           Math             27


>insert into student values "Mary Ann",   Davis,        Math,   30
Table name: student, records: 5
         record          fname          lname          major            age
              0            Flo            Yao            Art             20
              1             Bo           Yang             CS             28
              2     Sammuel L.        Jackson             CS             40
              3          Billy        Jackson           Math             27
              4       Mary Ann          Davis           Math             30





>select * from employee
Error: selected field does not exist.
Table name: _select_table, records: 4
         record           last          first            dep         salary           year
              0           Blow            Joe             CS         100000           2018
              1           Blow          JoAnn        Physics         200000           2016
              2        Johnson           Jack             HR         150000           2014
              3        Johnson          Jimmy      Chemistry         140000           2018


basic_test: records selected: 0 1 2 3

>select last, first, age from employee
Error: selected field does not exist.
Table name: _select_table, records: 4
         record           last          first            age
              0           Blow            Joe           Blow
              1           Blow          JoAnn           Blow
              2        Johnson           Jack        Johnson
              3        Johnson          Jimmy        Johnson


basic_test: records selected: 0 1 2 3

>select last from employee
Error: selected field does not exist.
Table name: _select_table, records: 4
         record           last
              0           Blow
              1           Blow
              2        Johnson
              3        Johnson


basic_test: records selected: 0 1 2 3

>select * from employee where last = Johnson
Table name: _select_table, records: 2
         record           last          first            dep         salary           year
              0        Johnson           Jack             HR         150000           2014
              1        Johnson          Jimmy      Chemistry         140000           2018


basic_test: records selected: 2 3

>select * from employee where last=Blow and major="JoAnn"
Table name: _select_table, records: 0
         record           last          first            dep         salary           year


basic_test: records selected:

>select * from student
Error: selected field does not exist.
Table name: _select_table, records: 5
         record          fname          lname          major            age
              0            Flo            Yao            Art             20
              1             Bo           Yang             CS             28
              2     Sammuel L.        Jackson             CS             40
              3          Billy        Jackson           Math             27
              4       Mary Ann          Davis           Math             30


basic_test: records selected: 0 1 2 3 4

>select * from student where (major=CS or major=Art)
Table name: _select_table, records: 3
         record          fname          lname          major            age
              0            Flo            Yao            Art             20
              1             Bo           Yang             CS             28
              2     Sammuel L.        Jackson             CS             40


basic_test: records selected: 0 1 2

>select * from student where lname>J
Table name: _select_table, records: 4
         record          fname          lname          major            age
              0     Sammuel L.        Jackson             CS             40
              1          Billy        Jackson           Math             27
              2             Bo           Yang             CS             28
              3            Flo            Yao            Art             20


basic_test: records selected: 2 3 1 0

>select * from student where lname>J and (major=CS or major=Art)
Table name: _select_table, records: 3
         record          fname          lname          major            age
              0            Flo            Yao            Art             20
              1             Bo           Yang             CS             28
              2     Sammuel L.        Jackson             CS             40


basic_test: records selected: 0 1 2
----- END TEST --------
[       OK ] SQL_BASIC.SQLBasic (1093 ms)
[----------] 1 test from SQL_BASIC (1097 ms total)

[----------] Global test environment tear-down
[==========] 1 test from 1 test suite ran. (1103 ms total)
[  PASSED  ] 1 test.
</pre>

# main.cpp output:
<pre>

//****************************************************************************
//              CREATE TABLES AND INSERT RECORDS
//****************************************************************************
[0] make table employee fields  last,           first,                  dep,
                salary,         year
[1] insert into employee values Blow,           Joe,                    CS,
                        100000,         2018
[2] insert into employee values Blow,           JoAnn,                  Physics,        200000,         2016
[3] insert into employee values Johnson,        Jack,                   HR,
                150000,         2014
[4] insert into employee values Johnson,        "Jimmy",                Chemistry,      140000,         2018
[5] insert into employee values Yao,            Jimmy,                  Math,
                145000,         2014
[6] insert into employee values "Yao",          Flo,                    CS,
                        147000,         2012
[7] insert into employee values Yang,           Bo,                     CS,                             160000,         2013
[8] insert into employee values Jackson,        "Flo",                  Math,                   165000,         2017
[9] insert into employee values Jackson,        Bo,
        Chemistry,      130000,         2011
[10] insert into employee values "Jackson",     Billy,                  Math,
                170000,         2017
[11] insert into employee values Johnson,       "Mary Ann",     Math,                   165000,         2014
[12] insert into employee values Johnson,       "Billy Bob",    Physics,                142000,         2014
[13] insert into employee values Johnson,       Billy,                  "Phys Ed",      102000,         2014
[14] insert into employee values "Van Gogh",    Vincent,                Art,
                240000,         2015
[15] insert into employee values "Van Gogh",    Vincent,                CS,
                        245000,         2015
[16] insert into employee values "Van Gogh",    "Jim Bob",              "Phys Ed",      230000,         2010
[17] select * from employee
Table name: _select_table, records: 16
         record           last          first            dep         salary           year
              0           Blow            Joe             CS         100000           2018
              1           Blow          JoAnn        Physics         200000           2016
              2        Johnson           Jack             HR         150000           2014
              3        Johnson          Jimmy      Chemistry         140000           2018
              4            Yao          Jimmy           Math         145000           2014
              5            Yao            Flo             CS         147000           2012
              6           Yang             Bo             CS         160000           2013
              7        Jackson            Flo           Math         165000           2017
              8        Jackson             Bo      Chemistry         130000           2011
              9        Jackson          Billy           Math         170000           2017
             10        Johnson       Mary Ann           Math         165000           2014
             11        Johnson      Billy Bob        Physics         142000           2014
             12        Johnson          Billy        Phys Ed         102000           2014
             13       Van Gogh        Vincent            Art         240000           2015
             14       Van Gogh        Vincent             CS         245000           2015
             15       Van Gogh        Jim Bob        Phys Ed         230000           2010


[18] make table student fields fname, lname, major, age, company
[19] insert into student values Flo,                    Yao,            CS,
                                20,     Google
[20] insert into student values Bo,                             Yang,
        CS,                             28,             Microsoft
[21] insert into student values "Sammuel L.",   Jackson,        CS,
                        40,             Uber
[22] insert into student values "Flo",                  "Jackson",      Math,
                                21,             Google
[23] insert into student values "Greg",                         "Pearson",
        Physics,                        20,             Amazon
[24] insert into student values "Jim Bob",              Smith,          Math,
                                23,             Verizon
[25] insert into student values Calvin,                         Woo,
        Physics,                        22,             Uber
[26] insert into student values "Anna Grace",   "Del Rio",      CS,
                                22,             USAF
[27] insert into student values "Teresa Mae",   Gowers,         Chemistry,
                        22,             Verizon
[28] insert into student values Alex,                   Smith,          "Gender Studies",       53,             Amazon
[29] select * from student
Table name: _select_table, records: 10
         record          fname          lname          major            age        company
              0            Flo            Yao             CS             20         Google
              1             Bo           Yang             CS             28      Microsoft
              2     Sammuel L.        Jackson             CS             40           Uber
              3            Flo        Jackson           Math             21         Google
              4           Greg        Pearson        Physics             20         Amazon
              5        Jim Bob          Smith           Math             23        Verizon
              6         Calvin            Woo        Physics             22           Uber
              7     Anna Grace        Del Rio             CS             22           USAF
              8     Teresa Mae         Gowers      Chemistry             22        Verizon
              9           Alex          Smith Gender Studies             53         Amazon


//****************************************************************************
//              SIMPLE SELECT:
//****************************************************************************
[30] select * from student
Table name: _select_table, records: 10
         record          fname          lname          major            age        company
              0            Flo            Yao             CS             20         Google
              1             Bo           Yang             CS             28      Microsoft
              2     Sammuel L.        Jackson             CS             40           Uber
              3            Flo        Jackson           Math             21         Google
              4           Greg        Pearson        Physics             20         Amazon
              5        Jim Bob          Smith           Math             23        Verizon
              6         Calvin            Woo        Physics             22           Uber
              7     Anna Grace        Del Rio             CS             22           USAF
              8     Teresa Mae         Gowers      Chemistry             22        Verizon
              9           Alex          Smith Gender Studies             53         Amazon


//------- simple strings -------------------
[31] select * from student where lname = Jackson
Table name: _select_table, records: 2
         record          fname          lname          major            age        company
              0     Sammuel L.        Jackson             CS             40           Uber
              1            Flo        Jackson           Math             21         Google


[32] select * from student where major = CS
Table name: _select_table, records: 4
         record          fname          lname          major            age        company
              0            Flo            Yao             CS             20         Google
              1             Bo           Yang             CS             28      Microsoft
              2     Sammuel L.        Jackson             CS             40           Uber
              3     Anna Grace        Del Rio             CS             22           USAF


[33] select * from student where company = Uber
Table name: _select_table, records: 2
         record          fname          lname          major            age        company
              0     Sammuel L.        Jackson             CS             40           Uber
              1         Calvin            Woo        Physics             22           Uber


//----- quoted strings ---------------------
[34] select * from student where lname = "Del Rio"
Table name: _select_table, records: 1
         record          fname          lname          major            age        company
              0     Anna Grace        Del Rio             CS             22           USAF


[35] select * from student where fname = "Jim Bob"
Table name: _select_table, records: 1
         record          fname          lname          major            age        company
              0        Jim Bob          Smith           Math             23        Verizon


[36] select * from student where fname = "Anna Grace"
Table name: _select_table, records: 1
         record          fname          lname          major            age        company
              0     Anna Grace        Del Rio             CS             22           USAF


[37] select * from student where fname = "Teresa Mae"
Table name: _select_table, records: 1
         record          fname          lname          major            age        company
              0     Teresa Mae         Gowers      Chemistry             22        Verizon


//-------- non-existing string ------------------
[38] select * from student where lname = "Does Not Exist"
Table name: _select_table, records: 0
         record          fname          lname          major            age        company


//****************************************************************************
//              RELATIONAL OPERATORS:
//****************************************************************************
//.................
//:Greater Than   :
//.................
[39] select * from student where lname > Yang
Table name: _select_table, records: 1
         record          fname          lname          major            age        company
              0            Flo            Yao             CS             20         Google


[40] select * from student where major > Math
Table name: _select_table, records: 2
         record          fname          lname          major            age        company
              0           Greg        Pearson        Physics             20         Amazon
              1         Calvin            Woo        Physics             22           Uber


[41] select * from student where fname > "Sammuel L."
Table name: _select_table, records: 1
         record          fname          lname          major            age        company
              0     Teresa Mae         Gowers      Chemistry             22        Verizon


[42] select * from employee where salary > 200000
Table name: _select_table, records: 3
         record           last          first            dep         salary           year
              0       Van Gogh        Jim Bob        Phys Ed         230000           2010
              1       Van Gogh        Vincent            Art         240000           2015
              2       Van Gogh        Vincent             CS         245000           2015


[43] select * from employee where dep > Chemistry
Table name: _select_table, records: 9
         record           last          first            dep         salary           year
              0        Johnson           Jack             HR         150000           2014
              1            Yao          Jimmy           Math         145000           2014
              2        Jackson            Flo           Math         165000           2017
              3        Jackson          Billy           Math         170000           2017
              4        Johnson       Mary Ann           Math         165000           2014
              5        Johnson          Billy        Phys Ed         102000           2014
              6       Van Gogh        Jim Bob        Phys Ed         230000           2010
              7           Blow          JoAnn        Physics         200000           2016
              8        Johnson      Billy Bob        Physics         142000           2014


[44] select * from employee where last > Jackson
Table name: _select_table, records: 11
         record           last          first            dep         salary           year
              0        Johnson           Jack             HR         150000           2014
              1        Johnson          Jimmy      Chemistry         140000           2018
              2        Johnson       Mary Ann           Math         165000           2014
              3        Johnson      Billy Bob        Physics         142000           2014
              4        Johnson          Billy        Phys Ed         102000           2014
              5       Van Gogh        Vincent            Art         240000           2015
              6       Van Gogh        Vincent             CS         245000           2015
              7       Van Gogh        Jim Bob        Phys Ed         230000           2010
              8           Yang             Bo             CS         160000           2013
              9            Yao          Jimmy           Math         145000           2014
             10            Yao            Flo             CS         147000           2012


[45] select * from employee where first > "Billy Bob"
Table name: _select_table, records: 13
         record           last          first            dep         salary           year
              0           Yang             Bo             CS         160000           2013
              1        Jackson             Bo      Chemistry         130000           2011
              2            Yao            Flo             CS         147000           2012
              3        Jackson            Flo           Math         165000           2017
              4        Johnson           Jack             HR         150000           2014
              5       Van Gogh        Jim Bob        Phys Ed         230000           2010
              6        Johnson          Jimmy      Chemistry         140000           2018
              7            Yao          Jimmy           Math         145000           2014
              8           Blow          JoAnn        Physics         200000           2016
              9           Blow            Joe             CS         100000           2018
             10        Johnson       Mary Ann           Math         165000           2014
             11       Van Gogh        Vincent            Art         240000           2015
             12       Van Gogh        Vincent             CS         245000           2015


//. . . . . . . . . . . . . (Greater Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .
[46] select * from student where age > 50
Table name: _select_table, records: 1
         record          fname          lname          major            age        company
              0           Alex          Smith Gender Studies             53         Amazon


[47] select * from student where age > 35
Table name: _select_table, records: 2
         record          fname          lname          major            age        company
              0     Sammuel L.        Jackson             CS             40           Uber
              1           Alex          Smith Gender Studies             53         Amazon


[48] select * from student where fname > T
Table name: _select_table, records: 1
         record          fname          lname          major            age        company
              0     Teresa Mae         Gowers      Chemistry             22        Verizon


[49] select * from employee where salary > 130000
Table name: _select_table, records: 13
         record           last          first            dep         salary           year
              0        Johnson          Jimmy      Chemistry         140000           2018
              1        Johnson      Billy Bob        Physics         142000           2014
              2            Yao          Jimmy           Math         145000           2014
              3            Yao            Flo             CS         147000           2012
              4        Johnson           Jack             HR         150000           2014
              5           Yang             Bo             CS         160000           2013
              6        Jackson            Flo           Math         165000           2017
              7        Johnson       Mary Ann           Math         165000           2014
              8        Jackson          Billy           Math         170000           2017
              9           Blow          JoAnn        Physics         200000           2016
             10       Van Gogh        Jim Bob        Phys Ed         230000           2010
             11       Van Gogh        Vincent            Art         240000           2015
             12       Van Gogh        Vincent             CS         245000           2015


[50] select * from employee where  year > 2009
Table name: _select_table, records: 16
         record           last          first            dep         salary           year
              0       Van Gogh        Jim Bob        Phys Ed         230000           2010
              1        Jackson             Bo      Chemistry         130000           2011
              2            Yao            Flo             CS         147000           2012
              3           Yang             Bo             CS         160000           2013
              4        Johnson           Jack             HR         150000           2014
              5            Yao          Jimmy           Math         145000           2014
              6        Johnson       Mary Ann           Math         165000           2014
              7        Johnson      Billy Bob        Physics         142000           2014
              8        Johnson          Billy        Phys Ed         102000           2014
              9       Van Gogh        Vincent            Art         240000           2015
             10       Van Gogh        Vincent             CS         245000           2015
             11           Blow          JoAnn        Physics         200000           2016
             12        Jackson            Flo           Math         165000           2017
             13        Jackson          Billy           Math         170000           2017
             14           Blow            Joe             CS         100000           2018
             15        Johnson          Jimmy      Chemistry         140000           2018


//. . . . . . . . . . . . . (Greater than: last item) . . . . . . . . . . . . . . . . . .
[51] select * from student where age  > 53
Table name: _select_table, records: 0
         record          fname          lname          major            age        company


[52] select * from student where lname > Yao
Table name: _select_table, records: 0
         record          fname          lname          major            age        company


[53] select * from student where fname > "Teresa Mae"
Table name: _select_table, records: 0
         record          fname          lname          major            age        company


[54] select * from employee where last > "Van Gogh"
Table name: _select_table, records: 3
         record           last          first            dep         salary           year
              0           Yang             Bo             CS         160000           2013
              1            Yao          Jimmy           Math         145000           2014
              2            Yao            Flo             CS         147000           2012


[55] select * from employee where first > Vincent
Table name: _select_table, records: 0
         record           last          first            dep         salary           year


[56] select * from employee where salary > 260000
Table name: _select_table, records: 0
         record           last          first            dep         salary           year


//. . . . . . . . . . . . . (Greater Than: Passed last item) . . . . . . . . . . . . . . . . . . . . .
[57] select * from student where age > 54
Table name: _select_table, records: 0
         record          fname          lname          major            age        company


[58] select * from student where lname > Zoolander
Table name: _select_table, records: 0
         record          fname          lname          major            age        company


[59] select * from employee where last > Zoolaner
Table name: _select_table, records: 0
         record           last          first            dep         salary           year


[60] select * from employee where first > Xu
Table name: _select_table, records: 0
         record           last          first            dep         salary           year


//.................
//:Greater Equal  :
//.................
[61] select * from student where lname >= Yang
Table name: _select_table, records: 2
         record          fname          lname          major            age        company
              0             Bo           Yang             CS             28      Microsoft
              1            Flo            Yao             CS             20         Google


[62] select * from student where fname >= "Sammuel L."
Table name: _select_table, records: 2
         record          fname          lname          major            age        company
              0     Sammuel L.        Jackson             CS             40           Uber
              1     Teresa Mae         Gowers      Chemistry             22        Verizon


[63] select * from student where age >= 40
Table name: _select_table, records: 2
         record          fname          lname          major            age        company
              0     Sammuel L.        Jackson             CS             40           Uber
              1           Alex          Smith Gender Studies             53         Amazon


//. . . . . .  (Greater Equal non-existing: ) . . . . . . . . . . .
[64] select * from employee where last >= Jack
Table name: _select_table, records: 14
         record           last          first            dep         salary           year
              0        Jackson            Flo           Math         165000           2017
              1        Jackson             Bo      Chemistry         130000           2011
              2        Jackson          Billy           Math         170000           2017
              3        Johnson           Jack             HR         150000           2014
              4        Johnson          Jimmy      Chemistry         140000           2018
              5        Johnson       Mary Ann           Math         165000           2014
              6        Johnson      Billy Bob        Physics         142000           2014
              7        Johnson          Billy        Phys Ed         102000           2014
              8       Van Gogh        Vincent            Art         240000           2015
              9       Van Gogh        Vincent             CS         245000           2015
             10       Van Gogh        Jim Bob        Phys Ed         230000           2010
             11           Yang             Bo             CS         160000           2013
             12            Yao          Jimmy           Math         145000           2014
             13            Yao            Flo             CS         147000           2012


[65] select * from employee where first >= Bill
Table name: _select_table, records: 16
         record           last          first            dep         salary           year
              0        Jackson          Billy           Math         170000           2017
              1        Johnson          Billy        Phys Ed         102000           2014
              2        Johnson      Billy Bob        Physics         142000           2014
              3           Yang             Bo             CS         160000           2013
              4        Jackson             Bo      Chemistry         130000           2011
              5            Yao            Flo             CS         147000           2012
              6        Jackson            Flo           Math         165000           2017
              7        Johnson           Jack             HR         150000           2014
              8       Van Gogh        Jim Bob        Phys Ed         230000           2010
              9        Johnson          Jimmy      Chemistry         140000           2018
             10            Yao          Jimmy           Math         145000           2014
             11           Blow          JoAnn        Physics         200000           2016
             12           Blow            Joe             CS         100000           2018
             13        Johnson       Mary Ann           Math         165000           2014
             14       Van Gogh        Vincent            Art         240000           2015
             15       Van Gogh        Vincent             CS         245000           2015


[66] select * from employee where salary >= 235000
Table name: _select_table, records: 2
         record           last          first            dep         salary           year
              0       Van Gogh        Vincent            Art         240000           2015
              1       Van Gogh        Vincent             CS         245000           2015


//.................
//:Less Than      :
//.................
//. . . . . . . . . . . . . (Less Than: Non-existing) . . . . . . . . . . . . . . . . . . . . .
[67] select * from student where lname < Jackson
Table name: _select_table, records: 2
         record          fname          lname          major            age        company
              0     Anna Grace        Del Rio             CS             22           USAF
              1     Teresa Mae         Gowers      Chemistry             22        Verizon


[68] select * from student where major < Math
Table name: _select_table, records: 6
         record          fname          lname          major            age        company
              0            Flo            Yao             CS             20         Google
              1             Bo           Yang             CS             28      Microsoft
              2     Sammuel L.        Jackson             CS             40           Uber
              3     Anna Grace        Del Rio             CS             22           USAF
              4     Teresa Mae         Gowers      Chemistry             22        Verizon
              5           Alex          Smith Gender Studies             53         Amazon


[69] select * from student where fname < "Jim Bob"
Table name: _select_table, records: 7
         record          fname          lname          major            age        company
              0           Alex          Smith Gender Studies             53         Amazon
              1     Anna Grace        Del Rio             CS             22           USAF
              2             Bo           Yang             CS             28      Microsoft
              3         Calvin            Woo        Physics             22           Uber
              4            Flo            Yao             CS             20         Google
              5            Flo        Jackson           Math             21         Google
              6           Greg        Pearson        Physics             20         Amazon


[70] select * from employee where salary < 200000
Table name: _select_table, records: 12
         record           last          first            dep         salary           year
              0           Blow            Joe             CS         100000           2018
              1        Johnson          Billy        Phys Ed         102000           2014
              2        Jackson             Bo      Chemistry         130000           2011
              3        Johnson          Jimmy      Chemistry         140000           2018
              4        Johnson      Billy Bob        Physics         142000           2014
              5            Yao          Jimmy           Math         145000           2014
              6            Yao            Flo             CS         147000           2012
              7        Johnson           Jack             HR         150000           2014
              8           Yang             Bo             CS         160000           2013
              9        Jackson            Flo           Math         165000           2017
             10        Johnson       Mary Ann           Math         165000           2014
             11        Jackson          Billy           Math         170000           2017


[71] select * from employee where dep < CS
Table name: _select_table, records: 1
         record           last          first            dep         salary           year
              0       Van Gogh        Vincent            Art         240000           2015


[72] select * from employee where last < Jackson
Table name: _select_table, records: 2
         record           last          first            dep         salary           year
              0           Blow            Joe             CS         100000           2018
              1           Blow          JoAnn        Physics         200000           2016


[73] select * from employee where first < "Billy Bob"
Table name: _select_table, records: 2
         record           last          first            dep         salary           year
              0        Jackson          Billy           Math         170000           2017
              1        Johnson          Billy        Phys Ed         102000           2014


//. . . . . . . . . . . . . (Less than: first item) . . . . . . . . . . . . . . . . . .
[74] select * from student where age  < 20
Table name: _select_table, records: 0
         record          fname          lname          major            age        company


[75] select * from student where lname < "Del Rio"
Table name: _select_table, records: 0
         record          fname          lname          major            age        company


[76] select * from student where fname < Alex
Table name: _select_table, records: 0
         record          fname          lname          major            age        company


[77] select * from employee where last < Blow
Table name: _select_table, records: 0
         record           last          first            dep         salary           year


[78] select * from employee where first < Billy
Table name: _select_table, records: 0
         record           last          first            dep         salary           year


[79] select * from employee where salary < 100000
Table name: _select_table, records: 0
         record           last          first            dep         salary           year


//. . . . . . . . . . . . . (Less Than: before first item) . . . . . . . . . . . . . . . . . . . . .
[80] select * from student where age  < 19
Table name: _select_table, records: 0
         record          fname          lname          major            age        company


[81] select * from student where lname < Adams
Table name: _select_table, records: 0
         record          fname          lname          major            age        company


[82] select * from student where fname < Adam
Table name: _select_table, records: 0
         record          fname          lname          major            age        company


[83] select * from employee where last < Alex
Table name: _select_table, records: 0
         record           last          first            dep         salary           year


[84] select * from employee where first < Avory
Table name: _select_table, records: 0
         record           last          first            dep         salary           year


[85] select * from employee where dep < Alchemy
Table name: _select_table, records: 0
         record           last          first            dep         salary           year


//.................
//:Less Equal     :
//.................
[86] select * from student where lname <= Smith
Table name: _select_table, records: 7
         record          fname          lname          major            age        company
              0     Anna Grace        Del Rio             CS             22           USAF
              1     Teresa Mae         Gowers      Chemistry             22        Verizon
              2     Sammuel L.        Jackson             CS             40           Uber
              3            Flo        Jackson           Math             21         Google
              4           Greg        Pearson        Physics             20         Amazon
              5        Jim Bob          Smith           Math             23        Verizon
              6           Alex          Smith Gender Studies             53         Amazon


[87] select * from student where fname <= Greg
Table name: _select_table, records: 7
         record          fname          lname          major            age        company
              0           Alex          Smith Gender Studies             53         Amazon
              1     Anna Grace        Del Rio             CS             22           USAF
              2             Bo           Yang             CS             28      Microsoft
              3         Calvin            Woo        Physics             22           Uber
              4            Flo            Yao             CS             20         Google
              5            Flo        Jackson           Math             21         Google
              6           Greg        Pearson        Physics             20         Amazon


[88] select * from student where age <= 40
Table name: _select_table, records: 9
         record          fname          lname          major            age        company
              0            Flo            Yao             CS             20         Google
              1           Greg        Pearson        Physics             20         Amazon
              2            Flo        Jackson           Math             21         Google
              3         Calvin            Woo        Physics             22           Uber
              4     Anna Grace        Del Rio             CS             22           USAF
              5     Teresa Mae         Gowers      Chemistry             22        Verizon
              6        Jim Bob          Smith           Math             23        Verizon
              7             Bo           Yang             CS             28      Microsoft
              8     Sammuel L.        Jackson             CS             40           Uber


//. . . . . .  (Less Equal non-existing: ) . . . . . . . . . . .
[89] select * from employee where last <= Peach
Table name: _select_table, records: 10
         record           last          first            dep         salary           year
              0           Blow            Joe             CS         100000           2018
              1           Blow          JoAnn        Physics         200000           2016
              2        Jackson            Flo           Math         165000           2017
              3        Jackson             Bo      Chemistry         130000           2011
              4        Jackson          Billy           Math         170000           2017
              5        Johnson           Jack             HR         150000           2014
              6        Johnson          Jimmy      Chemistry         140000           2018
              7        Johnson       Mary Ann           Math         165000           2014
              8        Johnson      Billy Bob        Physics         142000           2014
              9        Johnson          Billy        Phys Ed         102000           2014


[90] select * from employee where first <= Gary
Table name: _select_table, records: 7
         record           last          first            dep         salary           year
              0        Jackson          Billy           Math         170000           2017
              1        Johnson          Billy        Phys Ed         102000           2014
              2        Johnson      Billy Bob        Physics         142000           2014
              3           Yang             Bo             CS         160000           2013
              4        Jackson             Bo      Chemistry         130000           2011
              5            Yao            Flo             CS         147000           2012
              6        Jackson            Flo           Math         165000           2017


[91] select * from employee where salary <= 23500
Table name: _select_table, records: 14
         record           last          first            dep         salary           year
              0           Blow            Joe             CS         100000           2018
              1        Johnson          Billy        Phys Ed         102000           2014
              2        Jackson             Bo      Chemistry         130000           2011
              3        Johnson          Jimmy      Chemistry         140000           2018
              4        Johnson      Billy Bob        Physics         142000           2014
              5            Yao          Jimmy           Math         145000           2014
              6            Yao            Flo             CS         147000           2012
              7        Johnson           Jack             HR         150000           2014
              8           Yang             Bo             CS         160000           2013
              9        Jackson            Flo           Math         165000           2017
             10        Johnson       Mary Ann           Math         165000           2014
             11        Jackson          Billy           Math         170000           2017
             12           Blow          JoAnn        Physics         200000           2016
             13       Van Gogh        Jim Bob        Phys Ed         230000           2010


//****************************************************************************
//              LOGICAL OPERATORS
//****************************************************************************
//.................
//:AND            :
//.................
[92] select * from student where fname = "Flo" and lname = "Yao"
Table name: _select_table, records: 1
         record          fname          lname          major            age        company
              0            Flo            Yao             CS             20         Google


[93] select * from student where major = "CS" and age < 25
Table name: _select_table, records: 2
         record          fname          lname          major            age        company
              0            Flo            Yao             CS             20         Google
              1     Anna Grace        Del Rio             CS             22           USAF


[94] select * from student where major < Math and age > 25
Table name: _select_table, records: 3
         record          fname          lname          major            age        company
              0             Bo           Yang             CS             28      Microsoft
              1     Sammuel L.        Jackson             CS             40           Uber
              2           Alex          Smith Gender Studies             53         Amazon


[95] select * from employee where dep = CS and salary > 150000
Table name: _select_table, records: 2
         record           last          first            dep         salary           year
              0           Yang             Bo             CS         160000           2013
              1       Van Gogh        Vincent             CS         245000           2015


[96] select * from employee where last = Jackson and year < 2015
Table name: _select_table, records: 1
         record           last          first            dep         salary           year
              0        Jackson             Bo      Chemistry         130000           2011


[97] select * from employee where last = Johnson and year >=2014
Table name: _select_table, records: 5
         record           last          first            dep         salary           year
              0        Johnson           Jack             HR         150000           2014
              1        Johnson          Jimmy      Chemistry         140000           2018
              2        Johnson       Mary Ann           Math         165000           2014
              3        Johnson      Billy Bob        Physics         142000           2014
              4        Johnson          Billy        Phys Ed         102000           2014


//.................
//:OR            :
//.................
[98] select * from student where fname = Flo or lname = Jackson
Table name: _select_table, records: 3
         record          fname          lname          major            age        company
              0            Flo            Yao             CS             20         Google
              1     Sammuel L.        Jackson             CS             40           Uber
              2            Flo        Jackson           Math             21         Google


[99] select * from student where age >=40  or company = Verizon
Table name: _select_table, records: 4
         record          fname          lname          major            age        company
              0     Sammuel L.        Jackson             CS             40           Uber
              1        Jim Bob          Smith           Math             23        Verizon
              2     Teresa Mae         Gowers      Chemistry             22        Verizon
              3           Alex          Smith Gender Studies             53         Amazon


[100] select * from employee where first = Bo or last = Johnson
Table name: _select_table, records: 7
         record           last          first            dep         salary           year
              0        Johnson           Jack             HR         150000           2014
              1        Johnson          Jimmy      Chemistry         140000           2018
              2           Yang             Bo             CS         160000           2013
              3        Jackson             Bo      Chemistry         130000           2011
              4        Johnson       Mary Ann           Math         165000           2014
              5        Johnson      Billy Bob        Physics         142000           2014
              6        Johnson          Billy        Phys Ed         102000           2014


[101] select * from employee where year >= 2015 or dep = CS
Table name: _select_table, records: 9
         record           last          first            dep         salary           year
              0           Blow            Joe             CS         100000           2018
              1           Blow          JoAnn        Physics         200000           2016
              2        Johnson          Jimmy      Chemistry         140000           2018
              3            Yao            Flo             CS         147000           2012
              4           Yang             Bo             CS         160000           2013
              5        Jackson            Flo           Math         165000           2017
              6        Jackson          Billy           Math         170000           2017
              7       Van Gogh        Vincent            Art         240000           2015
              8       Van Gogh        Vincent             CS         245000           2015


//.................
//:OR AND         :
//.................
[102] select * from student where fname = Flo or major = CS and age <= 23
Table name: _select_table, records: 3
         record          fname          lname          major            age        company
              0            Flo            Yao             CS             20         Google
              1            Flo        Jackson           Math             21         Google
              2     Anna Grace        Del Rio             CS             22           USAF


[103] select * from student where lname = Jackson or age < 23 and company > Uber
Table name: _select_table, records: 3
         record          fname          lname          major            age        company
              0     Sammuel L.        Jackson             CS             40           Uber
              1            Flo        Jackson           Math             21         Google
              2     Teresa Mae         Gowers      Chemistry             22        Verizon


[104] select * from employee where last = "Van Gogh" or last = Jackson and salary >= 165000
Table name: _select_table, records: 5
         record           last          first            dep         salary           year
              0        Jackson            Flo           Math         165000           2017
              1        Jackson          Billy           Math         170000           2017
              2       Van Gogh        Vincent            Art         240000           2015
              3       Van Gogh        Vincent             CS         245000           2015
              4       Van Gogh        Jim Bob        Phys Ed         230000           2010


//.................
//:AND OR AND     :
//.................
[105] select * from student where age <30 and major=CS or major = Physics and company = Amazon
Table name: _select_table, records: 4
         record          fname          lname          major            age        company
              0            Flo            Yao             CS             20         Google
              1             Bo           Yang             CS             28      Microsoft
              2           Greg        Pearson        Physics             20         Amazon
              3     Anna Grace        Del Rio             CS             22           USAF


[106] select * from student where age <=40 and company=Uber or major = CS and company = Google
Table name: _select_table, records: 3
         record          fname          lname          major            age        company
              0            Flo            Yao             CS             20         Google
              1     Sammuel L.        Jackson             CS             40           Uber
              2         Calvin            Woo        Physics             22           Uber


[107] select * from employee where dep = CS and salary >= 160000 or year > 2014 and last = "Van Gogh"
Table name: _select_table, records: 3
         record           last          first            dep         salary           year
              0           Yang             Bo             CS         160000           2013
              1       Van Gogh        Vincent            Art         240000           2015
              2       Van Gogh        Vincent             CS         245000           2015


//.................
//:OR AND OR      :
//.................
[108] select * from student where lname = Yang or major = CS and age < 23 or company = Google
Table name: _select_table, records: 4
         record          fname          lname          major            age        company
              0            Flo            Yao             CS             20         Google
              1             Bo           Yang             CS             28      Microsoft
              2            Flo        Jackson           Math             21         Google
              3     Anna Grace        Del Rio             CS             22           USAF


[109] select * from student where major = Physics or major = Math and company = Google or lname = Jackson
Table name: _select_table, records: 4
         record          fname          lname          major            age        company
              0     Sammuel L.        Jackson             CS             40           Uber
              1            Flo        Jackson           Math             21         Google
              2           Greg        Pearson        Physics             20         Amazon
              3         Calvin            Woo        Physics             22           Uber


[110] select * from employee where dep = CS or year >2014 and year < 2018 or salary >= 265000
Table name: _select_table, records: 8
         record           last          first            dep         salary           year
              0           Blow            Joe             CS         100000           2018
              1           Blow          JoAnn        Physics         200000           2016
              2            Yao            Flo             CS         147000           2012
              3           Yang             Bo             CS         160000           2013
              4        Jackson            Flo           Math         165000           2017
              5        Jackson          Billy           Math         170000           2017
              6       Van Gogh        Vincent            Art         240000           2015
              7       Van Gogh        Vincent             CS         245000           2015


------- END OF BATCH PROCESS -------

</pre>
