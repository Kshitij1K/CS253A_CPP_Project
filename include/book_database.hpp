#pragma once
#include <string>
#include <list>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>

class BookDatabase;

class Date {
    public:
    Date();
    Date(int day, int month, int year);
    long int getDifference(Date& date);
    static int days_shifted;

    private:
    int day_;
    int month_;
    int year_;
};

class Book {
    public:
    Book(std::string title,
         std::string author,
         std::string isbn,
         std::string publication);
    void bookRequest(Date date_of_issue);
    void displayBookInfo();
    Date getDateOfIssue();
    std::string getISBN();

    private:
    std::string title;
    std::string author;
    std::string isbn;
    std::string publication;
    Date date_of_issue;

    friend class BookDatabase;
};

class BookDatabase {
    public:
    BookDatabase();
    void addBook(Book book);
    void updateBook(std::string isbn, Book new_book, std::string availability);
    void deleteBook(std::string isbn);

    // Didn't really come in use, since I have used ISBN as a unique identifer
    std::shared_ptr<std::list<Book>> searchBookByTitle(std::string title);
    
    std::list<std::pair<Book, bool>>::iterator searchBookByISBN(std::string isbn);
    bool isBookAvailable(std::string isbn);
    void updateAvailability(std::string isbn, bool is_available);
    bool doesBookExist(std::string isbn);
    Book bookRequest(std::string isbn, bool is_stock_over);
    std::vector<Book> getAllBooks();

    private:
    std::list<std::pair<Book, bool>> list_of_books_;
    
};