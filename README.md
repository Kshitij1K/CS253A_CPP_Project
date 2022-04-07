# CS253A_CPP_Project
To run this project you need CMake, minimum version required is 3.10. It can be installed from the official [CMake website](https://cmake.org/).

This should work both on Linux and Windows systems.

To build this project, simply create a build folder in this folder, and navigate to it in the command prompt. After you have navigated to the build folder in the command prompt, type:
```
cmake ..
cmake --build .
```

This will build the executable file and place it in the bin folder (inside the build folder that you just created). The executable might also be inside another folder named Debug (inside the bin folder) depending on what compiler you use (this happens with MSVS 22).

To run it, navigate to the folder where the executable file (named `main.exe` or `main`) is located, and type
`main.exe` (if you are on windows) or `./main` (if you are on linux) to run it.

The software works on the command line interface, hence you have to give it commands to do the various things required by the assignment. The list of available commands and the syntax to properly run them is given in each prompt when you run the software.

## Command List 

All the data inside the angular brackets should be entered without the angular brackets.
### Login page commands

 - LOGIN \<username> \<password> : Logs you into the system. Please refer to the Pre-Included Data section to see which credentials are already enrolled in the system during initialization. You can, of course, login with the credentials of users that you create when using the software

 - EXIT : Exits the software. Keep in mind is that this software does not read/write data to a file. So there is no permanent storage. Any changes made to the users or books will not be saved.

### Student Portal Commands

- ALLBOOKLIST : Will display all books that are registered in the library system. It is not necessary that the book be in stock.

- ISSUEDBOOKLIST : Will display books that have been issued to this student.
             
- ISBOOKAVAILABLE \<ISBN> : Will check  whether the book with this particular ISBN is available for issue or not

- GETFINE : Will display book wise and total fine accumulated by this student.

- LOGOUT : Will log this student out.

- EXIT : Will exit the software.

### Professor Portal Commands

- ALLBOOKLIST : Will display all books that are registered in the library system. It is not necessary that the book be in stock.

- ISSUEDBOOKLIST : Will display books that have been issued to this professor.
             
- ISBOOKAVAILABLE \<ISBN> : Will check  whether the book with this particular ISBN is available in stock for issue or not.

- GETFINE : Will display book wise and total fine accumulated by this professor.

- LOGOUT : Will log this professor out.

- EXIT : Will exit the software.

### Librarian Portal Commands

- ADDUSER : Will add a user. The prompts to enter the new user's details, such as username, password, type of user, etc. will follow after this.

- UPDATEUSER : Will update a user. The prompts to enter the user's new details, such as username, password, etc. will follow after this. If you want to leave a particular detail unchanged, please leave the input after the corresponding prompt blank and hit enter.

- DELETEUSER \<username> : Will delete a user with this username. REMEMBER: This is IRREVERSIBLE and there will be NO PROMPT after this to confirm whether you really want to delete this user or not. 
- ADDBOOK : Will add a book. The prompts to enter the new book's details, such as ISBN, Title, Author, etc. will follow after this.

- UPDATEBOOK Will update a book. The prompts to enter the book's new details, such as ISBN, Title, Author, etc. will follow after this. If you want to leave a particular detail unchanged, please leave the input after the corresponding prompt blank and hit enter.

- DELETEBOOK \<ISBN> : Will delete a book with this ISBN. REMEMBER: This is IRREVERSIBLE and there will be NO PROMPT after this to confirm whether you really want to delete this book or not. Deleting a book from the database also marks it as returned from all the users that borrowed it.

- ALLBOOKLIST : Will display all books that are registered in the library system. It is not necessary that the book be in stock.

- ALLUSERLIST : Will display all users that are registered in the library system.

- CHECKBOOKSTATUS \<ISBN> : Will check the status of this book. The status includes the book details, the list of users (along with their designation) that this book is issued to, and the whether this book is available in stock for issue or not.

- CHECKISSUEDBOOKS \<username> : Will display the list of all books that are issued by the user having this username.

- ISSUEBOOK \<username> \<ISBN> : Will issue the book having this ISBN to the user having this username. If the book is not in stock, then it will prevent you from issuing it. You also get another prompt asking whether this is the last piece in stock, if it is, it will set the stock to not available (hence no other users will be able to issue this book, unless another user returns it).

- RETURNBOOK \<username> \<ISBN> : Will mark the book having this ISBN as returned, from the user having this username. Will also display the fine that has to be collected from this user for this book. (However, this doesn't actually record a payment, that has to be done by the next command, CLEARFINE) 

- CLEARFINE \<username> \<amount> : Will mark this amount as cleared, from the due fines of this user.

- SHIFTCURRDATE \<number-of-days> : This is a feature that is included solely to make your (the TA testing my code) life easier. When a book is issued, it takes the date from the system time and puts it down as the issue date. Now, you can't really wait for 30 or 60 days to test whether my code produces the correct fine amount for this book, can you? So, what you can do, is shift the current date by as many number of days you want (should be an integer). This command is additive is nature, so if you run `SHIFTCURRDATE 30` twice, the date will  be shifted forward by 60 days in total. You can also go backwards in time by entering a negative integer.

- LOGOUT : Will log this librarian out.

- EXIT : Will exit the software.
    
## Pre-included Data

Since this code doesn't have any way of storing information, I have pre-included some data which get initialized every time the software runs. This is so you (the TA) don't have to tediously run multiple commands to build up the data to test the functionality. I have tried to make the data as diverse as possible, so that there aren't edge cases that are missed out. The data I have included is outlined below. You can, of course, add/modify/delete this data, but just remember that any changes you make to the database will be lost once you exit the software.

### Book data

I'm really sorry, I mistook publication as publication year. I realized this in the end, hence I was unable to change my code to reflect these changes. However, the publication year is also stored as a string, so you can store the publication house's name in this field and the software will run just fine. (Only minor difference will be that the publication house's name will be displayed in front of the publication year)

I have included data for 6 books in the library.
- Title: Embedded Systems,
  Author: Lee and Seshia,
  ISBN: 1263,
  Publication Year: 2017

- Title: Control Theory,
  Author: Donald Kirk,
  ISBN: 7176,
  Publication Year: 2012

- Title: Numerical Methods,
  Author: Richard Wesley,
  ISBN: 2003,
  Publication Year: 1962

- Title: Solid Mechanics,
  Author: Rownland Richard,
  ISBN: 4279,
  Publication Year: 2000

- Title: Fluid Mechanics,
  Author: Frank White,
  ISBN: 5002,
  Publication Year: 1979

- Title: Fluid Mechanics,
  Author: Cengel and Boles,
  ISBN: 3329,
  Publication Year: 2006

### User data

I have included data for 5 students, 3 professors, and 2 librarians. You can log in as any of these users, by using the username and password mentioned. 

- Students
    - Name: Kshitij Kabeer, Username: kabeer, Password: abc, 
      Fines already paid: Rs50, Fines from returned books: Rs100, List of books borrowed along with their dates:
        - ISBN: 7176, Issued on: 25/12/2021
        - ISBN: 2003, Issued on: 25/12/2021

    - Name: Ankit Lakhiwal, Username: ankitl, Password: def,
       Fines already paid: Rs34, Fines from returned books: Rs56, List of books borrowed along with their dates: 
        - ISBN: 1263, Issued on: 30/03/2022
        - ISBN: 7176, Issued on: 01/01/2022
        - ISBN: 5002, Issued on: 02/03/2022

    - Name: Pallab Mahato, Username: pallabm, Password: ghi, 
      Fines already paid: Rs12, Fines from returned books: Rs22, List of books borrowed along with their dates:
        - ISBN: 4279, Issued on: 02/02/2022
        - ISBN: 5002, Issued on: 15/03/2022

    - Name: Kshitiz Chaurasia, Username: kshitchaur, Password: jkl, 
      Fines already paid: Rs45, Fines from returned books: Rs4, List of books borrowed along with their dates:
        - ISBN: 7176, Issued on: 21/09/2021
        - ISBN: 2003, Issued on: 30/01/2022

    - Name: Sourabh Ingale, Username: singale, Password: mno, 
      Fines already paid: Rs0, Fines from returned books: Rs0, List of books borrowed along with their dates:
        - ISBN: 2003, Issued on: 07/12/2021

- Professors
    - Name: Indranil Saha, Username: isaha, Password: pqr, 
      Fines already paid: Rs5, Fines from returned books: Rs10, List of books borrowed along with their dates:
        - ISBN: 1263, Issued on: 20/02/2022
        - ISBN: 7176, Issued on: 22/01/2022
        - ISBN: 2003, Issued on: 01/01/2022

   - Name: Sumit Basu, Username: sbasu, Password: stu, 
      Fines already paid: Rs2, Fines from returned books: Rs15, List of books borrowed along with their dates:
        - ISBN: 4279, Issued on: 01/12/2021
        - ISBN: 3329, Issued on: 17/11/2021 
    
    - Name: Krishnamurthy Muralidhar, Username: kmurli, Password: vwx, 
      Fines already paid: Rs0, Fines from returned books: Rs0, List of books borrowed along with their dates:
        - ISBN: 2003, Issued on: 25/03/2022
        - ISBN: 5002, Issued on: 25/03/2022

- Librarians
    - Name: Gurunath Ramanathan, Username: librarian, Password: 123
    - Name: Suman Ashish, Username: sumana, Password: 456

## How to navigate my code
As you can see, my submitted code has a lot of folders and subfolders (for organizational purposes). 

In the include folder you can find:
- book_database.hpp : Contains declarations for the Book, BookDatabase and Date class
- user.hpp : Contains declarations for the User, Student, Professor and Librarian class, and an enum for storing UserType
- user_database.hpp : Contains declarations for the UserDatabase class
- library.hpp : Contains the declaration for the Library and the State class (State class is purely virtual)
- state_machine.hpp : Contains the declaration for the LoginState, StudentAccessState, ProfessorAccessState and LibrarianAccessState class. Basically, each state in the state machine is a separate class, and inherits from the Base class State (declared in library.hpp). They have access to an object of the library class, which (primarily) has both the databases in it.

In the src folder you can find
- book_database.cpp : Contains definitions for the Book, BookDatabase and Date class
- user.cpp : Contains definitions for the User, Student, Professor and Librarian class, and an enum for storing UserType
- user_database.cpp : Contains definitions for the UserDatabase class
- library.cpp : Contains the definitions for the Library class
- In the states folder
    - login.cpp : Contains the definition for the LoginState class.
    - student_access.cpp : Contains the definition for the StudentAccessState class.
    - professor_access.cpp : Contains the definition for the ProfessorAccessState class.
    - librarian_access.cpp : Contains the definition for the LibrarianAccessState class.
- main.cpp : Contains the main function (that forms the executable).


## Important points to keep in mind

- As mentioned repeatedly, this software DOES NOT save any data on disk and all data is lost when the program exits.

- This software will run on any system, Windows or Linux, as it doesn't use any system specific libraries. The only thing you need to make sure is that you have CMake (with minimum version 3.10) installed, and a compiler that supports minimum C++11 standard.

- I'm sorry, I didn't have time to write comments (I really should start writing comments as I write code), but I have tried to make my code as readable as possible.

- I have included all the functions and atrributes given in the template provided in the question, however, I have changed their names to conform to the Google Style Guide. I am mentioning the functions along with their changed names below, so that you can conform that I have indeed written these functions:

    - class Book database is named BookDatabase
        - List of Books is named list_of_books_
        - Add is named addBook
        - Update is named updateBook
        - Delete is named 
        - Search is named 

    - class User database is named UserDatabase
        - List of Users is named list_of_users_
        - Add is named addBook
        - Update is named updateBook
        - Delete is named
        - Search is named

    - class Book is named Book itself
        - Title is named title_
        - Author is named author_
        - ISBN is named isbn_
        - Publication is named publication_
        - Book_Request is named
        - Show_duedate is named

    - class User is named User itself
        - Name is named name_
        - ID is named id_
        - Password is named password_

    - class Professor is named Professor itself
        - Fine_amount is named fine_amount_
        - List of Books is named list_of_books_
        - Calculate_fine is named calculateFine
        - Clear Fine Amount is named clearFine

    - class Student is named Student itself
        - Fine_amount is named fine_amount_
        - List of Books is named list_of_books_
        - Calculate_fine is named calculateFine
        - Clear Fine Amount is named clearFine

    - class Librarian is named Librarian itself

- In the User Database, the username for each user is UNIQUE. Hence the software will not allow you to add or modify users such that two users have the same username. Also, the username and password both should not contain any spaces (again this too will be checked and the software will disallow any such additions or modifications). Rest all details need not be unique.

- Similarly in the Book Database, the ISBN is unique and should contain no spaces. The software automatically protects against erroneous inputs (and cancels the faulty operation with a prompt) in this case also. Rest all details need not be unique.

- This code can also be accessed (after 11:59PM on 07/04/2022) on this [github link](https://github.com/Kshitij1K/CS253A_CPP_Project).