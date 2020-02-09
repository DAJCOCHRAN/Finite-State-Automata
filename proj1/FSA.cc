/* Project 1: A Deterministic Finite-State Automaton
 *
 * Implementation file for FSA class
 *
 * Author: Donald Cochran
 * Date:   2/8/2020
 */

#include "FSA.h"
using namespace std;
//CONVERTS STRING TO CHAR VECTOR
vector<char> placeChars(string input)
{
    vector<char> output;
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i])
        {
            output.push_back(input[i]);
        }
    }
    return output;
}
//CONVERTS STRING TO CHAR VECTOR, THEN CONVERT CHAR VECTOR TO INT VECTOR W/ NO SPACES
vector<int> makeIntList(string input)
{
    vector<char> charaList;
    vector<int> output;
    int temp;
    charaList = placeChars(input);
    for (int i = 0; i < input.size(); i++)
    {
        temp = (int)input[i] - 48; //ASCII digits start at 48!!
        if (temp > 0)              // empty space characters became negative digits in vector
            output.push_back(temp);
    }
    return output;
}

/* This modified constructor checks that the file is open and loaded into memory before operation
    Then we will store all of our data into our program variables
*/
FSA::FSA(ifstream &ifs)
{
    cout << "called stub version of FSA constructor\n"; //INITIATION
    if (!ifs.is_open())
    { //If the file is not open we have a problem
        exit(EXIT_FAILURE);
    }
    vector<int> intList;
    string readLine;
    int index = 0;
    do
    {
        getline(ifs, readLine);
        switch (index)
        {
        case 0:
            sigma = readLine;
            break;
        case 1: //Total States
            intList = makeIntList(readLine);
            num_states = intList[0];
            break;
        case 2: //Start State
            intList = makeIntList(readLine);
            start_state = intList[0];
            break;
        case 3: //Total accept, and accept states
            intList = makeIntList(readLine);
            total_accept = intList[0];
            for (int i = 1; i < intList.size(); i++)
            {
                accept_states.push_back(intList[i]);
            }
            break;
        default:
            break;
        }
        if (index >= 4)
        {
            intList = makeIntList(readLine);
            state_table.push_back(intList);
        }
        index++;
    } while (ifs.good());
    get_state_table(state_table);
}

// Prints Table from FSA class object variables
void FSA::get_state_table(std::vector<std::vector<int>> sigmaList)
{
    cout << "----STATE TABLE-----" << endl;
    cout << "s | " << sigma[0] << " " << sigma[1] << endl;
    cout << "--|-----" << endl;
    for (int i = 0; i < sigmaList.size(); i++)
    {
        cout << i + 1 << " | ";
        for (int j = 0; j < sigmaList[i].size(); j++) //length of the row
        {
            cout << sigmaList[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Description of machine variables from class constructor
void FSA::describe()
{
    cout << "Alphabet: " << sigma << endl;
    cout << "Total number of states: " << num_states << endl;
    cout << "Start state: " << start_state << endl;
    cout << "Total number of accept states: " << total_accept << endl;
    cout << "Accepting state(s): ";
    for (int i = 0; i < accept_states.size(); i++)
    {
        cout << accept_states[i] << " ";
    }
    cout << endl;
}

// TRACE THROUGH THE 2 DIMENSIONAL VECTOR
void FSA::trace(const string &in_string)
{ //VAR DECLARATION OF INPUT VECTOR, CURRENT RUN-TIME STATE, AND BOOL TO BREAK LOOPS
    vector<char> in_vector = placeChars(in_string);
    currState = start_state - 1; //vector's index always start with 0
    bool breakMe = false;
    //WHILE INPUT VECTOR IS NOT EMPTY
    while (!in_vector.empty())
    { //CONDITIONAL SWITCHING OF ab CHARS AND EMPTYING INPUT VECTOR
        switch (in_vector[0])
        {
        case 'a':
            currState = state_table[currState][0] - 1;
            in_vector.erase(in_vector.begin());
            break;
        case 'b':
            currState = state_table[currState][1] - 1;
            in_vector.erase(in_vector.begin());
            break;
        //GIVE UP EMPTYING AND TRY AGAIN
        default:
            cout << "INVALID CHARACTERS!!" << endl;
            breakMe = true;
            break;
        }
        if (breakMe)
        {
            break;
        }
    }
    //REVERT CURRENT STATE VALUE BACK, DONE WITH VECTOR ITERATION
    currState++;
    for (int i = 0; i < num_states; i++)
    {
        if (currState == accept_states[i])
        {
            cout << "Language Accepted!!!" << endl;
            break;
        }
        if (i == num_states - 1)
        {
            cout << "Valid Input Language, But Not Accepted!!!" << endl;
            for (int i = 0; i < state_table.size(); i++)
            {
                cout << state_table[i].size() << endl;
            }
        }
    }
}
