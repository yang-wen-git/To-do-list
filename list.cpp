// Author: William Marklynn/Yang Wen-li
// Desc: This file contains extension code to class Todolist
//       defined in 'list.h'. Specifically, method definitions.
//       These include the default constructor, add, check, and
//       uncheck methods. The methods can be called to modify the to
//       do list/the linked list of nodes pointed by TodoList member
//       'head'.

#include "list.h"
#include <iostream>

// desc: Default constructor method for instance of class 'TodoList'
// pre:  None
// post: Default instance of class 'TodoList' is constructed with its size
//       initialized to 0 and head pointing to null as linked list has
//       yet to be created
TodoList::TodoList() {
    size = 0;
    head = nullptr;
}

// desc: copy constructor of class 'TodoList' which constructs an independent
//       copy of instance 'other' into a new instance
// pre:  - 'other' is an instance of class TodoList and follows all invariants
//         of the class (valid members head and size)
// post: - state of 'other' copied into a newly constructed instance
//       - does not leak memory
//       - does not access memory out of bounds
//       - does not dereference null pointers
//       - does not access uninitialized values
TodoList::TodoList(TodoList const &other) {
    Node *iter = other.head;
    size = other.size;
    head = new Node;
    Node *copy_iter = head;
    while (iter != nullptr) {
        copy_iter->title = iter->title;
        copy_iter->entry = iter->entry;
        copy_iter->checked = iter->checked;
        if (iter->next == nullptr) {
            copy_iter->next = nullptr;
        } else {
            copy_iter->next = new Node;
        }
        iter = iter->next;
        copy_iter = copy_iter->next;
    }
}

// desc: overloaded assignment operator of class 'TodoList' which assigns the
//       state of an instance 'other' to the state of another already
//       constructed instance
// pre:  - instance of TodoList follows all invariants of the class
//       - instance 'other' follows all invariants of the class
//       - instance 'other' is not empty
//       - linked list pointed by this instance's head member must be
//         deallocated
// post: - 'this' instance is now an independent copy of 'other' instance
//       - does not leak memory
//       - does not access memory out of bounds
//       - does not access/dereference null pointers or uninitialized values
void TodoList::operator=(TodoList const &other) {
    if (other.head != nullptr) {
        deallocate_list();
        Node *iter = other.head;
        size = other.size;
        head = new Node;
        Node *copy_iter = head;
        while (iter != nullptr) {
            copy_iter->title = iter->title;
            copy_iter->entry = iter->entry;
            copy_iter->checked = iter->checked;
            if (iter->next == nullptr) {
                copy_iter->next = nullptr;
            } else {
                copy_iter->next = new Node;
            }
            iter = iter->next;
            copy_iter = copy_iter->next;
        }
    }
}

// desc: Frees and deallocated all dynamically allocated nodes in the
//       linked list. Works in conjunction with class's overloaded
//       assignment operator and destructor.
// pre:  Instance of TodoList follows all invariants of the class
// post: - All dynamically allocated nodes in the linked list freed
//       - Does not access memory out of bounds
//       - Does not dereference null pointers;
//       - Does not leak memory
void TodoList::deallocate_list() {
    Node *iter = head;
    while (iter != nullptr) {
        head = iter->next;
        delete iter;
        iter = head;
    }
}

// desc: Adds a new 'to-do' to the TodoList/a new node to the linked list
// pre:  - Instance of TodoList follows all invariants of the class
//       - parameters 'name' and 'text' are of type strings
// post: - New node added to the TodoList/new node added to the linked list
//       - Instance's member 'size' incremented to reflect new size of
//         the instance's size
//       - Alphabetic order of the linked list preserved
//       - Does not access memory out of bounds
//       - Does not dereference null pointers
void TodoList::add(std::string name, std::string text) {
    size += 1;
    Node *temp = new Node;
    temp->title = name;
    temp->entry = text;
    temp->checked = false;
    temp->next = nullptr;
    if (head == nullptr) {
        head = temp;
    } else if (temp->title < head->title) {
        Node *ph = head;
        head = temp;
        head->next = ph;
        // if head node has element 'title', that node's
        // 'entry' will be overwritten with temp's 'entry'
    } else if (temp->title == head->title) {
        head->entry = temp->entry;
        head->checked = false;
        delete temp;
    } else {
        Node *iter = head;
        if (iter->next == nullptr && iter->title < name) {
            iter->next = temp;
        } else {
            while (iter->next != nullptr && iter->title < name) {
                if (iter->next->title > name) {
                    Node *ph = iter->next;
                    iter->next = temp;
                    temp->next = ph;
                } else if (iter->next->next == nullptr &&
                           iter->next->title < name) {
                    iter->next->next = temp;
                    iter = iter->next;
                    // if there exists a middle node with element 'title',
                    // that node's entry will be overwriten with temp's 'entry'
                } else if (iter->next->title == name) {
                    iter->next->entry = temp->entry;
                    iter->next->checked = false;
                    delete temp;
                }
                iter = iter->next;
            }
        }
    }
    temp = nullptr;
}

