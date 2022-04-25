#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"

using namespace std;

void PARSE();
void ADD();
void PRINT();

int main() {
  cout << "Red-Black Tree: Insertion" << endl << endl;
  bool running = true;
  char command[15]; 
  char input[10]; //User input
  char fileInput[10000]; //File input
  int modify[100];

  while (running == true) {
    cout << "Options: Add, FAdd, Print, Quit" << endl;
    cin.get(command, 15);
    cin.clear();
    cin.ignore(10000, '\n');
    if (strcmp(command, "Add") == 0) {

    }
    else if (strcmp(command, "FAdd") == 0) {

    }
    else if (strcmp(command, "Print") == 0) {

    }
    else if (strcmp(command, "Quit") == 0) {
      cout << endl << "Quitting Red-Black Tree: Insertion Edition" << endl;
      running = false;
    }
    else {
      cout << "Invalid input, try again." << endl << endl;
    }
  }
}
