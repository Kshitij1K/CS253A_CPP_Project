#pragma once
#include <string>
#include <list>
#include <ctime>
#include <iostream>

class Book {
    public:
    void bookRequest();
    std::tm showDueDate();
    std::string getTitle();
    std::string getisbn();
    void displayBookInfo();

    private:
    std::string title;
    std::string author;
    std::string isbn;
    std::string publication;
    std::tm date_of_issue;
};

class BookDatabase {
    public:
    void addBook();
    void updateBook();
    void deleteBook();
    Book searchBook(std::string title);

    private:
    std::list<Book> list_of_books_;
};