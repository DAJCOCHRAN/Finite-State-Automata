/**********************************************************************
 *
 * CISC 4090 (Theory of Computation)
 * Spring, 2020
 *
 * Project 2: A Turing Machine Emulator
 *
 * Implementation file for TM class
 *
 * Author: Donald Cochran
 * Date:   ???
 *
 **********************************************************************/

#include "TM.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

// document me
istream& operator>>(istream &is, Table_entry& entry)
{
    entry.new_state = 0;
    entry.new_char = ' ';
    entry.direction = ' ';
    return is;
}

// output the contents of a Table_entry
ostream& operator<<(ostream &os, const Table_entry& entry)
{
    return os << 'x';
}


// document me
TM::TM(ifstream &ifs)
{
    cout << "Stub version of TM constructor called\n";
}

// document me
void TM::describe()
{
    cout << "Stub version of TM::describe() called\n";
}

// document me
bool TM::trace(string& in_string)
{
    cout << "Stub version of TM::trace() called\n";
    return true;
}

// document me
void TM::print_config(int state, unsigned int pos,
                      const string& in_string)
{
    cout << "Stub version of TM::print_config() called\n";
}