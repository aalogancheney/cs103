#include "bigint.h"
#include <iostream>
using namespace std;

int main() {
   BigInt a("13");
   BigInt b("42");
   b.add(a);    // increase b by a
   b.println(); // prints 55
   b.add(a);    // increase b by a
   b.println(); // prints 68
   /*a.println(); // prints 13
   a.add(a);    // a = 13 + 13 = 26
   a.add(a);    // a = 26 + 26 = 52
   
   int i = 100;
   while(i > 0) {
    a.add(a);
    a.println();
    i--;
   }*/
   
   BigInt c("9999999999999999999999999999999999");
   BigInt d("3333333333333333333333333333333333");
   c.add(d);
   cout << "c: ";
   c.println();
   
   BigInt e("999999999999999999999");
   BigInt f("2");
   f.add(e);
   cout << "f: ";
   f.println();
}
