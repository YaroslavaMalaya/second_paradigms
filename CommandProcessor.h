#include <iostream>
#include <stack>
#include "LinkedList.h"
#include "Stack.h"
#include "DynamicLib.h"
using namespace std;

class CommandProcessor {
public:
    CommandProcessor();
    void append();
    void newLine();
    void printText();
    void saveFile();
    void loadFile();
    void insert();
    void search();
    void deletet();
    void undo();
    void redo();
    void cut();
    void paste();
    void copy();
    void replacement();
    void cursor();
    void encrypt();
    void decrypt();

private:
    LinkedList myList;
    string input;
    string fileName;
    string searchText;
    int lineIndex;
    int symbolIndex;
    int startIndex;
    int numberIndex;
   stack<LinkedList> undoStack;
    LinkedList buffer;
    stack<LinkedList> redoStack;
    string replText;
    char* result;
    int key;
    char* text;
    CaesarCipher caesarCipher{"./liblibrary.dylib"};
};