#pragma once
#include <string>
#include <list>
#include <ctime>
#include <iostream>
#include <algorithm>
class BookDatabase;

class Book {
    public:
    void bookRequest(std::tm date_of_issue);
    void displayBookInfo();
    std::tm getDateOfIssue();

    private:
    std::string title;
    std::string author;
    std::string isbn;
    std::string publication;
    std::tm date_of_issue;

    friend class BookDatabase;
};

class BookDatabase {
    public:
    void addBook(Book book);
    void updateBook(std::string isbn, Book new_book);
    void deleteBook(std::string isbn);
    std::shared_ptr<std::list<Book>> searchBookByTitle(std::string title);
    std::list<std::pair<Book, bool>>::iterator searchBookByISBN(std::string isbn);
    bool isBookAvailable(std::string isbn);
    void bookRequest(std::string isbn, bool is_stock_over);

    private:
    std::list<std::pair<Book, bool>> list_of_books_;
    
};