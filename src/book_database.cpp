#include <book_database.hpp>

Date::Date() {
    std::time_t time_now = std::time(0);
    std::tm* tm_time_now = std::localtime(&time_now);

    year_ = tm_time_now->tm_year+1900;
    month_ = tm_time_now->tm_mon+1;
    day_ = tm_time_now->tm_mday;
}

Date::Date(int day, int month, int year) {
    year_ = year;
    month_ = month;
    day_ = day;
}

long int Date::getDifference(Date& date) {
    const int days_in_a_month[12] = { 31, 28, 31, 30, 31, 30,
                                      31, 31, 30, 31, 30, 31 };

    int curr_date_leap_years = year_;
    if (month_ <=2 ) curr_date_leap_years--;
    curr_date_leap_years = curr_date_leap_years/4 + curr_date_leap_years/400 - curr_date_leap_years/100;

    long long int num_days_curr_date = year_*365 + day_;
    for (int i=0; i<month_-1; i++) num_days_curr_date += days_in_a_month[i];
    num_days_curr_date += curr_date_leap_years;

    int prev_date_leap_years = date.year_;
    if (date.month_ <=2 ) prev_date_leap_years--;
    prev_date_leap_years = prev_date_leap_years/4 + prev_date_leap_years/400 - prev_date_leap_years/100;

    long long int num_days_prev_date = date.year_*365 + date.day_;
    for (int i=0; i<date.month_-1; i++) num_days_prev_date += days_in_a_month[i];
    num_days_prev_date += prev_date_leap_years;

    return num_days_curr_date - num_days_prev_date;
}

BookDatabase::BookDatabase() {
    std::vector<std::string> names = {"Embedded Systems",
                                      "Control Theory",
                                      "Numerical Methods",
                                      "Solid Mechanics",
                                      "Fluid Mechanics",
                                      "Fluid Mechanics"};

    std::vector<std::string> authors = {"Lee and Seshia",
                                        "Donald Kirk",
                                        "Richard Wesley",
                                        "Rownland Richard",
                                        "Frank White",
                                        "Cengel and Boles"};

    std::vector<std::string> isbn = {"1263",
                                     "7176",
                                     "2003",
                                     "4279",
                                     "5002",
                                     "3329"};

    std::vector<std::string> publication = {"2017",
                                            "2012",
                                            "1962",
                                            "2000",
                                            "1979",
                                            "2006"};

    std::vector<bool> is_available = {true,
                                      true,
                                      false,
                                      true,
                                      true,
                                      true};


    for (int i=0; i<names.size(); i++) {
        Book book(names[i],
                  authors[i],
                  isbn[i],
                  publication[i]);

        list_of_books_.push_back({book, is_available[i]});
    }
}

void BookDatabase::addBook(Book book){
    auto existing_book = searchBookByISBN(book.isbn);
    if (existing_book != list_of_books_.end()) {
        std::cout << "Book with the given ISBN already exists! ISBN should be unique. Adding new book failed.\n\n";
        return;
    }

    list_of_books_.push_back({book, true});
    std::cout << "Adding new book successful. The new book added is\n";
    book.displayBookInfo();
}

void BookDatabase::updateBook(std::string isbn, Book new_book) {
    auto existing_book = searchBookByISBN(isbn);

    if (existing_book == list_of_books_.end()) {
        std::cout << "Book with the given ISBN doesn't exist! Updating book failed.\n\n";
        return;
    }

    existing_book->first = new_book;
    std::cout << "Updating book successful. The new details of the book are\n";
    new_book.displayBookInfo();
}

void BookDatabase::deleteBook(std::string isbn) {
    auto existing_book = searchBookByISBN(isbn);

    if (existing_book == list_of_books_.end()) {
        std::cout << "Book with the given ISBN doesn't exist! Deleting book failed.\n\n";
        return;
    }

    std::cout << "Deleting book successful. The details of the deleted book are\n";
    existing_book->first.displayBookInfo();
    list_of_books_.erase(existing_book);
}

std::shared_ptr<std::list<Book>> BookDatabase::searchBookByTitle(std::string title) {
    auto result = std::make_shared<std::list<Book>>();

    for (auto book_:list_of_books_){
        if (book_.first.title == title) {
            result->push_back(book_.first);
        }
    }

    return result;
}

std::list<std::pair<Book, bool>>::iterator BookDatabase::searchBookByISBN(std::string isbn) {
    auto book_it_ = list_of_books_.begin();

    for (; book_it_ != list_of_books_.end(); book_it_++) {
        if (book_it_->first.isbn == isbn) return book_it_;
    }

    return book_it_;
}

bool BookDatabase::isBookAvailable(std::string isbn) {
    auto book = searchBookByISBN(isbn);

    if (book == list_of_books_.end()) {
        std::cout << "Book with this ISBN doesn't exist!\n";
        return false;
    }

    return book->second;
}

bool BookDatabase::doesBookExist(std::string isbn) {
    auto book = searchBookByISBN(isbn);
    if (book == list_of_books_.end()) return false;
    return true;
}


void BookDatabase::bookRequest(std::string isbn, bool is_stock_left) {
    auto book = searchBookByISBN(isbn);

    if (book == list_of_books_.end()) {
        std::cout << "Book with this ISBN doesn't exist!\n\n";
        return;
    }
    
    Date today;
    book->first.bookRequest(today);
    book->second = is_stock_left;
}

std::vector<Book> BookDatabase::getAllBooks() {
    auto book_it_ = list_of_books_.begin();
    std::vector<Book> book_list;
    book_list.reserve(list_of_books_.size());

    for (; book_it_ != list_of_books_.end(); book_it_++) {
        book_list.push_back(book_it_->first);
    }

    return book_list;
}

Book::Book(std::string title,
           std::string author,
           std::string isbn,
           std::string publication) {

    this->title = title;
    this->author = author;
    this->isbn = isbn;
    this->publication = publication;
}

void Book::bookRequest(Date date_of_issue) {
    this->date_of_issue = date_of_issue;
}

void Book::displayBookInfo() {
    std::cout << "Title: " << title << "\n";
    std::cout << "Author: " << author << "\n";
    std::cout << "ISBN: " << isbn << "\n";
    std::cout << "Publication Year: " << publication << "\n\n";
}

Date Book::getDateOfIssue() {
    return date_of_issue;
}
