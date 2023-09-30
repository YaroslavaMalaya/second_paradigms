#include <iostream>
#include <stack>
#include "LinkedList.h"
#include "Stack.h"
using namespace std;

int main() {
    int command;
    LinkedList myList{};
    myList.head = nullptr;
    myList.current = nullptr;
    string input;
    string fileName;
    string searchText;
    int lineIndex;
    int symbolIndex;
    int startIndex;
    int numberIndex;
    stack<LinkedList> undoStack;
    LinkedList buffer{};
    stack<LinkedList> redoStack;
    string replText;

    cout << "\nAll commands:\n1-enter new text.\n2-start the new line.\n3-saving the information to your file."
            "\n4-loading the information from your file.\n5-print the current text to console.\n6-insert the text "
            "by line and symbol index.\n7-search by word.\n8-delete command.\n9-undo command.\n10-redo command."
            "\n11-cut command.\n12-paste command.\n13-copy command.\n14-replacement command.\n";

    while (true) {
        //system("clear");
        cout << "Choose the command: ";
        cin >> command;
        switch (command) {
            case 1:
                cin.ignore(); // clear the input buffer
                cout << "Enter text to append (please, no more than 100 characters): ";
                getline(cin, input);
                myList.addCharElement(&myList, input);
                myList.printLinkedList(&myList);
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 2:
                myList.addNewLine(&myList);
                cout << "New line is started.\n";
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 3:
                cout << "Enter the file name for saving: ";
                cin >> fileName;
                myList.saveTextToFile(&myList, fileName);
                cout << "Text has been saved successfully.\n";
                break;
            case 4:
                cout << "Enter the file name for loading: ";
                cin >> fileName;
                if (!fileName.empty()) {
                    myList.loadTextFromFile(&myList, fileName);
                    cout << "Text has been loaded successfully.\n";
                } else {
                    cout << "Choose command 3.\n";
                }
                break;
            case 5:
                myList.printLinkedList(&myList);
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 6:
                cout << "Choose line and index: ";
                cin >> lineIndex >> symbolIndex;
                cin.ignore(); // clear the input buffer
                cout << "Enter text to insert (please, no more than 100 characters): ";
                getline(cin, input);
                myList.insertText(&myList, lineIndex, symbolIndex, input);
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 7:
                cin.ignore(); // clear the input buffer
                cout << "Enter text to search: ";
                getline(cin, searchText);
                cout << "Text is present in this position: ";
                myList.searchInText(&myList, searchText);
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 8:
                cout << "Choose line, index and number of symbols: ";
                cin >> lineIndex >> startIndex >> numberIndex;
                myList.deleteText(&myList, lineIndex, startIndex, numberIndex);
                cout << "Text has been deleted successfully.\n";
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 9:
                myList = undo(&undoStack, &redoStack);
                myList.printLinkedList(&myList);
                pushCurrentCommand(&myList, &redoStack);
                cout << "Undo completed.\n";
                break;
            case 10:
                myList = redo(&redoStack);
                myList.printLinkedList(&myList);
                cout << "Redo completed.\n";
                break;
            case 11:
                cout << "Choose line and index and number of symbols: ";
                cin >> lineIndex >> startIndex >> numberIndex;
                myList.cutText(&myList, lineIndex, startIndex, numberIndex, &buffer);
                myList.printLinkedList(&myList);
                break;
            case 12:
                cout << "Choose line and index: ";
                cin >> lineIndex >> startIndex;
                myList.pasteText(&myList, lineIndex, startIndex, &buffer);
                myList.printLinkedList(&myList);
                break;
            case 13:
                cout << "Choose line and index and number of symbols: ";
                cin >> lineIndex >> startIndex >> numberIndex;
                myList.copyText(&myList, lineIndex, startIndex, numberIndex, &buffer);
                myList.printLinkedList(&buffer);
                myList.printLinkedList(&myList);
                break;
            case 14:
                cout << "Choose line and index: ";
                cin >> lineIndex >> startIndex;
                cin.ignore();
                cout << "Write text: ";
                getline(cin, replText);
                myList.replacementText(&myList, lineIndex, startIndex, replText);
                myList.printLinkedList(&myList);
                break;
            default:
                cout << "The command is not implemented.\n";
                break;
        }
    }
}