#include <user.hpp>

Student::Student(std::string name,
                std::string username,
                std::string password,
                std::list<Book> borrowed_books,
                std::vector<double> fines) {

    name_ = name;
    id_ = username;
    password_ = password;

    list_of_books_ = borrowed_books;
    cleared_fine_ = fines[0];
    prev_fine_ = fines[1];
}

double Student::calculateBookWiseFine(Book& book) {
    std::time_t t = std::time(0);
    std::tm* today = std::localtime(&t);

    today->tm_min = 0;
    today->tm_sec = 0;
    today->tm_hour = 1;

    auto due_date = book.showDueDate();
    double difference = std::difftime(std::mktime(today), std::mktime(&due_date)) / SECS_IN_DAY;
    long long int days_since_due = std::floor(difference);

    double fine = 0;
    if (days_since_due >= 0) fine = days_since_due*2;
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

    std::cout << "Total fine is Rs" << total_current_fine + prev_fine_ - cleared_fine_ << "\n\n\n\n\n";
    fine_amount_ = total_current_fine + prev_fine_ - cleared_fine_;
}

Book Student::returnBook(std::list<Book>::iterator book_to_clear) {
    list_of_books_.erase(book_to_clear);
    std::cout << "The following book has been marked returned:\n";
    book_to_clear->displayBookInfo();

    prev_fine_ += calculateBookWiseFine(*book_to_clear);

    Book returned_book = *book_to_clear;
    list_of_books_.erase(book_to_clear);
    return returned_book;
    // calculateFine();
}

void Student::clearFineAmount(double amount) {
    cleared_fine_ += amount;
    std::cout << "Remaining fine is: " << fine_amount_+prev_fine_-cleared_fine_ <<"\n\n";
}




Professor::Professor(std::string name,
                std::string username,
                std::string password,
                std::list<Book> borrowed_books,
                std::vector<double> fines) {

    name_ = name;
    id_ = username;
    password_ = password;

    list_of_books_ = borrowed_books;
    cleared_fine_ = fines[0];
    prev_fine_ = fines[1];
}

double Professor::calculateBookWiseFine(Book& book) {
    std::time_t t = std::time(0);
    std::tm* today = std::localtime(&t);

    today->tm_min = 0;
    today->tm_sec = 0;
    today->tm_hour = 1;

    auto due_date = book.showDueDate();
    double difference = std::difftime(std::mktime(today), std::mktime(&due_date)) / SECS_IN_DAY;
    long long int days_since_due = std::floor(difference);

    double fine = 0;
    if (days_since_due >= 0) fine = days_since_due*5;
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

    std::cout << "Total fine is Rs" << total_current_fine + prev_fine_ - cleared_fine_ << "\n\n\n\n\n";
    fine_amount_ = total_current_fine + prev_fine_ - cleared_fine_;
}

Book Professor::returnBook(std::list<Book>::iterator book_to_clear) {
    list_of_books_.erase(book_to_clear);
    std::cout << "The following book has been marked returned:\n";
    book_to_clear->displayBookInfo();

    prev_fine_ += calculateBookWiseFine(*book_to_clear);

    Book returned_book = *book_to_clear;
    list_of_books_.erase(book_to_clear);
    return returned_book;
    // calculateFine();
}

void Professor::clearFineAmount(double amount) {
    cleared_fine_ += amount;
    std::cout << "Remaining fine is: " << fine_amount_+prev_fine_-cleared_fine_ <<"\n\n";
}



Librarian::Librarian(std::string name,
                std::string username,
                std::string password,
                UserDatabase* database) {

    name_ = name;
    id_ = username;
    password_ = password;
    list_of_users_ = database;
}