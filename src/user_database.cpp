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
                                                              {3,5},
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

    issue_dates professor_borrow_dates = {{{1,1,2021}, {22,1,2022}, {20, 2, 2022}},
                                          {{1,12,2021}, {17,11,2021}},
                                          {{25,3,2022}, {25,3,2022}}};

    auto all_books = book_database.getAllBooks();

    for (int i = 0; i<student_names.size(); i++) {
        std::list<Book> borrowed_books;

        int count = 0;
        for (auto it_:student_borrowed_books[i]) {
            Date issue_date(std::get<0>(student_borrow_dates[i][count]),
                            std::get<1>(student_borrow_dates[i][count]),
                            std::get<2>(student_borrow_dates[i][count]));

            Book book = all_books[it_];
            book.bookRequest(issue_date);
            borrowed_books.push_back(book);

            count++;
        }

        auto student = std::make_shared<Student>(student_names[i],
                                                    student_usernames[i],
                                                    student_passwords[i],
                                                    borrowed_books,
                                                    student_fines[i]);
        
        list_of_users_.push_back(student);
    } 

    for (int i = 0; i<prof_names.size(); i++) {
        std::list<Book> borrowed_books;

        int count = 0;
        for (auto it_:professor_borrowed_books[i]) {
            Date issue_date(std::get<0>(professor_borrow_dates[i][count]),
                            std::get<1>(professor_borrow_dates[i][count]),
                            std::get<2>(professor_borrow_dates[i][count]));


            Book book = all_books[it_];
            book.bookRequest(issue_date);
            borrowed_books.push_back(book);

            count++;
        }

        auto professor = std::make_shared<Professor>(prof_names[i],
                                                     prof_usernames[i],
                                                     prof_passwords[i],
                                                     borrowed_books,
                                                     prof_fines[i]);
        
        list_of_users_.push_back(professor);
    }                                     


    for (int i = 0; i<lib_names.size(); i++) {
        auto librarian = std::make_shared<Librarian>(lib_names[i],
                                                     lib_usernames[i],
                                                     lib_passwords[i]);

        list_of_users_.push_back(librarian);
    }                                     
    
}

std::shared_ptr<std::list<User>> UserDatabase::searchUserByName(std::string name) {
    auto result = std::make_shared<std::list<User>>();
    
    for (auto user_:list_of_users_){
        if (user_->name_ == name) {
            result->push_back(*user_);
        }
    }

    return result;
}

void UserDatabase::addUser(std::shared_ptr<User> user) {
    if (doesUserExist(user->id_)) {
        std::cout << "User with this username already exists! Please enter a unique username.\n";
        return;
    }

    list_of_users_.push_back(user);
    std::cout << "User added successfully.\n\n";
}

void UserDatabase::updateUser(std::string old_username,
                              std::string new_username,
                              std::string new_password,
                              std::string new_name) {
    auto user_it_ = searchUserByUsername(old_username);
    if (user_it_ == list_of_users_.end()) {
        std::cout << "No such User Found! Updating user failed\n\n";
        return;
    }

    if (new_username != "") (*user_it_)->id_ = new_username;
    if (new_password != "") (*user_it_)->password_ = new_password;
    if (new_name != "") (*user_it_)->name_ = new_name;
    
    std::cout << "User updated successfully.\n\n";
}

void UserDatabase::deleteUser(std::string username) {
    auto user_it_ = searchUserByUsername(username);
    if (user_it_ == list_of_users_.end()) {
        std::cout << "No such User Found!\n\n";
        return;
    }

    list_of_users_.erase(user_it_);
    std::cout << "User deleted successfully.\n\n";
}

std::list<std::shared_ptr<User>>::iterator UserDatabase::searchUserByUsername(std::string username) {
    auto user_it_ = list_of_users_.begin();

    for (; user_it_ != list_of_users_.end(); user_it_++) {
        if ((*user_it_)->id_ == username) return user_it_;
    }
    
    return user_it_;
}

