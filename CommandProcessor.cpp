#include "CommandProcessor.h"
#include "Stack.h"
#include <iostream>
using namespace std;

CommandProcessor::CommandProcessor() {
    myList.head = nullptr;
    myList.current = nullptr;
}

void CommandProcessor::append() {
    cin.ignore(); // clear the input buffer
    cout << "Enter text to append: ";
    getline(cin, input);
    myList.addCharElement(&myList, input);
    myList.printLinkedList(&myList);
    pushCurrentCommand(&myList, &undoStack);
}

void CommandProcessor::newLine() {
    myList.addNewLine(&myList);
    cout << "New line is started.\n";
    pushCurrentCommand(&myList, &undoStack);
}

void CommandProcessor::printText(){
    myList.printLinkedList(&myList);
    pushCurrentCommand(&myList, &undoStack);
}

void CommandProcessor::saveFile() {
    cout << "Enter the file name/path for saving: ";
    cin >> fileName;
    myList.saveTextToFile(&myList, fileName);
    cout << "Text has been saved successfully.\n";
}

void CommandProcessor::loadFile() {
    cout << "Enter the file name/path for loading: ";
    cin >> fileName;
    if (!fileName.empty()) {
        myList.loadTextFromFile(&myList, fileName);
        cout << "Text has been loaded successfully.\n";
    } else {
        cout << "Choose command 3.\n";
    }
}

void CommandProcessor::insert(){
    cout << "Choose line and index: ";
    cin >> lineIndex >> symbolIndex;
    cin.ignore(); // clear the input buffer
    cout << "Enter text to insert: ";
    getline(cin, input);
    myList.insertText(&myList, lineIndex, symbolIndex, input);
    pushCurrentCommand(&myList, &undoStack);
}

void CommandProcessor::search() {
    cin.ignore(); // clear the input buffer
    cout << "Enter text to search: ";
    getline(cin, searchText);
    cout << "Text is present in this position: ";
    myList.searchInText(&myList, searchText);
    pushCurrentCommand(&myList, &undoStack);
}

void CommandProcessor::deletet() {
    cout << "Choose line, index and number of symbols: ";
    cin >> lineIndex >> startIndex >> numberIndex;
    myList.deleteText(&myList, lineIndex, startIndex, numberIndex);
    cout << "Text has been deleted successfully.\n";
    pushCurrentCommand(&myList, &undoStack);
}

void CommandProcessor::undo() {
    myList = ::undo(&undoStack, &redoStack);
    myList.printLinkedList(&myList);
    pushCurrentCommand(&myList, &redoStack);
    cout << "Undo completed.\n";
}

void CommandProcessor::redo() {
    myList = ::redo(&redoStack);
    myList.printLinkedList(&myList);
    cout << "Redo completed.\n";
}

void CommandProcessor::cut() {
    cout << "Choose line and index and number of symbols: ";
    cin >> lineIndex >> startIndex >> numberIndex;
    myList.cutText(&myList, lineIndex, startIndex, numberIndex, &buffer);
    myList.printLinkedList(&buffer);
    myList.printLinkedList(&myList);
}

void CommandProcessor::paste() {
    cout << "Choose line and index: ";
    cin >> lineIndex >> startIndex;
    myList.pasteText(&myList, lineIndex, startIndex, &buffer);
    myList.printLinkedList(&myList);
}

void CommandProcessor::copy() {
    cout << "Choose line and index and number of symbols: ";
    cin >> lineIndex >> startIndex >> numberIndex;
    myList.copyText(&myList, lineIndex, startIndex, numberIndex, &buffer);
    myList.printLinkedList(&myList);
}

void CommandProcessor::replacement() {
    cout << "Choose line and index: ";
    cin >> lineIndex >> startIndex;
    cin.ignore();
    cout << "Write text: ";
    getline(cin, replText);
    myList.replacementText(&myList, lineIndex, startIndex, replText);
    myList.printLinkedList(&myList);
}

void CommandProcessor::cursor() {
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
}

void CommandProcessor::encrypt() {
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
}

void CommandProcessor::decrypt() {
    cout << "Enter number-key for decryption: ";
    cin >> key;
    cin.ignore();
    text = myList.linkedListToChar(&myList);
    if (text != nullptr) {
        result = caesarCipher.decrypt(text, key);
        cout << "Decrypted text: " << result << endl;
        myList.charToLinkedList(&myList, result);
    } else {
        cout << "Nothing to decrypt, the text is empty." << endl;
    }
}
