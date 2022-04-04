#include <state_machine.hpp>

State& StudentAccessState::getInstance() {
  static StudentAccessState singleton;
  return singleton;
}

void StudentAccessState::enter(Library* library) {
    std::cout << "Student Portal\n";
}

void StudentAccessState::run(Library* library) {
    // library->current_state_ = NULL;
    std::cout << "Please enter the command you wish to execute."
                 "Available commands are \n"
                 "1) ALLBOOKLIST (Will display all books available for issue)\n"
                 "2) ISSUEDBOOKLIST (Will display books you have issued)\n"
                 "3) ISBOOKAVAILABLE <ISBN> (Will check whether the book with this particular ISBN is available for issue or not)\n"
                //  "4) ISSUEBOOK <ISBN> (Will issue this book to you if it is available)\n"
                 "4) GETFINE (Will display book wise and total fine you have accumulated)\n"
                 "5) LOGOUT (Will exit the software)\n"
                 "6) EXIT (Will exit the software)\n";
    
    std::string command;
    std::getline(std::cin, command);

    std::vector<std::string> split_command = getSplitStrings(command);
}

void StudentAccessState::exit(Library* library) {}