bool UserDatabase::doesUserExist (std::string username) {
    auto user_it_ = searchUserByUsername(username);
    if (user_it_ == list_of_users_.end()) return false;
    return true;
}

void UserDatabase::checkIssuedUsers (std::string isbn) {
    std::cout << "The list of users this book is issued to are: \n";
    auto user_it_ = list_of_users_.begin();
    for (; user_it_ != list_of_users_.end(); user_it_++) {
        if ((*user_it_)->type_ == UserType::kStudent) {
            auto user_to_check = dynamic_cast<Student*>(&(**user_it_));
            
            int num_books = 0;
            for (auto book_it_:user_to_check->list_of_books_) {
                if (book_it_.getISBN() == isbn) num_books++;
            }

            if (num_books > 0) std::cout << num_books << " of these books have been issued to the student " << user_to_check->name_ <<", username: " <<user_to_check->id_ <<"\n";
        }

        else if ((*user_it_)->type_ == UserType::kProfessor) {
            auto user_to_check = dynamic_cast<Professor*>(&(**user_it_));
            
            int num_books = 0;
            for (auto book_it_:user_to_check->list_of_books_) {
                if (book_it_.getISBN() == isbn) num_books++;
            }

            if (num_books > 0) std::cout << num_books << " of these books have been issued to the professor " << user_to_check->name_ <<", username: " <<user_to_check->id_ <<"\n";
        }
    }
}

void UserDatabase::listAllUsers() {
    auto user_it_ = list_of_users_.begin();
    
    for (auto user_it_:list_of_users_) {
        std::cout << "Name: " << user_it_->name_ <<"\n";
        std::cout << "Username: " << user_it_->id_ <<"\n";
        std::cout << "Designation: ";
        switch (user_it_->type_)
        {
        case UserType::kStudent:
            std::cout << "Student\n\n";
            break;

        case UserType::kProfessor:
            std::cout << "Professor\n\n";
            break;

        case UserType::kLibrarian:
            std::cout << "Librarian\n\n";
            break;
        
        default:
            break;
        }
    }
}

void UserDatabase::updateIssuedBooks(std::string old_isbn, Book new_book) {
    for (auto user_it_:list_of_users_) {
        if (user_it_->type_ == UserType::kStudent) {
            auto user = dynamic_cast<Student*>(&(*user_it_));
            auto book_it_ = user->list_of_books_.begin();
            for (;book_it_ != user->list_of_books_.end(); book_it_++) {
                if (book_it_->getISBN() == old_isbn) {
                    Date date_of_issue = book_it_->getDateOfIssue();
                    *book_it_ = new_book;
                    book_it_->bookRequest(date_of_issue);
                }
            }
        }

        // std::cout << "Line 275\n";
        else if (user_it_->type_ == UserType::kProfessor){
            auto user = dynamic_cast<Professor*>(&(*user_it_));
            auto book_it_ = user->list_of_books_.begin();
            for (;book_it_ != user->list_of_books_.end(); book_it_++) {
                if (book_it_->getISBN() == old_isbn) {
                    Date date_of_issue = book_it_->getDateOfIssue();
                    *book_it_ = new_book;
                    book_it_->bookRequest(date_of_issue);
                }
            }      
        }
    }
}

void UserDatabase::deleteIssuedBooks (std::string isbn) {
    for (auto user_it_:list_of_users_) {
        if (user_it_->type_ == UserType::kStudent) {
            auto user = dynamic_cast<Student*>(&(*user_it_));
            auto book_it_ = user->list_of_books_.begin();
            for (;book_it_ != user->list_of_books_.end(); book_it_++) {
                if (book_it_->getISBN() == isbn) user->deleteBook(isbn);
            }
        }

        else if (user_it_->type_ == UserType::kProfessor){
            auto user = dynamic_cast<Professor*>(&(*user_it_));
            auto book_it_ = user->list_of_books_.begin();
            for (;book_it_ != user->list_of_books_.end(); book_it_++) {
                if (book_it_->getISBN() == isbn) user->returnBook(isbn);
            }      
        }
    }
}