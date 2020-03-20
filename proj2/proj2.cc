/**********************************************************************
 *
 * CISC 4090 (Theory of Computation)
 * Spring, 2020
 *
 * Project 2: A Turing Machine Emulator
 *
 * Given a file describing a TM, this program reads strings from
 * input, saying whether the TM accepts the string.  If the string is
 * accepted, then its trail through the TM is printed as well.
 *
 * The program does no error-checking on the input file.
 *
 * Author: A. G. Werschulz
 * Date:   20 Feb 2020
 *
 **********************************************************************/

#include "TM.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    // command-line argument munging
    if (argc != 2) {
        cerr << "usage: " << argv[0] << " tm_file\n"
             << "where tm_file is the data file describing the TM\n";
        return 1;
    }

    // open the TM data file
    ifstream tm_data(argv[1]);
    if (!tm_data) {
        cerr << argv[0] << ": couldn't open " << argv[1] << endl;
        return 2;
    }

    // initialize the TM and print its description
    TM tm(tm_data);
    cout << "Turing machine definition:\n";
    tm.describe();
    cout << endl;

    // prompt-read-eval loop
    cout << "Enter input strings, one line at a time:\n";
    while (true) {
        cout << "? ";
        string in_string;
        getline(cin, in_string);
        if (!cin) break;
        bool success = tm.trace(in_string);
        if (success) cout << "accept!\n";
        else cout << "reject!\n";
    }
}