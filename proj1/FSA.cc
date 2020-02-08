/* Project 1: A Deterministic Finite-State Automaton
 *
 * Implementation file for FSA class
 *
 * Author: Donald Cochran
 * Date:   2/2/2020
 */

#include "FSA.h"
using namespace std;
//removes s
vector<char> placeChars(string input){
    vector<char> output;
    for(int i=0; i<input.length(); i++){
        if(input[i])
        {
            output.push_back(input[i]);
        }
    }
    return output;
}

vector<int> makeIntList(string input){
    vector<char> charaList;
    vector<int> output;
    int temp;
    charaList = placeChars(input);
    for(int i=0; i<input.size(); i++)
    {
        temp = (int)input[i] - 48; //ASCII digits start at 48!!
        if(temp > 0) // empty space characters became negative digits in vector
        output.push_back(temp);
    }
    return output;
}

/* This modified constructor checks that the file is open and loaded into memory before operation
    Then we will store all of our data into our program variables
*/
FSA::FSA(ifstream &ifs){
    cout << "called stub version of FSA constructor\n"; //INITIATION
    if (!ifs.is_open())
    { //If the file is not open we have a problem
        exit(EXIT_FAILURE);
    }
    vector<vector<int>> temp;
    vector<int> intList; 
    string readLine;   
    int index = 0;
    do
    {
        getline(ifs,readLine);
        switch (index)
        {
        case 0:
            sigma = readLine;
            break;
        case 1://Total States
            intList = makeIntList(readLine);
            num_states = intList[0];
            break;
        case 2://Start State
            intList = makeIntList(readLine);
            start_state = intList[0];
            break;
        case 3://Total accept, and accept states
            intList = makeIntList(readLine);
            total_accept = intList[0];
            for(int i=1; i<intList.size(); i++)
            {
                accept_states.push_back(intList[i]);
            }
            break;
        default:
            break;
        }
        if(index >= 4)
        {   
            intList = makeIntList(readLine);
            temp.push_back(intList);
        }
        index++;
    }while(ifs.good());
    get_state_table(temp);
}

// document me
void FSA::get_state_table(std::vector<std::vector<int>> sigmaList)
{
    cout<<"----STATE TABLE-----"<<endl;
    cout<< "s| "<<sigma[0] << " " << sigma[1] << endl;
    cout<< "_________"<<endl;
    for(int i=0; i<sigmaList.size(); i++)
    {
        cout<< i + 1 << "| ";
        for(int j=0; j<sigmaList[i].size(); j++ ) //length of the row
        {
            cout << sigmaList[i][j] << " ";
        }
        cout<< endl;
    }
        cout << endl;
}

// Description of machine variables from constructor
void FSA::describe()
{
    cout << "called stub version of describe()\n";
    cout<< "Alphabet: " << sigma << endl;
    cout<< "Total number of states: " << num_states <<endl;
    cout<< "Start state: " << start_state <<endl;
    cout<<"Total number of accept states: " << total_accept <<endl;
    cout<< "Accepting state(s): ";
    for(int i=0; i < accept_states.size(); i++){
        cout << accept_states[i] << " ";
    }
    cout<< endl;
}

// document me
void FSA::trace(const string &in_string)
{
    cout << "called stub version of trace()\n";
}
