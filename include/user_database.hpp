#pragma once
#include <user.hpp>
#include <string>
#include <vector>

class UserDatabase {
    public:
    UserDatabase(BookDatabase book_database);
    
    void addUser(Professor prof);
    void addUser(Librarian lib);
    void addUser(Student stud);
    
    void updateUser(std::string username, Professor new_prof_data);
    void updateUser(std::string username, Student new_stud_data);
    void updateUser(std::string username, Librarian new_lib_data);
    
    void deleteUser(std::string username);
    
    std::shared_ptr<std::list<User>> searchUserByName(std::string name);
    User* searchUserByUsername(std::string username);

    private:
    std::list<Student> list_of_students_;
    std::list<Professor> list_of_professors_;
    std::list<Librarian> list_of_librarians_;
};