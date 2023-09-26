#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

struct Node {
    char value;
    Node* next;
};

struct LinkedList {
    Node* head;
    Node* current;
    Node* previous;
};

void addCharElement(LinkedList* list, string elements) {
    int i = 0;
    while (elements[i] != '\0') {
        if (list->head == nullptr) {
            list->head = new Node;
            list->head->value = elements[i];
            list->head->next = nullptr;
            list->current = list->head;
        } else {
            list->current->next = new Node;
            list->current->next->value = elements[i];
            list->current->next->next = nullptr;
            list->current = list->current->next;
        }
        i++;
    }
}

void addNewLine(LinkedList* list) {
    if (list->head == nullptr) {
        list->head = new Node;
        list->head->value = '\n';
        list->head->next = nullptr;
        list->current = list->head;
    } else {
        list->current->next = new Node;
        list->current->next->value = '\n';
        list->current->next->next = nullptr;
        list->current = list->current->next;
    }
}

void saveTextToFile(LinkedList* list, const string& fileName) {
    ofstream file(fileName, ios::app);
    Node* current = list->head;
    while (current != nullptr) {
        file.put(current->value);
        current = current->next;
    }
    file.close();
}

void loadTextFromFile(LinkedList* list, const string& fileName) {
    Node* current = list->head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    list->head = nullptr;
    list->current = nullptr;

    ifstream file(fileName);
    char block[100];
    int i = 0;

    while (file.getline(block, sizeof(block))) {
        while (block[i] != '\0') {
            if (list->head == nullptr) {
                list->head = new Node;
                list->head->value = block[i];
                list->head->next = nullptr;
                list->current = list->head;
            } else {
                list->current->next = new Node;
                list->current->next->value = block[i];
                list->current->next->next = nullptr;
                list->current = list->current->next;
            }
            i++;
        }
        list->current->next = new Node;
        list->current->next->value = '\n';
        list->current->next->next = nullptr;
        list->current = list->current->next;
        i = 0;
    }
    file.close();
}

void insertText(LinkedList* list, int lineIndex, int symbolIndex, string text) {
    if (lineIndex == 0 && symbolIndex == 0) {
        list->current = list->head;
        addCharElement(list, text);
    } else {
        list->current = list->head;
        Node* previous = nullptr;
        int currentLine = 0;
        int currentSymbol = 0;

        while (currentLine < lineIndex) {
            previous = list->current;
            list->current = previous->next;
            if (list->current == nullptr) {
                cout << "\nIncorrect line index.\n";
                break;
            }
            if (list->current->value == '\n') {
                currentLine++;
            }
        }

        while (currentSymbol < symbolIndex) {
            previous = list->current;
            list->current = previous->next;
            if (list->current == nullptr) {
                cout << "\nIncorrect symbol index.\n";
                break;
            }
            currentSymbol++;
        }

        Node* temp = nullptr;
        temp = list->current->next;
        int i = 0;

        while (text[i] != '\0') {
            list->current->next = new Node;
            list->current->next->value = text[i];
            list->current->next->next = nullptr;
            list->current = list->current->next;
            i++;
        }
        list->current->next = temp;
    }
}

void searchInText(LinkedList* list, string text) {
    Node* current = list->head;
    int lineIndex = 0;
    int symbolIndex = 1;
    int textIndex = 0;
    int checkLength = 0;

    while (current != nullptr) {
        if (current->value == '\n') {
            lineIndex++;
            symbolIndex = 0;
            textIndex = 0;
            checkLength = 0;
        } else if (current->value == text[textIndex]){
            textIndex++;
            checkLength++;
            if (text[textIndex] == '\0') {
                cout << "line " << lineIndex << " symbol " << symbolIndex - checkLength << "; ";
                textIndex = 0;
                checkLength = 0;
            }
        } else if (current->value == text[0]) {
            textIndex = 1;
            checkLength = 1;
        } else {
            textIndex = 0;
            checkLength = 0;
        }
        current = current->next;
        symbolIndex++;
    }
}

void printLinkedList(LinkedList* list) {
    Node* current = list->head;
    while (current != nullptr) {
        cout << current->value;
        current = current->next;
    }
    cout << "\n";
}

