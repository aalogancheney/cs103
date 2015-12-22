#include <iostream>
#include <cstdlib>

using namespace std;
int main(int argc, char* argv[])
{
  double sum = 0.0;
  double x;
  int cnt = 1;
  cin >> x;
  while( ! cin.fail() ){
    sum += x;
    cin >> x;
    cnt++;
  }
  cout << sum / cnt << endl;
  return 0;
}
