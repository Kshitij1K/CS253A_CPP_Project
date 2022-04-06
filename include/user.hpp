#pragma once
#include <book_database.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include <chrono>
#define SECS_IN_DAY 86400

class UserDatabase;

enum class UserType {
    kStudent,
    kProfessor,
    kLibrarian,
    kGeneral
};

class User {
    public:
    UserType typeOfUser();
    virtual bool checkCredentials(std::string password);
    protected:
    std::string name_;
    std::string id_;
    std::string password_;
    UserType type_;
    friend class UserDatabase;
};

class Professor : public User {
    public:
    Professor(std::string name,
                std::string username,
                std::string password,
                std::list<Book> borrowed_books,
                std::vector<double> fines);
    void calculateFine();
    void clearFineAmount(double amount);
    Book returnBook(std::list<Book>::iterator book_to_clear);
    void listIssuedBooks();

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
                std::list<Book> borrowed_books,
                std::vector<double> fines);
    void calculateFine();
    Book returnBook(std::list<Book>::iterator book_to_clear);
    void clearFineAmount(double amount);
    void listIssuedBooks();

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
              std::string password);
    
    private:
    UserDatabase* list_of_users_;
};