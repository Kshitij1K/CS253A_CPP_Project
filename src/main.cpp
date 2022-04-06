#include <state_machine.hpp>

int main (int argc, char** argv) {
    std::cout << "Welcome to PK Kelkar Library!\n";
    
    Library library;
    library.changeState(&LoginState::getInstance());


    while (1) {
        if (library.current_state_ == NULL) break;
        library.current_state_->run(&library);
    }

    std::cout << "Thanks for using this software. Exiting now.\n";

    return 0;
}