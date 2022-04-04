#include <state_machine.hpp>


State& ProfessorAccessState::getInstance() {
  static ProfessorAccessState singleton;
  return singleton;
}

void ProfessorAccessState::enter(Library* library) {
    std::cout << "Professor Portal\n";
}

void ProfessorAccessState::run(Library* library) {
    library->current_state_ = NULL;
}

void ProfessorAccessState::exit(Library* library) {}
