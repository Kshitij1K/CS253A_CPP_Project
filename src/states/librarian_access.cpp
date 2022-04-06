#include <state_machine.hpp>

State& LibrarianAccessState::getInstance() {
  static LibrarianAccessState singleton;
  return singleton;
}

void LibrarianAccessState::enter(Library* library) {
    std::cout << "Librarian Portal\n";
    librarian_ = dynamic_cast<Librarian*>(library->current_user);
}

void LibrarianAccessState::run(Library* library) {
  std::cout << "Please enter the command you wish to execute. "
                "Available commands are \n"
                "1)  ADDUSER <username> (Will add a user with this username, prompts to enter other details will follow)\n"
                "2)  UPDATEUSER <username> (Will update a user with this username, prompts to enter other details will follow)\n "
                "3)  DELETEUSER <username> (Will delete a user with this username. This is irreversible!) \n"
                "4)  ADDBOOK <isbn> (Will add a book with this ISBN, prompts to enter other details will follow)\n " 
                "5)  UPDATEBOOK <isbn> (Will update a book with this ISBN, prompts to enter other details will follow)\n"
                "6)  DELETEBOOK <isbn> (Will delete a book with this ISBN. This process is irreversible!\n"
                "7)  ALLBOOKLIST (Will list all books)\n" // Done
                "8)  CHECKBOOKSTATUS <isbn> (Check the status of this book, like whom is it issued to or whether it is available for issue or not\n"
                "9)  CHECKISSUEDBOOKS <username> (Check the books issued to this username)\n"
                "10) CHANGECURRDATE DD MM YYYY (This command is for testing purpose, it changes the current date to one specified by the user.\n"
                "11) LOGOUT (Will log you out)\n" // Done
                "12) EXIT (Will exit the software)\n\n"; // Done

  std::string command;
  std::getline(std::cin, command);

  std::vector<std::string> split_command = getSplitStrings(command);

  if (split_command.size() != 2 && split_command.size() != 1 && split_command.size() != 4) {
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

        if (split_command[0] == "ALLBOOKLIST") {
          auto books = library->book_database.getAllBooks();
          for (auto book_it_:books) {
            book_it_.displayBookInfo();
          }
          return;
        }
  }

  if (split_command.size() == 2) {
    if (split_command[0] == "ADDUSER") {
      std::string entered_username = split_command[1];
      auto found_user = library->user_database.searchUserByUsername(entered_username);
      if (found_user != NULL) {   
        std::cout << "A user with this username already exists! Please enter a unique username.\n\n";
        return;
      }
      addUser(entered_username);
      return;
    }

    if (split_command[0] == "UPDATEUSER") {
      std::string entered_username = split_command[1];
      auto found_user = library->user_database.searchUserByUsername(entered_username);
      if (found_user == NULL) {
        std::cout << "A user with this username doesn't exist!\n\n";
        return;
      }

      modifyUser(entered_username);
      return;
    }

    if (split_command[0] == "ADDBOOK") {
      std::string entered_isbn = split_command[1];
      // auto found_isbn = library->book_database.searchBookByISBN(entered_isbn);

      if (library->book_database.doesBookExist(entered_isbn)) {   
        std::cout << "A Book with this isbn already exists! Please enter a unique ISBN.\n\n";
        return;
      }

      addBook(entered_isbn);
      return;
    }

    if (split_command[0] == "UPDATEBOOK") {
      std::string entered_isbn = split_command[1];
      // auto found_isbn = library->book_database.searchBookByISBN(entered_isbn);

      if (!library->book_database.doesBookExist(entered_isbn)) {   
        std::cout << "A Book with this isbn doesn't exist!\n\n";
        return;
      }

      modifyBook(entered_isbn);
      return;
    }
    
  }
}

void LibrarianAccessState::exit(Library* library) {}