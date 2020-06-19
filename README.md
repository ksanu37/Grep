# Grep
A C++ Program to implement the functionality of the grep command.

The GrepCommandLine.cpp takes input from the terminal window and perfoms the grep operation. 

How to test:
1. Save the GrepCommandLine.cpp and the text file you want to run the grep command on, in the same directory, for the sake of simplicity. 
2. If not already installed, install and configure the cpp compiler in the system.
3. Open terminal window and navigate to the directory where the GrepCommandLine.cpp file is saved, using cd command
4. Run the command -> g++ GrepCommandLine.cpp -o grep  (This compiles the .cpp file and creates an object file which can be executed)
5. Run the command in this format -> ./grep grep -i pattern filename.txt  or ./grep grep pattern filename.txt 
6. This will return the output in the terminal window, starting with something like ######## RESULT ########
