#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stack>

void LinkedList::addCharElement(LinkedList* list, string elements) {
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

void LinkedList::addNewLine(LinkedList* list) {
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

void LinkedList::saveTextToFile(LinkedList* list, const string& fileName) {
    ofstream file(fileName, ios::app);
    Node* current = list->head;
    while (current != nullptr) {
        file.put(current->value);
        current = current->next;
    }
    file.close();
}

void LinkedList::loadTextFromFile(LinkedList* list, const string& fileName) {
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

void LinkedList::insertText(LinkedList* list, int lineIndex, int symbolIndex, string text) {
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

void LinkedList::searchInText(LinkedList* list, string text) {
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

void LinkedList::printLinkedList(LinkedList* list) {
    Node* current = list->head;
    while (current != nullptr) {
        cout << current->value;
        current = current->next;
    }
    cout << "\n";
}

void LinkedList::deleteText(LinkedList* list, int lineIndex, int startIndex, int number){
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

void LinkedList::pushCurrentCommand(LinkedList* list, stack<LinkedList>* stack) {
//    if(stack->size() > 3){
//        stack->pop();
//    }
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

LinkedList LinkedList::undo(stack<LinkedList>* stack, std::stack<LinkedList>* stack2) {
    if (stack->size() > 1) {
        LinkedList list1 = stack->top();
        stack->pop();
        pushCurrentCommand(&list1, stack2);
        LinkedList list2 = stack->top();
        stack->pop();
        pushCurrentCommand(&list2, stack2);
        LinkedList list3 = stack->top();
        stack->pop();
        pushCurrentCommand(&list3, stack2);
        LinkedList newMyList = stack->top();
        stack->pop();
        return newMyList;
    } else {
        cout << "Nothing to undo.";
        return stack->top();
    }
}

void LinkedList::cutText(LinkedList* list, int lineIndex, int startIndex, int number, LinkedList* buffer){
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

void LinkedList::copyText(LinkedList* list, int lineIndex, int startIndex, int number, LinkedList* buffer){
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

void LinkedList::pasteText(LinkedList* list, int lineIndex, int startIndex, LinkedList* buffer) {
    list->current = list->head;
    if (lineIndex == 0 && startIndex == 0) {
        buffer->current->next = list->current;
        list->head = buffer->head;
    } else {
        Node *previous = nullptr;
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

        while (currentSymbol < startIndex) {
            previous = list->current;
            list->current = previous->next;
            if (list->current == nullptr) {
                cout << "\nIncorrect symbol index.\n";
                break;
            }
            currentSymbol++;
        }

        Node *temp = nullptr;
        temp = list->current->next;
        buffer->current->next = temp;
        list->current->next = buffer->head;
    }
}

LinkedList LinkedList::redo(stack<LinkedList>* stack) {
    if (!stack->empty()) {
        stack->pop();
        stack->pop();
        stack->pop();
        LinkedList redoList = stack->top();
        stack->pop();
        return redoList;
    } else {
        cout << "Nothing to redo.";
        return stack->top();
    }
}