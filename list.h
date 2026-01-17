// Author: William Marklynn/Yang Wen-li
// Desc: This file contains the declaration of class "TodoList" and its
//       variables and methods. Variables and methods are defined and
//       detailed in 'list.cpp'. This .h file also contains struct Node which
//       the to do list in the form of linked list will be composed of
// Invariants: member 'head' is either pointing at null or at an instance 
//             of struct 'Node'. Member 'size' is an integer that reflects
//             the number of nodes in the linked list. 
#include <iostream>

#ifndef LIST_H
#define LIST_H
struct Node {
    std::string title;
    std::string entry;
    bool checked;
    Node *next;
};

class TodoList {
    private:
    int size;
    Node* head;

    public:
    TodoList();
    TodoList(TodoList const &other);
    void operator=(TodoList const &other);
    void deallocate_list();
    void add(std::string name, std::string text);
    void remove(std::string target);
    void check(std::string target);
    void uncheck(std::string target);
    void print_list();
    bool target_exists(std::string target);
    ~TodoList();
};
#endif