// desc: removes node containing element 'target'/removes to do of title
//       'target'
// pre:  - Instance of TodoList follows all invariants of the class
//       - string 'target' is of type string
//       - node containing 'target' exists within the list
// post: - node/todo containing string 'target' removed from list
//       - alphabetic order of the list preserved
//       - does not leak memory
//       - does not access memory out of bounds
//       - does not dereference null pointers
//       - does not access uninitialized values
void TodoList::remove(std::string target) {
    // bool method 'target_exists' check if node containing string 'target'
    // exists before running main method body
    if (target_exists(target)) {
        size -= 1;
        if (head->title == target) {
            Node *temp = head;
            head = head->next;
            delete temp;
        } else {
            Node *iter = head;
            while (iter != nullptr && iter->title != target) {
                if (iter->next->title == target) {
                    Node *temp = iter->next;
                    iter->next = temp->next;
                    delete temp;
                    iter = nullptr;
                } else {
                    iter = iter->next;
                }
            }
        }
    }
}
// desc: Sets the member 'checked' of the node in the linked list that
//       contains the title of 'target' to true. In other words, checking
//       the item in the to do list that contain the parameter target
// pre:  - 'target' is a string
//       - Instance of TodoList follows all invariants of the class
//       - Instance member 'head' is not pointing to null
// post: - Node containing 'target' have their member 'checked' set
//         to true
//       - alphabetic order of the list preserved
//       - Does not access memory out of bounds
//       - Does not dereference null pointers
void TodoList::check(std::string target) {
    Node *iter = head;
    while (iter != nullptr) {
        if (iter->title == target) {
            iter->checked = true;
        }
        iter = iter->next;
    }
}

// desc: Sets the member 'checked' of the node in the linked list that
//       contains the title of 'target' to false. In other words, unchecking
//       the item in the to do list that contain the parameter 'target'.
//       Reverses effect of 'check' method.
// pre:  - 'target' is a string
//       - Instance of TodoList follows all invariants of the class
//       - Instance member 'head' is not pointing to null
// post: - Node containing 'target' have their member 'checked' set
//         to false
//       - alphebatic order of the list preserved
//        - Does not access memory out of bounds
//        - Does not dereference null pointers
void TodoList::uncheck(std::string target) {
    Node *iter = head;
    while (iter != nullptr) {
        if (iter->title == target) {
            iter->checked = false;
        }
        iter = iter->next;
    }
}

// desc: Prints the title and the contents of each node in the
//       linked list pointed by instance member 'head'. In other words,
//       printing each title and item of each to do list line by line.
// pre:  - Instance of TodoList follows all invariants of the class
// post: - Title and contents of each node in the linked list is printed
//         out line by line
//       - Does not access memory out of bounds
//       - Does not dereference null pointers
void TodoList::print_list() {
    Node *iter = head;
    while (iter != nullptr) {
        if (iter->checked) {
            std::cout << "[X]    " << iter->title << ' ' << iter->entry
                      << std::endl;
        } else {
            std::cout << "[ ]    " << iter->title << ' ' << iter->entry
                      << std::endl;
        }
        iter = iter->next;
    }
}

// desc: Checks if a node containing string 'target' exists within the
//       list/to do list. Returns true if exists, returns false otherwise
//       Works in conjunction with 'remove' method
// pre:  - instance of TodoList follows all invariants of the class
//       - 'target' is of type string
// post: - does not access memory out of bounds
//       - does not dereference null pointers
//       - does not access uninitialized values
bool TodoList::target_exists(std::string target) {
    Node *iter = head;
    while (iter != nullptr) {
        if (target == iter->title) {
            return true;
        }
        iter = iter->next;
    }
    return false;
}

// desc: Destructor method of class TodoList
// pre:  - instance of class TodoList follows all invariants of the class
// post: - all dynamically allocated nodes in the linked list are freed
//       - class instance destructed
//       - does not leak memory
//       - does not access memory out of bounds
//       - does not dereference null pointers
TodoList::~TodoList() {
    deallocate_list();
}