void deleteText(LinkedList* list, int lineIndex, int startIndex, int number){
    list->current = list->head;
    list->previous = nullptr;
    int currentLine = 0;
    int currentSymbol = 0;
    int currentNumber = 0;

    if (lineIndex == 0 && startIndex == 0) {
        while (currentNumber != number) {
            list->current = list->current->next;
            currentNumber++;
        }
        list->head = list->current;
    } else {
        while (currentLine < lineIndex) {
            list->previous = list->current;
            list->current = list->current->next;
            if (list->current == nullptr) {
                cout << "\nIncorrect line index.\n";
                break;
            }
            if (list->current->value == '\n') {
                currentLine++;
            }
        }

        while (currentSymbol < startIndex) {
            list->previous = list->current;
            list->current = list->current->next;
            if (list->current == nullptr) {
                cout << "\nIncorrect symbol index.\n";
                break;
            }
            currentSymbol++;
        }

        while(currentNumber != number)
        {
            list->previous->next = list->current->next;
            list->current = list->previous->next;
            currentNumber++;
        }
    }
}

void pushCurrentCommand(LinkedList* list, stack<LinkedList>* stack) {
    if(stack->size() > 3){
        stack->pop();
    }
    LinkedList newList{};
    newList.head = nullptr;
    newList.current = nullptr;
    newList.previous = nullptr;
    Node* current = list->head;

    while (current != nullptr) {
        if (newList.head == nullptr) {
            newList.head = new Node;
            newList.head->value = current->value;
            newList.head->next = nullptr;
            newList.current = newList.head;
        } else {
            newList.current->next = new Node;
            newList.current->next->value = current->value;
            newList.current->next->next = nullptr;
            newList.current = newList.current->next;
        }
        current = current->next;
    }
    stack->push(newList);
}

LinkedList undo(stack<LinkedList>* stack) {
    if (stack->size() > 1)
    {
        stack->pop();
        stack->pop();
        LinkedList newMyList = stack->top();
        stack->pop();
        return newMyList;
    } else {
        cout << "Nothing to undo.";
        return stack->top();
    }
}

void cutText(LinkedList* list, int lineIndex, int startIndex, int number, LinkedList* buffer){
    buffer->head = nullptr;
    buffer->current = nullptr;
    buffer->previous = nullptr;

    list->current = list->head;
    list->previous = nullptr;
    int currentLine = 0;
    int currentSymbol = 0;
    int currentNumber = 0;

    if (lineIndex == 0 && startIndex == 0) {
        while (currentNumber != number) {
            list->current = list->current->next;
            currentNumber++;
        }
        list->head = list->current;
    } else {
        while (currentLine < lineIndex) {
            list->previous = list->current;
            list->current = list->current->next;
            if (list->current == nullptr) {
                cout << "\nIncorrect line index.\n";
                break;
            }
            if (list->current->value == '\n') {
                currentLine++;
            }
        }

        while (currentSymbol < startIndex) {
            list->previous = list->current;
            list->current = list->current->next;
            if (list->current == nullptr) {
                cout << "\nIncorrect symbol index.\n";
                break;
            }
            currentSymbol++;
        }

        while(currentNumber != number)
        {
            if (buffer->head == nullptr) {
                buffer->head = new Node;
                buffer->head->value = list->current->value;
                buffer->head->next = nullptr;
                buffer->current = buffer->head;
            } else {
                buffer->current->next = new Node;
                buffer->current->next->value = list->current->value;
                buffer->current->next->next = nullptr;
                buffer->current = buffer->current->next;
            }
            list->previous->next = list->current->next;
            list->current = list->previous->next;
            currentNumber++;
        }
    }
}

