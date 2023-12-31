#include <iostream>
#include <fstream>
#include <stack>

using namespace std;

class LinkedList {
public:
    class Node {
    public:
        char value;
        Node* next;
    };

public:
    Node* head;
    Node* current;
    Node* previous;

    void addCharElement(LinkedList* list, string elements);
    void addNewLine(LinkedList* list);
    void saveTextToFile(LinkedList* list, const string& fileName);
    void loadTextFromFile(LinkedList* list, const string& fileName);
    void insertText(LinkedList* list, int lineIndex, int symbolIndex, string text);
    void searchInText(LinkedList* list, string text);
    void printLinkedList(LinkedList* list);
    void deleteText(LinkedList* list, int lineIndex, int startIndex, int number);
    void cutText(LinkedList* list, int lineIndex, int startIndex, int number, LinkedList* buffer);
    void copyText(LinkedList* list, int lineIndex, int startIndex, int number, LinkedList* buffer);
    void pasteText(LinkedList* list, int lineIndex, int startIndex, LinkedList* buffer);
    void replacementText(LinkedList *list, int lineIndex, int startIndex, string buffer);

    void moveToPosition(LinkedList* list, int lineIndex, int startIndex);
    void cutTextCursor(LinkedList* list, LinkedList* buffer, int number);
    void copyTextCursor(LinkedList* list, LinkedList* buffer, int number);
    void pasteTextCursor(LinkedList* list, LinkedList* buffer);
    void deleteTextCursor(LinkedList* list, int number);
    void insertTextCursor(LinkedList* list, string text);
    char* linkedListToChar(LinkedList* list);
    void charToLinkedList(LinkedList* list, char* data);
};