#include "gtest/gtest.h"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include "../../includes/sql/sql.h"
using namespace std;

const vector<string> command_list = {

// CREATE
/*00*/     "create table employee fields  last,       first,         dep,      salary, year",
/*01*/     "insert into  employee values  Blow,       Joe,           CS,       100000, 2018",
/*02*/     "insert into  employee values  Blow,       JoAnn,         Physics,  200000, 2016",
/*03*/     "insert into  employee values  Johnson,    Jack,          HR,       150000, 2014",
/*04*/     "insert into  employee values  Johnson,    \"Jimmy\",     Chemistry,140000, 2018",
// MAKE
/*05*/     "make table  student fields fname,          lname,    major,   age",
/*06*/     "insert into student values Flo,            Yao, 	   Art,   	20",
/*07*/     "insert into student values Bo, 		         Yang, 	   CS, 		  28",
/*08*/     "insert into student values \"Sammuel L.\", Jackson,  CS, 		  40",
/*09*/     "insert into student values \"Billy\",	     Jackson,  Math,	  27",
/*10*/     "insert into student values \"Mary Ann\",   Davis,	   Math,	  30",
// SELECT
//   employee
/*11*/     "select * from employee",
/*12*/     "select first, salary, year from employee",
/*13*/     "select dep from employee",
//      where
//         =
/*14*/     "select * from employee where year = 2016",
//         <
/*15*/     "select * from employee where year < 2016",
//         >
/*16*/     "select * from employee where year > 2016",
//         <=
/*17*/     "select * from employee where year <= 2016",
//         >=
/*18*/     "select * from employee where year >= 2016",
//   student
/*19*/     "select * from student",
//      where
//         and
/*20*/     "select * from student where lname = Jackson and age = 27",
//         or
/*21*/     "select * from student where lname = Jackson or age = 27",
//         or and or
/*22*/     "select * from student where lname = Jackson or major = CS and age = 28 or fname = Flo",
//         and or and
/*23*/     "select * from student where lname = Jackson and major = CS or age = 28 and fname = Flo",
//         ()
/*24*/     "select * from student where (lname = Jackson)",
/*25*/     "select * from student where (fname=Flo and major=Art)",
/*26*/     "select * from student where (major=CS or major=Art)",
/*27*/     "select * from student where (lname = Yao) and (major=CS or major=Art)",
/*28*/     "select * from student where ((lname = Jackson or major = CS) and (age = 28 or fname = Flo))",
};

const int MAKE_TABLE_COMMANDS = 11;
const int SELECT_COMMANDS = 28;

bool sql_basic(bool debug = false)
{
     SQL sql;
     Table t;
     cout << ">" << command_list[0] << endl;
     sql.command(command_list[0]); 
     cout << "basic_test: table created." << endl<<endl;

     for (int i = 0; i < MAKE_TABLE_COMMANDS; i++)
     {
          cout << ">" << command_list[i] << endl;
          cout << sql.command(command_list[i]) << endl;
     }
     cout << endl
          << endl;
     /*
      *  Table name: employee, records: 4
      *  record           last          first            dep         salary           year
      *       0           Blow            Joe             CS         100000           2018
      *       1           Blow          JoAnn        Physics         200000           2016
      *       2        Johnson           Jack             HR         150000           2014
      *       3        Johnson          Jimmy      Chemistry         140000           2018
      */
     /*
      *  Table name: student, records: 5
      *  record          fname          lname          major            age
      *       0            Flo            Yao            Art             20
      *       1             Bo           Yang             CS             28
      *       2     Sammuel L.        Jackson             CS             40
      *       3          Billy        Jackson           Math             27
      *       4       Mary Ann          Davis           Math             30
      */
     for (int i = MAKE_TABLE_COMMANDS; i < command_list.size(); i++)
     {
          cout << "\n>" << command_list[i] << endl;
          if (debug)
          {
               cout<< sql.command(command_list[i])<<endl; //problem #15
          }
          else
               t = sql.command(command_list[i]);
          cout << "basic_test: records selected: "<<sql.select_recnos() << endl;
     }

     cout << "----- END TEST --------" << endl;
     return true;
}

TEST(SQL_BASIC, SQLBasic) {
  bool success = sql_basic(true);
  EXPECT_EQ(success, true);
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

