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
            std::list<Book> borrowed_books);
    void calculateFine();
    void clearFine(double fine);
    void returnBook(std::string isbn);
    void deleteBook(std::string isbn);
    void issueBook(Book book);
    void listIssuedBooks();

    private:
    double fine_amount_;
    double fine_prev_books_;
    double cleared_fine_;
    double calculateBookWiseFine(Book& book);
    std::list<Book> list_of_books_;
    friend class UserDatabase;
};

class Student : public User {
    public:
    Student(std::string name,
            std::string username,
            std::string password,
            std::list<Book> borrowed_books);
    void calculateFine();
    void clearFine(double fine);
    void returnBook(std::string isbn);
    void deleteBook(std::string isbn);
    void issueBook(Book book);
    void listIssuedBooks();

    private:
    double calculateBookWiseFine(Book& book);
    std::list<Book> list_of_books_;
    friend class UserDatabase;
};

class Librarian: public User{
    public:
    Librarian(std::string name,
              std::string username,
              std::string password);
    
    private:
    UserDatabase* list_of_users_;
    friend class UserDatabase;
};