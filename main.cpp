#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"

using namespace std;

void PARSE();
void ADD(Node* &head, Node* &current, Node*& previous, int value);
void FADD();
void PRINT();

void BALANCE();
void rotateLeft();
void rotateRight();

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
    if (strcmp(command, "Add") == 0) { //Add command, manually add a single value to the tree
      
    }
    else if (strcmp(command, "FAdd") == 0) { //File add command, add values from a file to the tree

    }
    else if (strcmp(command, "Print") == 0) { //Print command, print out tree

    }
    else if (strcmp(command, "Quit") == 0) { //Quit command, quits
      cout << endl << "Quitting Red-Black Tree: Insertion Edition" << endl;
      running = false;
    }
    else {
      cout << "Invalid input, try again." << endl << endl;
    }
  }
}

void ADD(Node* &head, Node* &current, Node*& previous, int value) {
  if (head == NULL) {
    head = new Node();
    current = head;
    head->setData(value);
    head->setColor(0); //Head is always black
  }
  else {
    if (value < current->getData()) {
      previous = current;
      current = current->getLeft();
      if (current == NULL) {
	current = new Node();
	current->setData(value);
	previous->setLeft(current);
	current->setParent(previous);
	//balance
	return;
      }
      else {
	ADD(head, current, previous, value);
      }
    }
    else {
      previous = current;
      current = current->getRight();
      if (current == NULL) {
	current = new Node();
	current->setData(value);
	previous->setRight(current);
	current->setParent(previous);
	//balance
	return;
      }
      else {
	ADD(head, current, previous, value);
      }
    }
  }
}
