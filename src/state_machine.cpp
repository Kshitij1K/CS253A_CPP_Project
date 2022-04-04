#include <state_machine.hpp>

std::vector<std::string> State::getSplitStrings(std::string full_string) {
    size_t position = 0;
    std::vector<std::string> string_list;

    while ((position = full_string.find(" ")) != std::string::npos) {
        string_list.push_back(full_string.substr(0, position));
        full_string.erase(0, position + 1);
    }

    string_list.push_back(full_string);

    return string_list;
}






State& LoginState::getInstance() {
  static LoginState singleton;
  return singleton;
}

void LoginState::enter(Library* library) {
    std::cout << "LOGIN PORTAL\n";
    usernames = {"stud", "prof", "lib"};
    passwords = {"abc", "123", "def"};
    types = {"1", "2", "3"};
}

void LoginState::run(Library* library) {
    std::cout << "Please enter the command you wish to execute."
                 "Available commands are \n"
                 "1) LOGIN <username> <password> (Enter your username and password without the angular brackets, and hit enter to login)\n"
                 "2) EXIT (Will exit the software)\n";
    
    std::string command;
    std::getline(std::cin, command);

    std::vector<std::string> split_command = getSplitStrings(command);

    if (split_command.size() != 3 && split_command.size() != 1) {
        std::cout << "Incorrect Command Entered! Please enter the correct command, according to instructions.\n";
        return;
    }

    if (split_command.size() == 1) {
        if (split_command[0] == "EXIT") {
            library->current_state_ = NULL;
            return;
        }
        std::cout << "Incorrect Command Entered! Please enter the correct command, according to instructions.\n";
        return;
    }

    if (split_command.size() == 3) {
        if (split_command[0] == "LOGIN") {
            entered_username = split_command[1];
            std::string entered_password = split_command[2];
            auto username_iter = std::find(usernames.begin(), usernames.end(), entered_username);

            if (username_iter == usernames.end()) {
                std::cout << "No such user exists! Please try again.\n";
                return;
            } 

            long long int index = username_iter-usernames.begin();

            if (passwords[index] != entered_password) {
                std::cout << "Password Incorrect! Please try again.\n";
                return;
            }



            switch (stoi(types[index]))
            {
            case 1:
                library->changeState(&StudentAccessState::getInstance());
                return;
            
            case 2:
                library->changeState(&ProfessorAccessState::getInstance());
                // current_state_ = std::make_shared<ProfessorAccessState>(current_state_);
                return;

            case 3:
                library->changeState(&LibrarianAccessState::getInstance());
                // current_state_ = std::make_shared<LibrarianAccessState>(current_state_);
                return;
            }

        }

    }

}   

void LoginState::exit(Library* library) {
    library->username = entered_username;
}

State& StudentAccessState::getInstance() {
  static StudentAccessState singleton;
  return singleton;
}

void StudentAccessState::enter(Library* library) {
    std::cout << "Student Portal\n";
}

void StudentAccessState::run(Library* library) {
    library->current_state_ = NULL;
}

void StudentAccessState::exit(Library* library) {}

State& ProfessorAccessState::getInstance() {
  static ProfessorAccessState singleton;
  return singleton;
}

void ProfessorAccessState::enter(Library* library) {
    std::cout << "Professor Portal\n";
}

void ProfessorAccessState::run(Library* library) {
    library->current_state_ = NULL;
}

void ProfessorAccessState::exit(Library* library) {}

State& LibrarianAccessState::getInstance() {
  static LibrarianAccessState singleton;
  return singleton;
}

void LibrarianAccessState::enter(Library* library) {
    std::cout << "Librarian Portal\n";
}

void LibrarianAccessState::run(Library* library) {
    library->current_state_ = NULL;
}

void LibrarianAccessState::exit(Library* library) {}