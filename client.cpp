// Author: William Marklynn/Yang Wen-li
// Desc: This file contains code that creates a to do list which the user
//       can add to, check and uncheck the contents of the list.
//       This is done by first creating an default instance of the Todolist
//       class from 'list.h'. The to do list is created using a linked list
//       composed of dynamically allocated instances of the struct 'Node',
//       also detailed in 'list.h'. The user will then be prompted to type
//       a one-line white-space separated input which, upon a valid input,
//       will be split using stringstream and assigned to variables, where the
//       appropriate method of the class will be a called, depending on the
//       command the user types. For instance, if the user input "add new
//       to do", 'add' will be assigned to string command by which the program
//       can determine which method of the class to call (in this case 'add'),
//       'new' will be assigned to 'title', and 'to do' will be assigned to
//       'entry'. Although, 'to do' is whitespace separated, using
//       the 'getline' method from the std library, everything after
//       'title'  will be assigned to the last variable
//       'entry'. If there has been a bad input e.g invalid command,
//       the user will be prompted to input again. User can keep modifying
//       until they input 'quit', after which bool value 'done', which keeps
//       while loop running, will be set to false, program exits loop, and
//       destructor method of the class is called to destruct the instance of
//       the class. Details of the class and its methods can be found in
//       'list.h' and 'list.cpp'

#include "list.h"
#include <iostream>
#include <sstream>
#include <string>

int main() {
    // instance of TodoList classes constructed
    TodoList user_list;
    TodoList saved_state;

    std::string command_list[7] = {
        "quit", "add", "remove", "check", "uncheck", "save", "load"
    };
    std::string line;
    bool done = false;
    bool bad_input = false;

    // while loop to keep editing process going until user inputs 'quit'
    // which sets done = true
    while (!done && std::getline(std::cin, line)) {
        bool command_exists = false;
        std::stringstream stream(line);
        std::string command;
        std::string title;
        std::string entry;
        stream >> command;
        // for loop checks 'command' against each element in array
        // 'command_list' to check if command inputted is a valid comment
        for (int i = 0; i < 7; i++) {
            if (command == command_list[i]) {
                command_exists = true;
            }
        }
        // if command exists, main body runs
        if (command_exists) {
            // program only ends if user inputs 'quit'
            if (command == "quit" || command == "save" || command == "load") {
                // friendly error message is outputted if more than 1 string
                // were inputted for these commands
                if (stream >> title) {
                    std::cout << std::endl;
                    std::cout << "ERROR: Too many arguments." << std::endl;
                    bad_input = true;
                } else if (command == "quit") {
                    done = true;
                } else if (command == "save") {
                    saved_state = user_list;
                } else if (command == "load") {
                    user_list = saved_state;
                }
            } else if (stream >> title) {
                // only command "add" can have more than two string input
                if (command == "add") {
                    if (std::getline(stream, entry)) {
                        user_list.add(title, entry);
                    } else {
                        // no description to do
                        user_list.add(title, " ");
                    }
                } else if (command == "check" || command == "uncheck" ||
                           command == "remove") {
                    // error message if more than 2 inputs were provided
                    if (stream >> entry) {
                        std::cout << std::endl;
                        std::cout << "ERROR: Too many arguments. " << std::endl;
                        bad_input = true;
                    } else {
                        if (command == "check") {
                            user_list.check(title);
                        } else if (command == "uncheck") {
                            user_list.uncheck(title);
                        } else if (command == "remove") {
                            user_list.remove(title);
                        }
                    }
                }
            } else {
                // if second word to be assigned to 'title' is missing,
                // friendly error message is outputed
                std::cout << std::endl;
                std::cout << "ERROR: No name given. " << std::endl;
                bad_input = true;
            }
        } else {
            // executes if user types in a command that is not one of the
            // 7 commands. Friendly error message outputted
            std::cout << std::endl;
            bad_input = true;
            std::cout << "ERROR: No such command. " << std::endl;
        }
        // current to do list and prompt again if not done or if
        // there has been a bad input
        if (bad_input || !done) {
            std::cout << std::endl;
            bad_input = false;
            user_list.print_list();
        }
    }
    return 0;
}
