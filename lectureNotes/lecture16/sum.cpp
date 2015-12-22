#include <iostream>

using namespace std;

int rsum_it(int data[], int len);

int main() {
  int data[4] = {8, 6, 7, 9};
  int sum2 = rsum_it(data, 4);

  cout << "The sum is " << sum2 << endl;
  return 0;
}

int rsum_it(int data[], int len) {
  if(len == 1) {
    return data[0];
  } else {
    int sum = rsum_it(data, len - 1);
    return sum + data[len - 1];
  }
}

