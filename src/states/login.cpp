#include <state_machine.hpp>

State& LoginState::getInstance() {
  static LoginState singleton;
  return singleton;
}

void LoginState::enter(Library* library) {
    std::cout << "LOGIN PORTAL\n";
    // usernames = {"stud", "prof", "lib"};
    // passwords = {"abc", "123", "def"};
    // types = {"1", "2", "3"};
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
            std::string entered_username = split_command[1];
            std::string entered_password = split_command[2];
            // auto username_iter = std::find(library->user_database..begin(), usernames.end(), entered_username);

            // auto username_found = library->user_database.searchUserByUsername(entered_username);

            if (!library->user_database.doesUserExist(entered_username)) {
                std::cout << "No such user exists! Please try again.\n";
                return;
            } 

            auto username_found = library->user_database.searchUserByUsername(entered_username);

            if (!(*username_found)->checkCredentials(entered_password)) {
                std::cout << "Password Incorrect! Please try again.\n";
                return;
            }

            library->current_user = &(**username_found);

            switch ((*username_found)->typeOfUser())
            {
            case UserType::kStudent:
                library->changeState(&StudentAccessState::getInstance());
                return;
            
            case UserType::kProfessor:
                library->changeState(&ProfessorAccessState::getInstance());
                return;

            case UserType::kLibrarian:
                library->changeState(&LibrarianAccessState::getInstance());
                return;

            default:
                std::cout << "User not determined\n\n";
            }

        }

    }

}   

void LoginState::exit(Library* library) {}