#include <iostream>
#include <stack>
#include "LinkedList.h"
#include "Stack.h"
#include "DynamicLib.h"
using namespace std;

class CommandProcessor{
public:
    void append();
    void newLine();
    void saveFile();
    void loadFile();
    void printText();
    void insert();
    void search();
    void deletet();
    void undo();
    void redo();
    void cut();
    void paste();
    void copy();
    void cursor();
    void encrypt();
    void decrypt();
};

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
    char* result;
    int key;
    char* text;

    CaesarCipher caesarCipher("./liblibrary.dylib");

    cout << "\nAll commands:\n1-enter new text.\n2-start the new line.\n3-saving the information to your file."
            "\n4-loading the information from your file.\n5-print the current text to console.\n6-insert the text "
            "by line and symbol index.\n7-search by word.\n8-delete command.\n9-undo command.\n10-redo command."
            "\n11-cut command.\n12-paste command.\n13-copy command.\n14-replacement command.\n15-cursor logic."
            "\n16-encrypt.\n17-decrypt.\n";

    CommandProcessor cp;

    while (true) {
        cout << "\nChoose the command: ";
        cin >> command;
        switch (command) {
            case 1:
                cp.append();
                cin.ignore(); // clear the input buffer
                cout << "Enter text to append: ";
                getline(cin, input);
                myList.addCharElement(&myList, input);
                myList.printLinkedList(&myList);
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 2:
                cp.newLine();
                myList.addNewLine(&myList);
                cout << "New line is started.\n";
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 3:
                cp.saveFile();
                cout << "Enter the file name/path for saving: ";
                cin >> fileName;
                myList.saveTextToFile(&myList, fileName);
                cout << "Text has been saved successfully.\n";
                break;
            case 4:
                cp.loadFile();
                cout << "Enter the file name/path for loading: ";
                cin >> fileName;
                if (!fileName.empty()) {
                    myList.loadTextFromFile(&myList, fileName);
                    cout << "Text has been loaded successfully.\n";
                } else {
                    cout << "Choose command 3.\n";
                }
                break;
            case 5:
                cp.printText();
                myList.printLinkedList(&myList);
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 6:
                cp.insert();
                cout << "Choose line and index: ";
                cin >> lineIndex >> symbolIndex;
                cin.ignore(); // clear the input buffer
                cout << "Enter text to insert: ";
                getline(cin, input);
                myList.insertText(&myList, lineIndex, symbolIndex, input);
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 7:
                cp.search();
                cin.ignore(); // clear the input buffer
                cout << "Enter text to search: ";
                getline(cin, searchText);
                cout << "Text is present in this position: ";
                myList.searchInText(&myList, searchText);
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 8:
                cp.deletet();
                cout << "Choose line, index and number of symbols: ";
                cin >> lineIndex >> startIndex >> numberIndex;
                myList.deleteText(&myList, lineIndex, startIndex, numberIndex);
                cout << "Text has been deleted successfully.\n";
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 9:
                cp.undo();
                myList = undo(&undoStack, &redoStack);
                myList.printLinkedList(&myList);
                pushCurrentCommand(&myList, &redoStack);
                cout << "Undo completed.\n";
                break;
            case 10:
                cp.redo();
                myList = redo(&redoStack);
                myList.printLinkedList(&myList);
                cout << "Redo completed.\n";
                break;
            case 11:
                cp.cut();
                cout << "Choose line and index and number of symbols: ";
                cin >> lineIndex >> startIndex >> numberIndex;
                myList.cutText(&myList, lineIndex, startIndex, numberIndex, &buffer);
                myList.printLinkedList(&buffer);
                myList.printLinkedList(&myList);
                break;
            case 12:
                cp.paste();
                cout << "Choose line and index: ";
                cin >> lineIndex >> startIndex;
                myList.pasteText(&myList, lineIndex, startIndex, &buffer);
                myList.printLinkedList(&myList);
                break;
            case 13:
                cp.copy();
                cout << "Choose line and index and number of symbols: ";
                cin >> lineIndex >> startIndex >> numberIndex;
                myList.copyText(&myList, lineIndex, startIndex, numberIndex, &buffer);
                myList.printLinkedList(&myList);
                break;
            case 14:
                cp.paste();
                cout << "Choose line and index: ";
                cin >> lineIndex >> startIndex;
                cin.ignore();
                cout << "Write text: ";
                getline(cin, replText);
                myList.replacementText(&myList, lineIndex, startIndex, replText);
                myList.printLinkedList(&myList);
                break;
            case 15:
                cp.cursor();
                cout << "Choose line and index: ";
                cin >> lineIndex >> startIndex;
                myList.moveToPosition(&myList, lineIndex, startIndex);
                int subCommand;
                cout << "Choose a subcommand: \n"
                     << "1 - cut.\n"
                     << "2 - copy.\n"
                     << "3 - paste.\n"
                     << "4 - delete.\n"
                     << "5 - insert.\n"
                     << "Enter subcommand: ";
                cin >> subCommand;
                cin.ignore();

                switch (subCommand) {
                    case 1:
                        cout << "Choose number of symbols: ";
                        cin >> numberIndex;
                        myList.cutTextCursor(&myList, &buffer, numberIndex);
                        myList.printLinkedList(&myList);
                        break;
                    case 2:
                        cout << "Choose number of symbols: ";
                        cin >> numberIndex;
                        myList.copyTextCursor(&myList, &buffer, numberIndex);
                        buffer.printLinkedList(&buffer);
                        myList.printLinkedList(&myList);
                        pushCurrentCommand(&myList, &redoStack);
                        break;
                    case 3:
                        myList.pasteTextCursor(&myList, &buffer);
                        myList.printLinkedList(&myList);
                        pushCurrentCommand(&myList, &redoStack);
                        break;
                    case 4:
                        cout << "Choose number of symbols: ";
                        cin >> numberIndex;
                        myList.deleteTextCursor(&myList,numberIndex);
                        myList.printLinkedList(&myList);
                        pushCurrentCommand(&myList, &redoStack);
                        break;
                    case 5:
                        cout << "Enter text to insert: ";
                        getline(cin, input);
                        myList.insertTextCursor(&myList, input);
                        myList.printLinkedList(&myList);
                        pushCurrentCommand(&myList, &redoStack);
                        break;
                    default:
                        cout << "Invalid subcommand.\n";
                        break;
                }
                break;
            case 16:
                cp.encrypt();
                cout << "Enter number-key for encryption: ";
                cin >> key;
                cin.ignore();
                text = myList.linkedListToChar(&myList);
                if (text != nullptr) {
                    result = caesarCipher.encrypt(text, key);
                    cout << "Encrypted text: " << result << endl;
                    myList.charToLinkedList(&myList, result);
                } else {
                    cout << "Nothing to encrypt, the text is empty." << endl;
                }
                break;
            case 17:
                cp.decrypt();
                cout << "Enter number-key for decryption: ";
                cin >> key;
                cin.ignore();
                text = myList.linkedListToChar(&myList);
                if (text != nullptr) {
                    result = caesarCipher.decrypt(text, key);
                    cout << "Encrypted text: " << result << endl;
                    myList.charToLinkedList(&myList, result);
                } else {
                    cout << "Nothing to encrypt, the text is empty." << endl;
                }
                break;
            default:
                cout << "The command is not implemented.\n";
                break;
        }
    }
}