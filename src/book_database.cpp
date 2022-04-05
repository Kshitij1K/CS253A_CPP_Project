#include <book_database.hpp>

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
        std::cout << "Book with this ISBN doesn't exist!\n\n";
        return false;
    }

    return book->second;
}

void BookDatabase::bookRequest(std::string isbn, bool is_stock_left) {
    auto book = searchBookByISBN(isbn);

    if (book == list_of_books_.end()) {
        std::cout << "Book with this ISBN doesn't exist!\n\n";
        return;
    }
    
    auto date_today = std::time(0);
    std::tm* today = std::localtime(&date_today);

    today->tm_min = 1;
    today->tm_sec = 0;
    today->tm_hour = 0;
    book->first.bookRequest(*today);
    book->second = is_stock_left;
}

void BookDatabase::listAllBooks() {
    auto book_it_ = list_of_books_.begin();

    for (; book_it_ != list_of_books_.end(); book_it_++) {
        book_it_->first.displayBookInfo();
    }
}

void Book::bookRequest(std::tm date_of_issue) {
    this->date_of_issue = date_of_issue;
}

void Book::displayBookInfo() {
    std::cout << "Title: " << title << "\n";
    std::cout << "Author: " << author << "\n";
    std::cout << "ISBN: " << isbn << "\n";
    std::cout << "Publication Year: " << publication << "\n\n";
}

std::tm Book::getDateOfIssue() {
    return date_of_issue;
}
