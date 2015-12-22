#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
	if(argc < 2){
		cout << argv[0] << " expects a string to be entered";
		cout << " on the command line" << endl;
		return 1;
	}

	cout << "Hello " << argv[1] << ". Welcome to CS103." << endl;
	return 0;
}

// The arguments in main() are used to keep track of the commands at
// the command terminal. The first argument tracks how many commands
// are on the terminal line, and the second argument is an array
// of pointers to char (char *) that stores those items entered there.
// For example, simply typing ./hello will execute the program, but
// the first "if" statement executes since there is only one thing
// entered on the command line. In order for the program to execute
// "successfully" you have to enter at least one more item past the
// command to execute the file hello.
