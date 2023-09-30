#include <stack>

class LinkedList;

void pushCurrentCommand(LinkedList* list, std::stack<LinkedList>* stack);
LinkedList undo(std::stack<LinkedList>* stack, std::stack<LinkedList>* stack2);
LinkedList redo(std::stack<LinkedList>* stack);
