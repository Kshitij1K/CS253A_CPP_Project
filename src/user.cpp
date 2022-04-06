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
                std::list<Book> borrowed_books,
                std::vector<double> fines) {

    name_ = name;
    id_ = username;
    password_ = password;
    type_ = UserType::kStudent;

    list_of_books_ = borrowed_books;
    cleared_fine_ = fines[0];
    prev_fine_ = fines[1];
}

double Student::calculateBookWiseFine(Book& book) {
    Date today;
    auto issue_date = book.getDateOfIssue();
    double fine = 0;
    std::cout << "Diff: " << today.getDifference(issue_date) <<"\n";
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

    std::cout << "Total fine from earlier books already returned is Rs" << prev_fine_ << "\n";
    std::cout << "Total fine already paid is Rs" << cleared_fine_ << "\n";

    std::cout << "Total fine remaining is Rs" << total_current_fine + prev_fine_ - cleared_fine_ << "\n\n\n\n\n";
    fine_amount_ = total_current_fine + prev_fine_ - cleared_fine_;
}

void Student::returnBook(std::string isbn) {
    auto book_it_ = list_of_books_.begin();

    for (; book_it_ != list_of_books_.end(); book_it_++) {
        if (book_it_->getISBN() == isbn) break;
    }

    prev_fine_ += calculateBookWiseFine(*book_it_);

    if (book_it_ == list_of_books_.end()) {
        std::cout << "User has not borrowed any books with this ISBN!\n\n";
        return;
    }
    list_of_books_.erase(book_it_);
}

void Student::clearFineAmount(double amount) {
    cleared_fine_ += amount;
    std::cout << "Remaining fine is: " << fine_amount_+prev_fine_-cleared_fine_ <<"\n\n";
}

void Student::listIssuedBooks() {
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
                std::list<Book> borrowed_books,
                std::vector<double> fines) {

    name_ = name;
    id_ = username;
    password_ = password;
    type_ = UserType::kProfessor;

    list_of_books_ = borrowed_books;
    cleared_fine_ = fines[0];
    prev_fine_ = fines[1];
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

    std::cout << "Total fine from earlier books already returned is Rs" << prev_fine_ << "\n";
    std::cout << "Total fine already paid is Rs" << cleared_fine_ << "\n";

    std::cout << "Total fine remaining is Rs" << total_current_fine + prev_fine_ - cleared_fine_ << "\n\n\n\n\n";
    fine_amount_ = total_current_fine + prev_fine_ - cleared_fine_;
}

void Professor::returnBook(std::string isbn) {
    auto book_it_ = list_of_books_.begin();

    for (; book_it_ != list_of_books_.end(); book_it_++) {
        if (book_it_->getISBN() == isbn) break;
    }

    prev_fine_ += calculateBookWiseFine(*book_it_);

    if (book_it_ == list_of_books_.end()) {
        std::cout << "User has not borrowed any books with this ISBN!\n\n";
        return;
    }
    list_of_books_.erase(book_it_);
}

void Professor::clearFineAmount(double amount) {
    cleared_fine_ += amount;
    std::cout << "Remaining fine is: " << fine_amount_+prev_fine_-cleared_fine_ <<"\n\n";
}

void Professor::listIssuedBooks() {
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
