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
 * Date:   3/23/2020
 *
 **********************************************************************/

#include "TM.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;
//PRINTS TAPE THAT WILL BE REQUESTED FROM TRACE FUNCTION IN THIS FILE
void printTape(vector<string> &input)
{
    for (int i = 0; i < input.size(); i++)
    {
        cout << input[i] << " ";
    }
    cout << endl;
}
//RETURNS A STRING REPRESENTING STATES q1,q2,q3...including q0 accept and q/ reject
//ASCII translates numerical integer values into numerical character values for computability(reading TM Instructions)/presentation (when tape is printed)
string newStateBuffer(int state)
{
    string tapeState = "q";
    int ASCIIofState = 48 + state;
    tapeState.push_back(char(ASCIIofState));
    return tapeState;
}

//  OVERLOADED INPUT OPERATOR TO READ TM INSTRUCTIONS FROM A DATA FILE
//  THIS OPERATOR USED ONLY ONCE WILL PULL ONE ROW FROM FILE. WHEN THIS OPERATOR IS CALLED AGAIN, IT READS THE NEXT ROW.
ifstream &operator>>(ifstream &is, Table_entry &entry)
{
    int elementCount = 0;
    char checker;         //TEMPORARY BUFFER TO READ THE DATA
    while (is >> checker) //WHILE EACH CHAR IS READ
    {
        if (checker != '(' && checker != ')' && checker != ',') //FILTER NON NEEDED CHARS
        {
            if ((int(checker) > 47) && (int(checker) < 58) && elementCount == 0) //LOOKS FOR ASCII RANGE OF 1 - 9
            {
                entry.new_state = int(checker) - 48; //TRANSLATES CHECKER TO INT
                elementCount++;                      //update elementCount state of table
            }
            else if (checker == '-') //CATCHES THE REJECT STATE -1 SINCE - IS READ BEFORE 1
            {
                is >> checker;                              //pull integer character next to - sign
                entry.new_state = (int(checker) - 48) * -1; //-1 TRANSLATION OF '1' to 1 is still positive / STORE STATE
                elementCount++;
            }
            else if (elementCount == 1) //WE HAVE STATE STORED
            {
                entry.new_char = checker; //CHAR SAFE TO LOAD
                elementCount++;
            }
            else if (elementCount == 2) //WE HAVE NEW CHAR STORED
            {
                entry.direction = checker; //CHAR SAFE TO LOAD
                break;                     //exit loop
            }
            else
            {
                cout << "error" << endl; //SHOULD NOT SEE THIS
            }
        }
    }
    return is; //RETURNS FILE POINTER WHERE LAST READ
}

// THIS CONSTRUCTION OF TM OBJECT IS GOING TO REPETITIVELY CALL OVERLOADED INPUT OPERATOR
// TO PULL ALL OF THE DATA FROM A FILE TO CONSTRUCT A STATE TABLE OF TM INSTRUCTIONS
TM::TM(ifstream &ifs)
{
    cout << "TM CONSTRUCTOR CALLED...\n";
    cout << "PULLING INITIAL INSTRUCTIONS...\n";
    ifs >> num_states;
    ifs >> sigma;
    ifs >> gamma;
    cout << "PULLING INSTRUCTIONS AND BUILDING TABLE SCHEMA...\n";
    int currLoadingState = 0;       //CURRENT STATE OF NUMBER OF ELEMENTS LOADED INTO EACH STATE TABLE COLUMN
    int level = 0;                  //DETERMINES CURRENT ROW OF STATE TABLE
    state_table.resize(num_states); //ADJUST SIZE OF STATE TABLE TO THE SIZE SPECIFIED FROM TM INSTRUCTIONS
    while (ifs >> tempTable)        //WHILE READING WITH OVERLOADED INPUT OPERATOR
    {
        if (currLoadingState < gamma.size())
        {
            state_table[level].push_back(tempTable);
            currLoadingState++;
            if (currLoadingState == gamma.size())
            {
                level++;
                currLoadingState = 0;
            }
        }
    }
}
// DESCRIBE SIMPLY PRINTS THE ACCEPTING ALPHABET OF TM ALONG WITH THE TM INSTRUCTIONS PER STATE
void TM::describe()
{
    cout << "Turing machine definition:\n      ";
    for (int i = 0; i < gamma.size(); i++)
    {
        cout << gamma[i] << "        ";
    }
    cout << endl;
    int state = 1;
    for (int i = 0; i < state_table.size(); i++)
    {
        cout << state << ":";
        for (int j = 0; j < state_table[i].size(); j++)
        {
            cout << "(" << state_table[i][j].new_state << "," << state_table[i][j].new_char << "," << state_table[i][j].direction << ") ";
        }
        cout << endl;
        state++;
    }
}

