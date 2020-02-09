#include"FSA.H"
#include<iostream>
using namespace std;

int main(int argc, char** argv)
{ 
    // command-line argument munging
    if (argc != 2) {
        cerr << "usage: " << argv[0] << " fsa_file\n"
             << "where fsa_file is the data describing the FSA\n";
        return 1;
    }

    // open the FSA data file
    //read data from a file into computer memory
    ifstream fsa_data(argv[1]);
    
    //cannot open data file
    if (!fsa_data) {
        cerr << argv[0] << ": couldn't open " << argv[1] << endl;
        return 2;
    }

    // initialize the FSA and print its description
    FSA fsa(fsa_data);
    cout << "FSA description:\n";
    fsa.describe();
    cout << endl;

    // prompt-read-eval loop
    cout << "Enter input strings, one line at a time:\n";
    cout<<"type finish to end the program"<<endl;
    while (true) {
        cout << "? ";
        string in_string;
        getline(cin, in_string);
        if (!cin) break;
        if (in_string == "finish") break;
        fsa.trace(in_string);
    }
}