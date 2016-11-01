Theory of Computing Project 2
Madeline Kusters

# DPDA
Deterministic Push Down Automaton Simulator

Compilation: run make in this directory. This produces an executable called "dpda.exe".

Execution: dpda.exe must be run with 2 command line arguments for the input filenames
					 $./dpda.exe <MachineDescriptionFile> <FileContainingTestStrings>

Output: The name of the machine followed by all transitions rule.
Each test string followed by the list of steps taken through the
machine, and then "Accepted" or "Rejected" for each string.

Test Cases: all of Professor Kogge's test machine files are in this
directory, as well as my student supplied machine called
"TestMachine.txt" it has two corresponding file with test strings
called "TestMachine-Accept.txt" and "TestMachine-Reject.txt"

