#include <iostream>
#include <cmath>

using namespace std;

// Declaration (function prototype for fact)
int fact(int);

int main(int argc, char *argv[])
{
	cout << "\nPlease enter the number of terms you wish" << endl;
	cout << "to use from the series expansion for sine: ";
	int numberOfTerms;
	cin >> numberOfTerms;

	cout << "\nPlease enter an angle, in radians: ";
	double angleInRadians;
	cin >> angleInRadians;

	double result = 0;

	for(int i = 0; i < numberOfTerms; i++) {
		result = result + (pow(-1, i) * pow(angleInRadians, 2 * i + 1)) / fact(2 * i + 1);
	}

	cout << "\nThe value of sin(" << angleInRadians << ") = " << result << endl;
  	cout << "using " << numberOfTerms << " terms in the series expansion." << endl;
  return 0;
  
}


int fact(int n)
{
  int i;
  int result = 1;
  for(i=1; i <= n; i++){
    result = result * i;
  }
  return result;
}

