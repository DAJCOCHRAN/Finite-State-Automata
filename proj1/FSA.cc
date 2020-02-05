 /* Project 1: A Deterministic Finite-State Automaton
 *
 * Implementation file for FSA class
 *
 * Author: Donald Cochran
 * Date:   2/2/2020
 */

#include "FSA.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// document me!
FSA::FSA(ifstream &ifs)
{
    cout << "called stub version of FSA constructor\n";
    // do stuff here, the last action being
    get_state_table(ifs);
}

// document me
void FSA::get_state_table(ifstream &ifs)
{
    cout << "called stub version of get_state_table()\n";
}

// document me
void FSA::describe()
{
    cout << "called stub version of describe()\n";
}

// document me
void FSA::trace(const string& in_string)
{
    cout << "called stub version of trace()\n";
}
