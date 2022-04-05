#include <user_database.hpp>

typedef std::vector<std::vector<std::tuple<int, int, int>>> issue_dates;

UserDatabase::UserDatabase(BookDatabase book_database) {
    std::vector<std::string> student_names = {"Kshitij Kabeer",
                                              "Ankit Lakhiwal",
                                              "Pallab Mahato",
                                              "Kshitiz Chaurasia",
                                              "Sourabh Ingale"};

    std::vector<std::string> prof_names = {"Indranil Saha",
                                            "Sumit Basu",
                                            "Krishnmurthy Muralidhar"};

    std::vector<std::string> lib_names = {"Gurunath Ramanathan",
                                          "Suman Ashish"};

    std::vector<std::string> student_usernames = {"kabeer",
                                                  "ankitl",
                                                  "pallabm",
                                                  "kshitchaur",
                                                  "singale"};

    std::vector<std::string> prof_usernames = {"isaha",
                                               "sbasu",
                                               "kmurli"};

    std::vector<std::string> lib_usernames = {"librarian",
                                              "sumana"};


    std::vector<std::string> student_passwords = {"abc",
                                                  "def",
                                                  "ghi",
                                                  "jkl",
                                                  "mno"};

    std::vector <std::string> prof_passwords = {"pqr",
                                                "stu",
                                                "vwx"};

    std::vector<std::string> lib_passwords = {"123",
                                              "456"};


    std::vector<std::vector<int>> student_borrowed_books = {{1,2},
                                                            {0,1,4},
                                                            {3,4},
                                                            {1,2},
                                                            {2}};

    std::vector<std::vector<int>> professor_borrowed_books = {{0,1,2},
                                                              {3},
                                                              {2,4}};

    std::vector<std::vector<double>> student_fines = {{50, 100},
                                                      {34, 56},
                                                      {12, 21},
                                                      {45, 3},
                                                      {0, 0}};

    std::vector<std::vector<double>> prof_fines = {{5, 10},
                                                   {2, 11},
                                                   {0, 0}};

    issue_dates student_borrow_dates = {{{25,12,2021}, {25,12,2021}},
                                        {{30,3,2022}, {1,1,2022}, {2,3,2022}},
                                        {{2,2,2022}, {15,3,2022}},
                                        {{21,9,2021}, {30,1,2022}},
                                        {{7,12,2021}}};

    issue_dates professor_borrow_dates = {{{20, 2, 2022}, {22,1,2022}, {1,1,2021}},
                                          {{1,12,2021}},
                                          {{25,3,2022}, {25,3,2022}}};

    for (int i = 0; i<student_names.size(); i++) {
        std::list<Book> borrowed_books;

        int count = 0;
        for (auto it_:student_borrowed_books[i]) {
            auto book = borrowed_books.begin();
            std::advance(book, it_);
            
            std::tm issue_date;
            issue_date.tm_year = std::get<0>(student_borrow_dates[i][count]);
            issue_date.tm_mon = std::get<1>(student_borrow_dates[i][count]);
            issue_date.tm_mday = std::get<2>(student_borrow_dates[i][count]);
            issue_date.tm_min = 1;
            count++;

            book->bookRequest(issue_date);

            borrowed_books.push_back(*book);
        }

        Student student(student_names[i],
                        student_usernames[i],
                        student_passwords[i],
                        borrowed_books,
                        student_fines[i]);
        
        list_of_students_.push_back(student);
    } 

    for (int i = 0; i<prof_names.size(); i++) {
        std::list<Book> borrowed_books;

        int count;
        for (auto it_:professor_borrowed_books[i]) {
            auto book = borrowed_books.begin();
            std::advance(book, it_);

            std::tm issue_date;
            issue_date.tm_year = std::get<0>(professor_borrow_dates[i][count]);
            issue_date.tm_mon = std::get<1>(professor_borrow_dates[i][count]);
            issue_date.tm_mday = std::get<2>(professor_borrow_dates[i][count]);
            issue_date.tm_min = 1;
            count++;

            book->bookRequest(issue_date);

            borrowed_books.push_back(*book);
        }

        Professor professor(prof_names[i],
                            prof_usernames[i],
                            prof_passwords[i],
                            borrowed_books,
                            prof_fines[i]);
        
        list_of_professors_.push_back(professor);
    }                                     

    for (int i = 0; i<lib_names.size(); i++) {
        Librarian librarian(lib_names[i],
                            lib_usernames[i],
                            lib_passwords[i],
                            this);

        list_of_librarians_.push_back(librarian);
    }                                     
    
}