// THIS FUNCTION IS WHAT DRIVES THE PROGRAM TO DECIDE IF INPUTED STRING IS GONNA BE ACCEPT OR REJECT.
bool TM::trace(string &in_string)
{
    //prepare tape for TM
    std::vector<string> tape; //using strings to store our q states and input
    tape.push_back("q1");     //HEAD OF TAPE
    string buffer;
    for (int i = 0; i < in_string.size(); i++)
    {
        buffer = in_string[i];
        tape.push_back(buffer);
    }
    tape.push_back("_"); //TAIL OF TAPE
    //prepare Sigma comparison with tape
    string gammaBuffer;
    std::vector<string> gammaVect;         //for comparison of gamma vector and tape vector compatability
    for (int i = 0; i < gamma.size(); i++) //store gamma in gamma vector
    {
        gammaBuffer = gamma[i];
        gammaVect.push_back(gammaBuffer);
    }
    printTape(tape); //INITIAL PRINT
    //Iterate through the tape
    int tapeStateIndex = 0;
    int tapeInputIndex = 1;
    int state = 1; //literaly starts at state one, but computer logic starts at 0 so use -1 rule when changing states
    bool breakMe = false;
    string stateBuffer;
    while (!breakMe)
    {
        //reading states of TM
        for (int i = 0; i < gamma.size(); i++)
        {
            if (tape[tapeInputIndex] == gammaVect[i]) //when tape input is same as gamma alphabet
            {
                if (state_table[state - 1][i].direction == 'R' && tapeInputIndex == 0) //THIS STATEMENT IS CALLED WHEN TM SWITCHES STATES FROM q5 TO q2 AND HAVE REACHED BEGINNING OF TAPE. have to manually switch '_' and 'q5'
                {
                    stateBuffer = newStateBuffer(state);
                    tape[0] = stateBuffer;
                    tape[1] = "_";
                    printTape(tape);
                    tape[tapeInputIndex] = "_";
                    state = state_table[state - 1][i].new_state; //update state
                    stateBuffer = newStateBuffer(state);
                    tape[tapeStateIndex] = stateBuffer; //print on the tape new character
                    //print qstate
                    tapeInputIndex = tapeInputIndex + 2;
                    //write state to tape
                    printTape(tape);
                }

                else if (state_table[state - 1][i].direction == 'R') //THIS STATEMENT IS CALLED WHEN TM INSTRUCITON MOVES TO THE RIGHT
                {
                    tape[tapeStateIndex] = state_table[state - 1][i].new_char; //print on the tape new character
                    state = state_table[state - 1][i].new_state;               //update state
                    stateBuffer = newStateBuffer(state);
                    //print qstate to tape
                    tape[tapeInputIndex] = stateBuffer;
                    tapeStateIndex++;
                    tapeInputIndex++;
                    //print table
                    printTape(tape);
                }
                else if (state_table[state - 1][i].direction == 'L' && tapeInputIndex == (tape.size() - 1)) // THIS STATEMENT IS CALLED WHEN TM REACHED TAIL OF TAPE AND NEEDS MOVING TO THE LEFT
                {
                    tape[tapeStateIndex] = state_table[state - 1][i].new_char; //print on tape new character
                    state = state_table[state - 1][i].new_state;               //update state
                    //print state q1,q2,...etc.
                    string stateBuffer = newStateBuffer(state);
                    tapeInputIndex = tapeInputIndex - 2;
                    tape[tapeInputIndex] = stateBuffer;
                    tapeStateIndex--;
                    tapeInputIndex--;
                    //print table
                    printTape(tape);
                }
                else if (state_table[state - 1][i].direction == 'L') //THIS STATEMENT IS CALLED WHEN TM INSTRUCTION IS MOVING TO THE LEFT
                {
                    tape[tapeStateIndex] = state_table[state - 1][i].new_char; //print on tape new character
                    state = state_table[state - 1][i].new_state;               //update state
                    //print state q1,q2,...etc.
                    string stateBuffer = newStateBuffer(state);
                    tape[tapeInputIndex] = stateBuffer;
                    tapeStateIndex--;
                    tapeInputIndex--;
                    //print table
                    printTape(tape);
                }
            }
            if (state == 0) //ALWAYS CHECK FOR STATE TO BE 0 WHICH SIGNIFIES ACCEPT
            {
                return true;
            }
            else if (state == -1)
            {
                return false; //ALWAYS CHECK FOR STATE TO BE -1 WHICH SIGNIFIES REJECT
            }
        }
    }
}
