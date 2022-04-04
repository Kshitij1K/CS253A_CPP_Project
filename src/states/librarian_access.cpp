#include <state_machine.hpp>

State& LibrarianAccessState::getInstance() {
  static LibrarianAccessState singleton;
  return singleton;
}

void LibrarianAccessState::enter(Library* library) {
    std::cout << "Librarian Portal\n";
}

void LibrarianAccessState::run(Library* library) {
    library->current_state_ = NULL;
}

void LibrarianAccessState::exit(Library* library) {}