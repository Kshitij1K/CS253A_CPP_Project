#include <user.hpp>

UserType User::typeOfUser() {
    return type_;
}

bool User::checkCredentials(std::string password) {
    return password_ == password;
}

Student::Student(std::string name,
                std::string username,
                std::string password,
                std::list<Book> borrowed_books) {

    name_ = name;
    id_ = username;
    password_ = password;
    type_ = UserType::kStudent;

    list_of_books_ = borrowed_books;
}

double Student::calculateBookWiseFine(Book& book) {
    Date today;
    auto issue_date = book.getDateOfIssue();
    double fine = 0;
    std::cout << "Number of days since issue: " << today.getDifference(issue_date) <<"\n";
    if (today.getDifference(issue_date) > 30) fine = (today.getDifference(issue_date)-30)*2;
    std::cout << "Fine for this book is Rs " << std::to_string(fine) <<"\n\n\n";
    return fine;
}

void Student::calculateFine() {
    double total_current_fine = 0;
    
    for (auto book_it_:list_of_books_) {
        book_it_.displayBookInfo();
        

        total_current_fine += calculateBookWiseFine(book_it_);
    }

    std::cout << "Total fine to pay is Rs" << total_current_fine << "\n\n\n\n\n";
}

void Student::returnBook(std::string isbn) {
    auto book_it_ = list_of_books_.begin();

    for (; book_it_ != list_of_books_.end(); book_it_++) {
        if (book_it_->getISBN() == isbn) break;
    }

    if (book_it_ == list_of_books_.end()) {
        std::cout << "User has not borrowed any books with this ISBN!\n\n";
        return;
    }

    calculateBookWiseFine(*book_it_);
    std::cout << "Please collect this fine amount from the user.\n"; 
    list_of_books_.erase(book_it_);
}

void Student::deleteBook(std::string isbn) {
    auto book_it_ = list_of_books_.begin();

    for (; book_it_ != list_of_books_.end(); book_it_++) {
        if (book_it_->getISBN() == isbn) list_of_books_.erase(book_it_);
    }
}

void Student::listIssuedBooks() {
    if (list_of_books_.size() == 0) {
        std::cout << "No books issued to this user.\n\n";
        return;
    }

    auto book_it_ = list_of_books_.begin();

    for (; book_it_ != list_of_books_.end(); book_it_++) {
        book_it_->displayBookInfo();
    }
}

void Student::issueBook(Book book) {
    list_of_books_.push_back(book);
}

Professor::Professor(std::string name,
                     std::string username,
                     std::string password,
                     std::list<Book> borrowed_books) {

    name_ = name;
    id_ = username;
    password_ = password;
    type_ = UserType::kProfessor;

    list_of_books_ = borrowed_books;
}

double Professor::calculateBookWiseFine(Book& book) {
    Date today;
    auto issue_date = book.getDateOfIssue();
    double fine = 0;
    if (today.getDifference(issue_date) > 60) fine = (today.getDifference(issue_date)-60)*5;
    std::cout << "Fine for this book is Rs " << std::to_string(fine) <<"\n\n\n";
    return fine;
}

void Professor::calculateFine() {
    double total_current_fine = 0;
    
    for (auto book_it_:list_of_books_) {
        book_it_.displayBookInfo();      
        total_current_fine += calculateBookWiseFine(book_it_);
    }

    std::cout << "Total fine remaining to pay is Rs" << total_current_fine << "\n\n\n\n\n";
}

void Professor::returnBook(std::string isbn) {
    auto book_it_ = list_of_books_.begin();

    for (; book_it_ != list_of_books_.end(); book_it_++) {
        if (book_it_->getISBN() == isbn) break;
    }

    if (book_it_ == list_of_books_.end()) {
        std::cout << "User has not borrowed any books with this ISBN!\n\n";
        return;
    }
    
    calculateBookWiseFine(*book_it_);
    std::cout << "Please collect this fine amount from the user.\n"; 
    list_of_books_.erase(book_it_);
}

void Professor::deleteBook(std::string isbn) {
    auto book_it_ = list_of_books_.begin();

    for (; book_it_ != list_of_books_.end(); book_it_++) {
        if (book_it_->getISBN() == isbn) list_of_books_.erase(book_it_);
    }
}

void Professor::listIssuedBooks() {
    if (list_of_books_.size() == 0) {
        std::cout << "No books issued to this user.\n\n";
        return;
    }
    
    auto book_it_ = list_of_books_.begin();

    for (; book_it_ != list_of_books_.end(); book_it_++) {
        book_it_->displayBookInfo();
    }
}

void Professor::issueBook(Book book) {
    list_of_books_.push_back(book);
}

Librarian::Librarian(std::string name,
                std::string username,
                std::string password) {

    name_ = name;
    id_ = username;
    password_ = password;
    type_ = UserType::kLibrarian;

}
