#pragma once
#include <user_base.hpp>
#include <book.hpp>
#include <cmath>
#include <iostream>
#define SECS_IN_DAY 86400

class Professor : public User {
    public:
    void calculateFine();
    void clearFineAmount(double amount);
    Book returnBook(std::list<Book>::iterator book_to_clear);

    private:
    double calculateBookWiseFine(Book& book);
    double fine_amount_;
    double cleared_fine_ = 0;
    double prev_fine_;
    std::list<Book> list_of_books_;
};

class Student : public User {
    public:
    void calculateFine();
    Book returnBook(std::list<Book>::iterator book_to_clear);
    void clearFineAmount(double amount);

    private:
    double calculateBookWiseFine(Book& book);
    double fine_amount_;
    double cleared_fine_ = 0;
    double prev_fine_;
    std::list<Book> list_of_books_;
};

class Librarian: public User{
    private:
    UserDatabase list_of_students_;
    UserDatabase list_of_professors_;
};