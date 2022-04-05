#pragma once
#include <book_database.hpp>
#include <cmath>
#include <iostream>
#define SECS_IN_DAY 86400

class UserDatabase;

class User {
    private:
    std::string name_;
    std::string id_;
    std::string password_;
    std::string type_;
    friend class UserDatabase;
};

class Professor : public User {
    public:
    Professor(std::string name,
                std::string username,
                std::string password,
                std::string type,
                std::list<Book> borrowed_books,
                std::vector<double> fines);
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
    Student(std::string name,
                std::string username,
                std::string password,
                std::string type,
                std::list<Book> borrowed_books,
                std::vector<double> fines);
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
    public:
    Librarian(std::string name,
              std::string username,
              std::string password,
              std::string type,
              UserDatabase* database);
    
    private:
    UserDatabase* list_of_users_;
};