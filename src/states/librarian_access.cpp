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
                "1)  ADDUSER (Will add a user, prompts to enter other details will follow)\n" // Done
                "2)  UPDATEUSER (Will update a user, prompts to enter other details will follow)\n " // Done
                "3)  DELETEUSER <username> (Will delete a user with this username. This is irreversible!) \n" // Done
                "4)  ADDBOOK (Will add a book, prompts to enter other details will follow)\n " // DONE
                "5)  UPDATEBOOK (Will update a book, prompts to enter other details will follow)\n" // Done
                "6)  DELETEBOOK <isbn> (Will delete a book with this ISBN. This process is irreversible!\n" // Done
                "7)  ALLBOOKLIST (Will list all books)\n" // Done
                "8)  CHECKBOOKSTATUS <isbn> (Check the status of this book, like whom is it issued to or whether it is available for issue or not\n"
                "9)  CHECKISSUEDBOOKS <username> (Check the books issued to this username)\n"
                "10) ISSUEBOOK <username> <isbn> (Issue the book with this ISBN, to the user having this username)\n"
                "11) ISSUEBOOK <username> <isbn> (Issue the book with this ISBN, to the user having this username)\n"
                "12) CHANGECURRDATE DD MM YYYY (This command is for testing purpose, it changes the current date to one specified by the user.\n"
                "13) LOGOUT (Will log you out)\n" // Done
                "14) EXIT (Will exit the software)\n\n"; // Done

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

    if (split_command[0] == "ADDBOOK") {
      std::string entered_isbn = split_command[1];
      addBook(library);
      return;
    }

    if (split_command[0] == "UPDATEBOOK") {
      std::string entered_isbn = split_command[1];
      modifyBook(library);
      return;
    }

    if (split_command[0] == "ADDUSER") {
      std::string entered_username = split_command[1];
      addUser(library);
      return;
    }

    if (split_command[0] == "UPDATEUSER") {
      std::string entered_username = split_command[1];
      modifyUser(library);
      return;
    }
  }

  if (split_command.size() == 2) {
    

    if (split_command[0] == "DELETEUSER") {
      std::string entered_username = split_command[1];
      library->user_database.deleteUser(entered_username);
      return;
    }



    if (split_command[0] == "DELETEBOOK") {
      std::string entered_isbn = split_command[1];
      library->book_database.deleteBook(entered_isbn);
      return;
    }
    
  }
}

void LibrarianAccessState::addBook(Library* library) {
  // Book new_book;
  std::string title;
  std::cout << "Please enter the book title and hit Enter:\n";
  std::getline(std::cin, title);
  
  std::string author;
  std::cout << "Please enter the author name and hit Enter:\n";
  std::getline(std::cin, author);

  std::string isbn;
  std::cout << "Please enter the ISBN of the new book and hit Enter:\n";
  std::getline(std::cin, isbn);
  
  std::string publication;
  std::cout << "Please enter the publication year of the new book and hit Enter:\n";
  std::getline(std::cin, publication);

  Book new_book(title, author, isbn, publication);
  library->book_database.addBook(new_book);
}

void LibrarianAccessState::addUser(Library* library) {
  // Book new_book;
  std::string name;
  std::cout << "Please enter the new user's full name and hit Enter:\n";
  std::getline(std::cin, name);
  
  std::string username;
  std::cout << "Please enter the new user's username (should not contain spaces) and hit Enter:\n";
  std::getline(std::cin, username);
  if (getSplitStrings(username).size() != 1) {
    std::cout << "Username should not contain spaces! Aborting.\n\n";
    return;
  }

  std::string password;
  std::cout << "Please enter the new user's password (should not contain spaces) and hit Enter:\n";
  std::getline(std::cin, password);
  if (getSplitStrings(password).size() != 1) {
    std::cout << "Password should not contain spaces! Aborting.\n\n";
    return;
  }

  std::string type;
  std::cout << "Please type (without the single quotes)\n"
               "'Librarian' if this user is a librarian, \n"
               "'Professor' if this user is a professor, \n"
               "'Student' is this user is a student:\n";
  std::getline(std::cin, type);

  if (type == "Librarian") {
    Librarian librarian(name, username, password);
    library->user_database.addUser(librarian);
  } 
  
  else if (type == "Professor") {
    std::list<Book> borrowed_books;
    std::vector<double> fines;
    Professor professor(name, username, password, borrowed_books, fines);
    library->user_database.addUser(professor);
    library->user_database.addUser(professor);
  }
  
  else if (type == "Student") {
    std::list<Book> borrowed_books;
    std::vector<double> fines;
    Student student(name, username, password, borrowed_books, fines);
    library->user_database.addUser(student);
  }
  else {
    std::cout << "Incorrect user type entered! Aborting.\n\n";
  }
}

void LibrarianAccessState::modifyBook(Library* library) {
  std::string old_isbn;
  std::cout << "Please enter the ISBN of the book to update and hit Enter:\n";
  std::getline(std::cin, old_isbn);

  auto old_book = library->book_database.searchBookByISBN(old_isbn);

  std::string new_isbn;
  std::cout << "Please enter the new ISBN of the book to update. "
               "If you want it to be the same as before, don't enter anything. "
               "Hit Enter:\n";
  std::getline(std::cin, new_isbn);
  // if (new_isbn = "") new_isbn = old_book->first

  std::string new_title;
  std::cout << "Please enter the new Title of the book to update. "
               "If you want it to be the same as before, don't enter anything. "
               "Hit Enter:\n";
  std::getline(std::cin, new_title);
  
  std::string new_author;
  std::cout << "Please enter the new author of the book to update. "
               "If you want it to be the same as before, don't enter anything. "
               "Hit Enter:\n";
  std::getline(std::cin, new_author);

  
  std::string new_publication;
  std::cout << "Please enter the new publication year of the book to update. "
               "If you want it to be the same as before, don't enter anything. "
               "Hit Enter:\n";
  std::getline(std::cin, new_publication);

  std::string availability;
  std::cout << "Please enter 1 if the book is available for issue right now, 0 if it isn't. "
               "Entering anything else will leave the availability unchanged. "
               "Hit Enter:\n";
  std::getline(std::cin, availability);

  Book new_book(new_title, new_author, new_isbn, new_publication);
  library->book_database.updateBook(old_isbn, new_book, availability);
}

void LibrarianAccessState::modifyUser(Library* library) {
  // Book new_book;
  std::string old_username;
  std::cout << "Please enter the user's username and hit Enter:\n";
  std::getline(std::cin, old_username);
  if (getSplitStrings(old_username).size() != 1) {
    std::cout << "Username should not contain spaces! Aborting.\n\n";
    return;
  }

  std::string new_username;
  std::cout << "Please enter the new username of the user to update. "
               "If you want it to be the same as before, don't enter anything. "
               "Hit Enter:\n";
  std::getline(std::cin, new_username);

  std::string new_password;
  std::cout << "Please enter the new password of the username to update. "
               "If you want it to be the same as before, don't enter anything. "
               "Hit Enter:\n";
  std::getline(std::cin, new_password);
  
  std::string new_name;
  std::cout << "Please enter the new name of the user to update. "
               "If you want it to be the same as before, don't enter anything. "
               "Hit Enter:\n";
  std::getline(std::cin, new_name);
  
  library->user_database.updateUser(old_username, new_username, new_password, new_name);
}
void LibrarianAccessState::exit(Library* library) {

}