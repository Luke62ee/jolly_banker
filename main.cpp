#include "bank.h"

int main(int argc, char* argv[])
{
    if (argc == 2) {
        string file = argv[1];
        Bank bank;
        bank.Read(file);
    }
    else {
        cerr << "ERROR: Incorrect input!" << endl;
        cerr << "Please enter valid input" << endl;
    }
}