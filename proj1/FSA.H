/*
 * CISC 4090 (Theory of Computation)
 * Spring, 2020
 *
 * Project 1: A Deterministic Finite-State Automaton
 *
 * Header file for FSA class
 *
 * Author: A. G. Werschulz
 * Date:   28 Jan 2020
 */

#pragma once

#include <fstream>
#include <string>
#include <vector>

class FSA {
public:
    FSA(std::ifstream &ifs);
    FSA() = delete;                 // disallow 0-param constructor
    void describe();
    void trace(const std::string& in_string);
private:
    std::string sigma;               // alphabet
    int num_states;                  // number of states
    int start_state;
    std::vector<int> accept_states;
    std::vector<std::vector<int>> state_table;
    void get_state_table(std::ifstream &ifs);
};