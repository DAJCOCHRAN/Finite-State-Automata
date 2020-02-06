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
#include <cstdlib>

using namespace std;

// document me!
FSA::FSA(ifstream &ifs)
{
    cout << "called stub version of FSA constructor\n";

    if (!ifs.is_open())
    { //If the file is not open we have a problem
        exit(EXIT_FAILURE);
    }

    char word[2];
    ifs >> word; //first value from document which should be the alphabet
    sigma = word;
    int index = 0; //to track each element we itterate through in the while
    while (ifs.good())
    {                        //while we are not to the end of the file
        cout << word << " "; //print word from file pointer
        int intVal = atoi(word); //convert file char to int
        switch (index)
        {
        case 0:
            //do nothing
            break;
        case 1:
            num_states = intVal;
            break;
        case 2:
            start_state = intVal;
            break;
        
        case 3:
            break;
        
        default:
            //cout << "An error has occured!!" << endl;
            break;
        }
        
        ifs >> word; //get to next word
        index++;
    }
    cout << word << endl; //last character to be printed
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
    cout<< "Start state: " << start_state <<endl;
    cout<< "Total number of states: " << num_states <<endl;
}

// document me
void FSA::trace(const string &in_string)
{
    cout << "called stub version of trace()\n";
}
