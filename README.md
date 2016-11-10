My implementation for this challenge is written in C++ and uses the GNU GCC compiler for C++ g++ with C++11 or greater. I am currently using GCC 4.2.1 on my computer, but I imagine any version with C++11 would work. In addition it uses the default STL that comes with linux as well as the standard c++ library. 

My code is set up with a main function and two helper classes, payment verifier and user node.  Payment verifier handles processing of the input stream and batch files as well as outputs to the three output files.  User node defines and implements a custom graph user node class.  Run time has been optimized, with constant
    user node lookup time by usage of a map, and minimal graph searching through a BFS starting at the from
    user node based on entry in the file.  The graph is created through dynamic memory allocation of new nodes.
    Currently they are only freed upon program termination, as it was not desired to remove users based on the
    challenge specification. However, for completeness I included a delete user function which, while not used, 
    could be used to free node memory if needed.

I have included 7 additional unit tests to the 1 default given, and all are passing with run_tests.sh.  They cover a variety of basic expected cases as well as corner cases for input.

As a side note, for the sake of brevity I am recompiling each time in the run.sh before running a unit test.  Given that the compile time and code size are minimal I did not think this would be an issue.  However in a more realistic and large scale project, I would check for code change and reuse the previous build through a makefile.