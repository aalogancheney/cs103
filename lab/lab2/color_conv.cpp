#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

int main()
{
	cout << "Please enter three integers (red, green, and blue): ";
	int red, green, blue;
	cin >> red >> green >> blue;

	double tempWhite = max(red / 255.0, green / 255.0);
	const double WHITE = max(tempWhite, blue / 255.0);

	double cyan = (WHITE - red / 255.0) / WHITE;
	double magenta = (WHITE - green / 255.0) / WHITE;
	double yellow = (WHITE - blue / 255.0) / WHITE;
	double black = 1 - WHITE;

	cout << "The corresponding CMYK values are: " << endl;
	cout << "cyan:   " << setw(12) << cyan << endl;
	cout << "magenta:" << setw(12) << magenta << endl;
	cout << "yellow: " << setw(12) << yellow << endl;
	cout << "black:  " << setw(12) << black << endl;

	return 0;
}
