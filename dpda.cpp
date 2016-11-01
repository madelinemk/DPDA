// Project 1
// DFA
// Madeline Kusters
// Theory of Computing
// 9/26/2016

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <sstream>
#include <unistd.h>
#include <stack>

typedef struct rule{
  std::string initial_state;
  char input_symbol;
  char stack_top;
  std::string new_state;
  char new_stack_top;
} rule_t;

class DPDA {
public:
  DPDA(std::string filename);
  void process(std::string x);

private:
  std::string current_state;
  std::deque<char> stack;

  std::set<char> alphabet;
  std::set<char> stack_alphabet;
  std::set<std::string> states;
  std::string start_state;
  std::set<std::string> accept_states;
  std::vector<rule_t> transitions;
};

int main(int argc, char* argv[]) {
  // get input files
  std::string machine_spec;
  std::string test_strings;
  if ( argc == 3 ) {
    machine_spec = argv[1];
    test_strings = argv[2];
  } else {
    std::cout << "ERROR: wrong number of input files" << std::endl;
    exit(1);
  }

  // construct DFA object based on the file
  DPDA dpda(machine_spec);

  // open file stream for test strings
  std::cout << std::endl << test_strings << std::endl;
  std::ifstream ifs;
  ifs.open(test_strings);
  if (!ifs.good()) {
    std::cout << "ERROR: Filename \"" << test_strings << "\" invalid." << std::endl;
    exit(1);
  }

  //process each string
  std::string s;
  while (ifs >> s) {
    dpda.process(s);
  }
}



// function definitions for class DPDA

DPDA::DPDA(std::string filename) {
  //** open input filestream
  std::ifstream ifs;
  ifs.open(filename);
  if (!ifs.good()) {
    std::cout << "ERROR: Filename \"" << filename << "\" invalid." << std::endl;
    exit(1);
  }

  //** read each line of the file into line
  std::string line;

  //** Line 1 - name of the DPDA
  getline(ifs, line);
  std::cout << line << std::endl;

  //** Line 2 - input alphabet, comma-seperated, ~ not a valid character
  getline(ifs, line);
  if(line.back() == '\r'){
    line.pop_back();
  }
  std::istringstream ssLine2(line);
  while(ssLine2) {
    std::string a;
    if(!getline(ssLine2,a,',')) {
      break;
    }
    alphabet.insert(a[0]);
  }

  //** Line 3 - stack alphabet
  getline(ifs, line);
  if(line.back() == '\r'){
    line.pop_back();
  }
  std::istringstream ssLine3(line);
  while(ssLine3) {
    std::string a;
    if(!getline(ssLine3,a,',')) {
      break;
    }
    stack_alphabet.insert(a[0]);
  }

  //** Line 4 - states
  getline(ifs, line);
  if(line.back() == '\r'){
    line.pop_back();
  }
  std::istringstream ssLine4(line);
  while(ssLine4) {
    std::string a;
    if(!getline(ssLine4,a,',')) {
      break;
    }
    states.insert(a);
  }

  //** Line 5 - start state
  getline(ifs, line);
  if(line.back() == '\r') {
    line.pop_back();
  }
  start_state = line;

  //** Line 6 - accepting states
  getline(ifs, line);
  if(line.back() == '\r') {
    line.pop_back();
  }
  std::istringstream ssLine6(line);
  while(ssLine6) {
    std::string a;
    if (!getline(ssLine6,a,',')){
      break;
    }
    accept_states.insert(a);
  }

  //** Line 7 and beyond - transitions
  //   Read the rest of the lines in ifs
  while(ifs) {
    if(!getline(ifs,line)) {
      break;
    } else {
      if(line.back() == '\r') {
        line.pop_back();
      }
      std::istringstream ssTransition(line);
      std::string Initial_State_Name, Input_Symbol, Stack_Top, New_State_Name, New_Stack_Top;
      getline(ssTransition, Initial_State_Name, ',');
      getline(ssTransition, Input_Symbol, ',');
      getline(ssTransition, Stack_Top, '|');
      getline(ssTransition, New_State_Name, ',');
      getline(ssTransition, New_Stack_Top);

      rule_t r = {Initial_State_Name, Input_Symbol[0], Stack_Top[0], New_State_Name, New_Stack_Top[0]};
      transitions.push_back(r);
    }
  }

  //** Print transition rules

  std::cout << "Transition rules:\n";
  int index = 0;
  for (auto i : transitions) {
    std::cout << index << ": "
              << i.initial_state << ","
              << i.input_symbol << ","
              << i.stack_top << "|"
              << i.new_state << ","
              << i.new_stack_top << std::endl;
    index++;
  }

  //** Close input filestream
  ifs.close();

  //** Set current state to start state

  current_state = start_state;

}

void DPDA::process(std::string x) {


  //** reset machine to start state and clear stack before processing
  current_state = start_state;
  stack.clear();

  //** print out the string about to be processed
  std::cout << "String: " << x << std::endl;

  bool matched = false;
  int i = 0;
  while( i < (int)x.size() ) {

    int rule;
    matched = false;
    for (rule = 0; rule < (int)transitions.size(); rule++) {
      if (current_state == transitions[rule].initial_state &&
          ( x[i] == transitions[rule].input_symbol || transitions[rule].input_symbol == '~' ) &&
          ( ( !stack.empty() && stack.front() == transitions[rule].stack_top ) || transitions[rule].stack_top == '~') ) {
        matched = true;
        break;
      }
    }

    if (!matched) {
      std::cout << "Rejected" << std::endl << std::endl;
      return;
    }


    //** Apply the rule

    // Read input symbol and advance input if input_symbol is not ~
    if (transitions[rule].input_symbol != '~') {
      i++;
    }

    // Pop from stack if stack_top is not ~

    if (transitions[rule].stack_top != '~' ) {
      if ( !stack.empty()) {
        stack.pop_front();
      } else {
        std::cout << "fuck you " << std::endl;
      }
    }

    // Enter the new state
    current_state = transitions[rule].new_state;

    // Push new_stack_top
    if (transitions[rule].new_stack_top != '~') {
      stack.push_front(transitions[rule].new_stack_top);
    }

    //** Print out the rule to be applied in this format:
    //   <Step#>#<Rule_Number>: <Initial_State_Name>, <Input_Symbol>, <top_of_stack>|
    //   <New_State_Name>, <New_stack>

    std::cout << i << "#" << rule << ": "
              << transitions[rule].initial_state << ", "
              << transitions[rule].input_symbol  << ", "
              << transitions[rule].stack_top     << "| "
              << transitions[rule].new_state     << ", ";

    for (auto i : stack) {
      std::cout << i << " ";
    }
    std::cout << std::endl;
  }

   // print "Accepted" or "Rejected"
  if ( accept_states.find(current_state) != accept_states.end()) {
    std::cout << "Accepted" << std::endl << std::endl;
  } else {
    std::cout << "Rejected" << std::endl << std::endl;
  }

}