std::shared_ptr<std::list<User>> UserDatabase::searchUserByName(std::string name) {
    auto result = std::make_shared<std::list<User>>();
    
    for (auto user_:list_of_librarians_){
        if (user_.name_ == name) {
            result->push_back(user_);
        }
    }

    for (auto user_:list_of_professors_){
        if (user_.name_ == name) {
            result->push_back(user_);
        }
    }

    for (auto user_:list_of_librarians_){
        if (user_.name_ == name) {
            result->push_back(user_);
        }
    }

    return result;
}

void UserDatabase::addUser(Student stud) {
    list_of_students_.push_back(stud);
    std::cout << "User added successfully.\n\n";
}

void UserDatabase::addUser(Professor prof) {
    list_of_professors_.push_back(prof);
    std::cout << "User added successfully.\n\n";
}

void UserDatabase::addUser(Librarian lib) {
    list_of_librarians_.push_back(lib);
    std::cout << "User added successfully.\n\n";
}

void UserDatabase::updateUser(std::string username, Professor new_prof_data) {
    auto user_it_ = list_of_professors_.begin();
    
    for (;user_it_ != list_of_professors_.end(); user_it_++){
        if (user_it_->id_ == username) {
            *user_it_ = new_prof_data;
            std::cout << "User updated successfully\n\n";
            return;
        }
    }

    std::cout << "No such User Found!\n\n";
}

void UserDatabase::updateUser(std::string username, Student new_stud_data) {
    auto user_it_ = list_of_students_.begin();
    
    for (;user_it_ != list_of_students_.end(); user_it_++){
        if (user_it_->id_ == username) {
            *user_it_ = new_stud_data;
            std::cout << "User updated successfully\n\n";
            return;
        }
    }

    std::cout << "No such User Found!\n\n";
}

void UserDatabase::updateUser(std::string username, Librarian new_lib_data) {
    auto user_it_ = list_of_librarians_.begin();
    
    for (;user_it_ != list_of_librarians_.end(); user_it_++){
        if (user_it_->id_ == username) {
            *user_it_ = new_lib_data;
            std::cout << "User updated successfully\n\n";
            return;
        }
    }

    std::cout << "No such User Found!\n\n";
}

void UserDatabase::deleteUser(std::string username) {
    auto lib_it_ = list_of_librarians_.begin();
    
    for (;lib_it_ != list_of_librarians_.end(); lib_it_++){
        if (lib_it_->id_ == username) {
            list_of_librarians_.erase(lib_it_);
            std::cout << "User deleted successfully\n\n";
            return;
        }
    }

    auto prof_it_ = list_of_professors_.begin();
    
    for (;prof_it_ != list_of_professors_.end(); prof_it_++){
        if (prof_it_->id_ == username) {
            list_of_professors_.erase(prof_it_);
            std::cout << "User deleted successfully\n\n";
            return;
        }
    }

    auto student_it_ = list_of_students_.begin();
    
    for (;student_it_ != list_of_students_.end(); student_it_++){
        if (student_it_->id_ == username) {
            list_of_students_.erase(student_it_);
            std::cout << "User deleted successfully\n\n";
            return;
        }
    }

    std::cout << "No such User Found!\n\n";
}

User* UserDatabase::searchUserByUsername(std::string username) {
    auto lib_it_ = list_of_librarians_.begin();
    
    for (;lib_it_ != list_of_librarians_.end(); lib_it_++){
        if (lib_it_->id_ == username) {
            return &(*lib_it_);
        }
    }

    auto prof_it_ = list_of_professors_.begin();
    
    for (;prof_it_ != list_of_professors_.end(); prof_it_++){
        if (prof_it_->id_ == username) {
            return &(*prof_it_);
        }
    }

    auto student_it_ = list_of_students_.begin();
    
    for (;student_it_ != list_of_students_.end(); student_it_++){
        if (student_it_->id_ == username) {
            list_of_students_.erase(student_it_);
            return &(*student_it_);
        }
    }

    return NULL;
}

