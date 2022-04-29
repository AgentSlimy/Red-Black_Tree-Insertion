#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"

//Colors
#define RESET "\033[0m"
#define RED   "\033[31m"
#define BLUE  "\033[34m" //Substitute for black

using namespace std;

struct Trunk { //Used for printing
    Trunk *previous;
    char* str;

    Trunk(Trunk* previous, char* str) {
        this->previous = previous;
        this->str = str;
    }
};

void showTrunks(Trunk* p) { //Uesd for printing
    if (p == NULL) 
        return;

    showTrunks(p->previous);

    cout << p->str;
}

void PARSE(char* in, int* modify, int& count);
void ADD(Node* &head, Node* &current, Node*& previous, int value);
void FADD(Node* &head);
void PRINT(Node* root, Trunk *previous, bool isLeft);

void BALANCE();
void rotateLeft();
void rotateRight();

int main() {
  cout << "Red-Black Tree: Insertion" << endl << endl;
  bool running = true;
  char command[15];
  Node* head = NULL;
  while (running == true) {
    cout << "Options: Add, FAdd, Print, Quit" << endl;
    cin.get(command, 15);
    cin.clear();
    cin.ignore(10000, '\n');
    if (strcmp(command, "Add") == 0) { //Add command, manually add a single value to the tree
      int value;
      cout << "Add value >> ";
      cin >> value;
      cin.clear();
      cin.ignore(10000, '\n');
      Node* current = head;
      Node* previous = NULL;
      ADD(head, current, previous, value);
      if (current != head) {
	//Balance
      }
      cout << endl << value << " added to tree." << endl << endl;
    }
    else if (strcmp(command, "FAdd") == 0) { //File add command, add values from a file to the tree
      FADD(head);
    }
    else if (strcmp(command, "Print") == 0) { //Print command, print out tree
      cout << endl;
      PRINT(head, NULL, false);
      cout << endl;
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

void FAdd(Node* &head) {
  char input[10000];
  char fileName[100];
  int modify[100];
  int modSize = 0;
  int count = 0;
  memset(input, 0, 10000);
  memset(fileName, 0, 100);
  memset(modify, 0, 100);

  cout << endl << "What is the name of the file? ";
  cin.get(fileName, 30);
  cin.clear();
  cin.ignore(100000, '\n');
  streampos size;
  ifstream file(fileName, ios::in | ios::binary | ios::ate);
  if (file.is_open()) {
    size = file.tellg();
    file.seekg(0, ios::beg);
    file.read(input, size);
    file.close();
    PARSE(input, modify, count); //Parse input to modify array
    cout << "Input: ";
    for (int i = 0; i < 100; i++) {
      if (modify[i] != 0) {
	cout << modify[i] << " ";
        modSize++;
      }
    }
    cout << endl << "Size: " << modSize << endl;
    Node* current = NULL;
    Node* previous = NULL;
    for (int i = 0; i < modSize; i++) {
      if (modify[i] == 0) break;
      current = head;
      ADD(head, current, previous, modify[i]);
    }
  }
}

void PRINT(Node* root, Trunk *previous, bool isLeft) { //Print functions, prints out tree
  if (root == NULL) {
    return;
  }
  char* prevStr = (char*)("    ");
  Trunk *trunk = new Trunk(previous, prevStr);
  PRINT(root->getLeft(), trunk, true);
  //Formatting tree
  if (!previous) {
    trunk->str = (char*)("---");
  }
  else if (isLeft) {
    trunk->str = (char*)(".---");
    prevStr= (char*)("   |");
  }
  else {
    trunk->str = (char*)("'---");
    previous->str = prevStr;
  }
  showTrunks(trunk);
  if (root->getColor() == 0) { //if Black
    cout << BLUE << root->getData() << RESET << endl;
  }
  else { //Red
    cout << RED << root->getData() << RESET << endl;
  }
  if (previous) {
    previous->str = prevStr;
  }
  trunk->str = (char*)("   |");
  PRINT(root->getRight(), trunk, false);
}

void PARSE(char* in, int* modify, int& count) { //Parse function, takes in input
    int x = 0;  //keeps track of # of chars before space
    for (int i = 0; i < strlen(in); i++) {
        if (in[i] == ' ') {
            if (x == 1) {
                int temp = 0;
                temp = in[i - 1] - '0';
                modify[count] = temp;
                count++;
                x = 0;
            }
            else {
                int temp = 0;
                for (int a = 0; a < x; a++) {
                    temp = 10 * temp + (in[i - x + a] - '0');
                }
                modify[count] = temp;
                count++;
                x = 0;
            }
        }
        else {
            int temp = 0;
            x++;
            if (i == strlen(in) - 1) {  //last possible pair of chars
                for (int a = 0; a < x; a++) {
                    temp = 10 * temp + (in[i + a + 1 - x] - '0');
                }
                modify[count] = temp;
                count++;
            }
        }
    }
}
