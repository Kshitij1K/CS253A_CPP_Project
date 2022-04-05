# CS253A_CPP_Project
To run this project you need CMake, minimum version required is 3.10. It can be installed from the official [CMake website](https://cmake.org/).

This should work both on Linux and Windows systems.

To build this project, simply create a build folder in this folder, and navigate to it in the command prompt. After you have navigated to the build folder in the command prompt, type:
```
cmake ..
cmake --build .
```

This will build the executable file and place it in the bin folder (inside the build folder that you just created).

To run it, navigate to the bin folder, and type
`main.exe` (if you are on windows) or `./main` (if you are on linux) to run it.

The software works on the command line interface, hence you have to give it commands to do the various things required by the assignment. The list of available commands and the syntax to properly run them is given in each prompt when you run the software, so I am not explaining it here.

One thing to keep in mind is that this software does not read/write data to a file. So there is no permanent storage. As Jay mentioned in the Hellot IITK forum, you can make the user fill in the data every time the program runs. A list of 5 books, 5 students, 3 professors, and 2 librarians is already initialized every time the program runs, so you can test out the features without adding any users yourself. Please see the constructor of the UserDatabase class (in user_database.cpp) to see which users are added. Alternatively, you can log in as Gurunath Ramanathan (using the username librarian and password 123) and list all the users, and books as well.