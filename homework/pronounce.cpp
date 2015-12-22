#include <iostream>
using namespace std;

const char* units[] = {"zero", "one", "two", "three", "four",
                             "five", "six", "seven", "eight", "nine",
                             "ten", "eleven", "twelve", "thirteen",
                             "fourteen", "fifteen", "sixteen", "seventeen",
                             "eighteen", "nineteen"};

const char* tenfolds[] = {"", "ten", "twenty", "thirty", "forty",
                               "fifty", "sixty", "seventy", "eighty", "ninety"};

// Function prototype for the pronounce function. 
void pronounce(int n);

int main() {
  int n;
  cin >> n;
  pronounce(n);
  cout << endl; 
}

// Here is the definition for the function. It takes one integer as
// its formal argument and does not have a return type, since the goal
// of the function is to show the user their number in plain English. 
void pronounce(int n) {

  // These are the base cases for when numbers are less than 20. 
  if (n < 20) {
      cout << units[n];
  }
  // These are some more base cases, which cover when a number is less than
  // 100 but is an exact multiple of 10. 
  else if (n % 10 == 0 && n < 100) {
    cout << tenfolds[n / 10];
  }
  // This covers all other cases for numbers less than 100, but that don't fit
  // the above criteria. A hyphen is added where necessary. 
  else if (n < 100) {
    // This will pronounce the tens place
    pronounce(n / 10 * 10);
    // And this if statement checks to see if the number is not divisible by
    // 10, and if not it adds the hyphen and pronounces the correct digit
    // from the first base-case array. 
    if (n % 10 != 0) {
      cout << "-";
      pronounce(n % 10);
    }
  }
  // This will consider when the integer is an exact multiple of 100, and is
  // less than 1000. 
  else if (n % 100 == 0 && n < 1000) {
    pronounce(n / 100);  
    cout << " hundred";
  }
  // This will consider when the integer is less than 1000 but is not an 
  // exact multiple of 100.
  else if (n < 1000) {
    pronounce(n - (n % 100)); // Gets rid of the tens and ones columns.
    // Checks to see if the number is not divisible by 100.
    if (n % 100 != 0) {
      cout << " ";
      pronounce(n % 100);   // Pronounces whatever the remainder is after
    }                       // dividing by 100, which is some 2-digit number
  }                         // and we have already considered those cases. 
  // This will consider when the integer is less than 1 million. 
  else if (n < 1E6) {
    // Here we need to consider when our number is larger than 1000, and we 
    // want to know how many thousand to show. For example, we might want to
    // show "512" thousand, so we need to get rid of the ones, tens, and 
    // hundreds digits.
    pronounce((n - (n % 1000)) / 1000) ;
    cout << " thousand";
    // Then we need to consider if the number is not evenly divisible by
    // 1000
    if (n % 1000 != 0) {
      cout << " ";
      pronounce(n % 1000);
    }
  }
  // This will consider the case when the number is less than 1 billion.
  else if (n < 1E9) {
    pronounce(n / 1E6);
    cout << " million";
    if (n % (int) 1E6 != 0) {
      cout << " ";
      pronounce(n % (int) 1E6);
    }
  }
  // Our default case shows any other number that our system can display,
  // since integers are less than 1 trillion.
  else {
    pronounce(n / 1E9);
    cout << " billion";
    if (n % (int) 1E9 != 0) {
      cout << " ";
      pronounce(n % (int) 1E9);
    }
  }
}
