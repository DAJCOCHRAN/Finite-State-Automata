/**********************************************************************
 *
 * CISC 4090 (Theory of Computation)
 * Spring, 2020
 *
 * Project 2: A Turing Machine Emulator
 *
 * Header file for TM class
 *
 * Author: Donald Cochran
 * Date:   23 Mar 2020
 *
 **********************************************************************/
#pragma once

#include <fstream>
#include <string>
#include <vector>

// entry for a TM state table
struct Table_entry
{
    int new_state;  // 0 for accept, -1 for reject
    char new_char;
    char direction; // 'L' or 'R'
};
// deterministic Turing machine
class TM {
public:
    // trace the TM on input in_string, returning true if it accepts
    // and false if it rejects
    TM(std::ifstream &ifs);
    TM() = delete;                      // disallow 0-param ctor
    void describe();
    bool trace(std::string& in_string);
    // I/O for Table_entry
    friend std::ifstream& operator>>(std::ifstream &is, Table_entry& entry);
    friend std::ostream& operator<<(std::ostream &os, const Table_entry& entry);
private:
    Table_entry tempTable;         //Table entry temp to load into state_table;
    std::string sigma;             // input alphabet
    std::string gamma;             // tape alphabet
    int num_states;                // number of states
    char blank;                    // how we represent a blank
    std::vector<std::vector<Table_entry>> state_table; // transition table
};