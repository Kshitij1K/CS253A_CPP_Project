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
                "8)  CHECKBOOKSTATUS <isbn> (Check the status of this book, like whom is it issued to or whether it is available for issue or not\n" // Done
                "9)  CHECKISSUEDBOOKS <username> (Check the books issued to this username)\n" // Done
                "10) ISSUEBOOK <username> <isbn> (Issue the book with this ISBN, to the user having this username)\n" // Done
                "11) RETURNBOOK <username> <isbn> (Mark book with this ISBN as being returned by the user having this username)\n" // Done
                "12) SHIFTCURRDATE <number-of-days> (This command is for testing purpose, it shifts the current date forward by this many days. You can also specify a negative number here.)\n" // Done
                "13) LOGOUT (Will log you out)\n" // Done
                "14) EXIT (Will exit the software)\n\n"; // Done

  std::string command;
  std::getline(std::cin, command);

  std::vector<std::string> split_command = getSplitStrings(command);

  if (split_command.size() < 1 || split_command.size() > 4) {
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
    std::cout << "Incorrect Command Entered! Please enter the correct command, according to instructions.\n";
    return;
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
    
    if (split_command[0] == "CHECKBOOKSTATUS") {
      std::string entered_isbn = split_command[1];
      library->user_database.checkIssuedUsers(entered_isbn);
      std::cout << (library->book_database.isBookAvailable(entered_isbn) ? "Book is in stock and available for issue" : "Book is not in stock and unavailable for issue") << "\n\n";
      return;
    }

    if (split_command[0] == "CHECKISSUEDBOOKS") {
      std::string entered_username = split_command[1];
      if (!library->user_database.doesUserExist(entered_username)) {
        std::cout << "This user doesn't exist!\n\n";
        return;
      }
      std::cout << "The list of books issued by this user is\n";
      auto user = library->user_database.searchUserByUsername(entered_username);

      if (user->typeOfUser() == UserType::kStudent) {
        auto student = dynamic_cast<Student*>(&(*user));
        student->listIssuedBooks();
      } 

      else {
        auto professor = dynamic_cast<Professor*>(&(*user));
        professor->listIssuedBooks();
      }
    }

    if (split_command[0] == "SHIFTCURRDATE") {
      std::string days = split_command[1];
      try {
        Date::days_shifted += std::stoi(days);
        std::cout << "Current date is now shifted by " << Date::days_shifted << " for all date calculations. "
                     "Please keep in mind that this doesn't change the date of issue of books, merely the current date.\n\n";
      } catch (std::invalid_argument) {
        std::cout << "Please enter a valid integer for the number of days.\n\n";
    }

    std::cout << "Incorrect Command Entered! Please enter the correct command, according to instructions.\n";
    return;
  }


  if (split_command.size() == 3) {
    if (split_command[0] == "ISSUEBOOK") {
      std::string entered_isbn = split_command[1];
      std::string entered_username = split_command[2];

      if (!library->book_database.isBookAvailable(entered_isbn)) {
        std::cout << "This book is not available in stock and hence cannot be issued.\n\n";
        return;
      }

      if (!library->user_database.doesUserExist(entered_username)) {
        std::cout << "No user exists with the given username!\n\n";
        return;
      }

      std::cout << "This book is available for issue. Type YES and hit Enter if this is the last piece available in stock (Any other text will be intrepreted as NO):\n";
      std::string answer;
      std::getline(std::cin, answer);
      
      auto book_to_issue = library->book_database.searchBookByISBN(entered_isbn);
      auto user_to_issue = library->user_database.searchUserByUsername(entered_username);
      
      if (user_to_issue->typeOfUser() == UserType::kStudent) {
        auto student = dynamic_cast<Student*>(&(*user_to_issue));
        student->issueBook(book_to_issue->first);
        book_to_issue->second = (answer == "YES") ? false : true;
      }

      if (user_to_issue->typeOfUser() == UserType::kProfessor) {
        auto professor = dynamic_cast<Professor*>(&(*user_to_issue));
        professor->issueBook(book_to_issue->first);
        book_to_issue->second = (answer == "YES") ? false : true;
      }

    }

    if (split_command[0] == "RETURNBOOK") {
      std::string entered_isbn = split_command[1];
      std::string entered_username = split_command[2];

      if (!library->user_database.doesUserExist(entered_username)) {
        std::cout << "No user exists with the given username!\n\n";
        return;
      }

      auto user_for_return = library->user_database.searchUserByUsername(entered_username);

      if (user_for_return->typeOfUser() == UserType::kStudent) {
        auto student = dynamic_cast<Student*>(&(*user_for_return));
        student->returnBook(entered_isbn);
        library->book_database.updateAvailability(entered_isbn, true);
      }

      if (user_for_return->typeOfUser() == UserType::kProfessor) {
        auto professor = dynamic_cast<Professor*>(&(*user_for_return));
        professor->returnBook(entered_isbn);
        library->book_database.updateAvailability(entered_isbn, true);
      }
      std::cout << "Incorrect Command Entered! Please enter the correct command, according to instructions.\n";
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