#pragma once
#include <string>
#include <list>

class Book {
    void bookRequest();
    void showDueDate();

    private:
    std::string title;
    std::string author;
    std::string isbn;
    std::string publication;
    std::string date_of_issue; // in dd-mm-yyyy format
};

class BookDatabase {
    void addBook();
    void updateBook();
    void deleteBook();
    Book searchBook(std::string title);

    private:
    std::list<Book> list_of_books_;
};