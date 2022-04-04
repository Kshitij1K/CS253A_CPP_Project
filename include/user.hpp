#pragma once
#include <user_base.hpp>
#include <book.hpp>

class Professor : public User {
    public:
    double calculateFine();
    double clearFineAmount();

    private:
    double fine_amount_;
    std::list<Book> list_of_books_;
};

class Student : public User {
    public:
    double calculateFine();
    double clearFineAmount();

    private:
    double fine_amount_;
    std::list<Book> list_of_books_;
};

class Librarian: public User{
    private:
    UserDatabase list_of_users_;
};