#include <state_machine.hpp>


State& ProfessorAccessState::getInstance() {
  static ProfessorAccessState singleton;
  return singleton;
}

void ProfessorAccessState::enter(Library* library) {
    std::cout << "Professor Portal\n";
    // professor_ = dynamic_cast<Professor&>(*library->current_user);
    professor_ = dynamic_cast<Professor*>(library->current_user);
}

void ProfessorAccessState::run(Library* library) {
    // library->current_state_ = NULL;
    std::cout << "Please enter the command you wish to execute. "
                 "Available commands are \n"
                 "1) ALLBOOKLIST (Will display all books)\n" //Done 
                 "2) ISSUEDBOOKLIST (Will display books you have issued)\n" //Done
                 "3) ISBOOKAVAILABLE <ISBN> (Will check  whether the book with this particular ISBN is available for issue or not)\n" //Done
                 "4) GETFINE (Will display book wise and total fine you have accumulated)\n" //Done
                 "5) LOGOUT (Will exit the software)\n" // Done
                 "6) EXIT (Will exit the software)\n"; // Done
    
    std::string command;
    std::getline(std::cin, command);

    std::vector<std::string> split_command = getSplitStrings(command);

    if (split_command.size() != 2 && split_command.size() != 1) {
        std::cout << "Incorrect Command Entered! Please enter the correct command, according to instructions.\n";
        return;
    }

    if (split_command.size() == 1) {
        if (split_command[0] == "EXIT") {
            library->current_state_ = NULL;
            return;
        }

        if (split_command[0] == "LOGOUT") {
          library->changeState(&LoginState::getInstance());
          return;
        }

        if (split_command[0] == "GETFINE") {
          professor_->calculateFine();
          return;
        }

        if (split_command[0] == "ALLBOOKLIST") {
          auto books = library->book_database.getAllBooks();
          for (auto book_it_:books) {
            book_it_.displayBookInfo();
          }
          return;
        }

        if (split_command[0] == "ISSUEDBOOKLIST") {
          professor_->listIssuedBooks();
          return;
        }
    }

    if (split_command.size() == 2) {
      if (split_command[0] == "ISBOOKAVAILABLE") {
        std::string isbn = split_command[1];
        bool is_book_avalaible = library->book_database.isBookAvailable(isbn);
        std::cout << (is_book_avalaible ? "Book is available for issue.\n\n" : "Book is unavailable for issue.\n\n");
        return;
      }
    }

    std::cout << "Incorrect Command Entered! Please enter the correct command, according to instructions.\n\n";
}

void ProfessorAccessState::exit(Library* library) {
  std::cout << "Logging out\n\n\n";
}