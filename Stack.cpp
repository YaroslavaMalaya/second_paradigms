#include "Stack.h"
#include "LinkedList.h"

void pushCurrentCommand(LinkedList* list, std::stack<LinkedList>* stack) {
    LinkedList newList{};
    newList.head = nullptr;
    newList.current = nullptr;
    newList.previous = nullptr;
    LinkedList::Node* current = list->head;

    while (current != nullptr) {
        if (newList.head == nullptr) {
            newList.head = new LinkedList::Node;
            newList.head->value = current->value;
            newList.head->next = nullptr;
            newList.current = newList.head;
        } else {
            newList.current->next = new LinkedList::Node;
            newList.current->next->value = current->value;
            newList.current->next->next = nullptr;
            newList.current = newList.current->next;
        }
        current = current->next;
    }
    stack->push(newList);
}

LinkedList undo(std::stack<LinkedList>* stack, std::stack<LinkedList>* stack2) {
    if (stack->size() > 2) {
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

LinkedList redo(std::stack<LinkedList>* stack) {
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
