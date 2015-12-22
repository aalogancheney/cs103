#include <iostream>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])
{
	// Regardless of the angles of the input, there will always be
	// 30 lines, so HEIGHT is constant.
	const int HEIGHT = 30;

	// Asks the user for input
	cout << "Please enter an angle between 15 and 75 degrees: ";
	double theta;
	cin >> theta;

	// The FACTOR does not change either and is dependent on the 
	// angle the user inputs. The constant M_PI is defined under the
	// cmath header file, and is the constant for pi. We use it here
	// since the function tan() accepts input in radians.
	const double FACTOR = tan(theta * M_PI / 180.0);
	
	// Used for debugging purposes:
	// cout << FACTOR << endl;

	// This first for loop will execute a total of HEIGHT times, and this
	// height can be changed later, but for now is set to 30. 
	for(int i = 1; i <= HEIGHT; i++)
	{
		// This inner loop will print '*' until i * FACTOR is reached for
		// each line. This means that there may be some lines that don't 
		// have equal spacing of the lines.
		for(int j = 0; j <= floor(i * FACTOR); j++)
		{
			// This special case will execute only if the inner 
			// for loop would print somewhere between 20 and 30 
			// '*', and instead it will print 20, break, and start
			// the next iteration of the outter for loop.
			if(floor(i * FACTOR) >= 20 && floor(i * FACTOR) <= 30)
			{
				cout << "********************";
				break;
			}
				// This statement will be executed several times so
				// long as the above if condition is not met. 
				cout << '*';
		}
		// This means that each row will be printed on its own row. The 
		// only time this prints is at the end of each line. 
		cout << endl;
	}

	return 0;
}
