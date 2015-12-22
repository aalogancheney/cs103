#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
	srand(time(0));

	for(int i = 0; i < 5; i++) {
		cout << rand() % 20 + 1 << endl;
	}

	return 0;
}
