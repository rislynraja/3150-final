# 3150-final

instructions for use:

- in order to run, first make sure any necessary c/c++ extensions are installed
- in the terminal, run the line: 
g++ -std=c++17 finalTest.cpp -o test
- this line will compile the tests and put the results in a file called 'test'
- in order to read the file, next run the following line in the terminal: 
./test

notes on files included:

- doctest.h - for testing
- Node.h - Node struct
- TimedSharedPtr.h - timed shared pointer template class
- ControlTimedSharedPtr.h - control timed shared pointer with timing stuff
- finalTest.cpp - file with test cases needed for checking the functions