void copyText(LinkedList* list, int lineIndex, int startIndex, int number, LinkedList* buffer){
    buffer->head = nullptr;
    buffer->current = nullptr;
    buffer->previous = nullptr;

    list->current = list->head;
    list->previous = nullptr;
    int currentLine = 0;
    int currentSymbol = 0;
    int currentNumber = 0;

    while (currentLine < lineIndex) {
        list->previous = list->current;
        list->current = list->current->next;
        if (list->current == nullptr) {
            cout << "\nIncorrect line index.\n";
            break;
        }
        if (list->current->value == '\n') {
            currentLine++;
        }
    }

    while (currentSymbol < startIndex) {
        list->previous = list->current;
        list->current = list->current->next;
        if (list->current == nullptr) {
            cout << "\nIncorrect symbol index.\n";
            break;
        }
        currentSymbol++;
    }

    while(currentNumber != number)
    {
        if (buffer->head == nullptr) {
            buffer->head = new Node;
            buffer->head->value = list->current->value;
            buffer->head->next = nullptr;
            buffer->current = buffer->head;
        } else {
            buffer->current->next = new Node;
            buffer->current->next->value = list->current->value;
            buffer->current->next->next = nullptr;
            buffer->current = buffer->current->next;
        }
        list->current = list->current->next;
        currentNumber++;
    }
}

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

    while (true) {
        system("clear");

        // cout << "\nAll commands:\n1-enter new text.\n2-start the new line.\n3-saving the information to your file."
                "\n4-loading the information from your file.\n5-print the current text to console.\n6-insert the text "
                "by line and symbol index.\n7-search by word.\n8-delete command.\n9-undo command.\n10-redo command."
                "\n11-cut command.\n12-paste command.\n13-copy command.\n";

        cout << "Choose the command: ";
        cin >> command;
        switch (command) {
            case 1:
                cin.ignore(); // clear the input buffer
                cout << "Enter text to append (please, no more than 100 characters): ";
                getline(cin, input);
                addCharElement(&myList, input);
                printLinkedList(&myList);
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 2:
                addNewLine(&myList);
                cout << "New line is started.\n";
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 3:
                cout << "Enter the file name for saving: ";
                cin >> fileName;
                saveTextToFile(&myList, fileName);
                cout << "Text has been saved successfully.\n";
                break;
            case 4:
                cout << "Enter the file name for loading: ";
                cin >> fileName;
                if (!fileName.empty()) {
                    loadTextFromFile(&myList, fileName);
                    cout << "Text has been loaded successfully.\n";
                } else {
                    cout << "Choose command 3.\n";
                }
                break;
            case 5:
                printLinkedList(&myList);
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 6:
                cout << "Choose line and index: ";
                cin >> lineIndex >> symbolIndex;
                cin.ignore(); // clear the input buffer
                cout << "Enter text to insert (please, no more than 100 characters): ";
                getline(cin, input);
                insertText(&myList, lineIndex, symbolIndex, input);
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 7:
                cin.ignore(); // clear the input buffer
                cout << "Enter text to search: ";
                getline(cin, searchText);
                cout << "Text is present in this position: ";
                searchInText(&myList, searchText);
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 8:
                cout << "Choose line, index and number of symbols: ";
                cin >> lineIndex >> startIndex >> numberIndex;
                deleteText(&myList, lineIndex, startIndex, numberIndex);
                cout << "Text has been deleted successfully.\n";
                pushCurrentCommand(&myList, &undoStack);
                break;
            case 9:
                myList = undo(&undoStack);
                printLinkedList(&myList);
                cout << "Undo completed.\n";
                break;
            case 10:
                // some code will be here
                cout << "Redo completed.\n";
                break;
            case 11:
                cout << "Choose line and index and number of symbols: ";
                cin >> lineIndex >> startIndex >> numberIndex;
                cutText(&myList, lineIndex, startIndex, numberIndex, &buffer);
                //printLinkedList(&buffer);
                break;
            case 12:
                cout << "Choose line and index: ";
                cin >> lineIndex >> startIndex;
                break;
            case 13:
                cout << "Choose line and index and number of symbols: ";
                cin >> lineIndex >> startIndex >> numberIndex;
                copyText(&myList, lineIndex, startIndex, numberIndex, &buffer);
                printLinkedList(&buffer);
                printLinkedList(&myList);
                break;
            case 14:
                cout << "The command 14.\n";
                break;
            default:
                cout << "The command is not implemented.\n";
                break;
        }
    }
}