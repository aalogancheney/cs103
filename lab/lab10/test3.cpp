#include "bigint.h"
using namespace std;

int main(int argc, char *argv[]) {
  BigInt a("A", 16);
  a.printlnBase();
  BigInt b("ABC", 13);
  b.printlnBase();
  
  BigInt c("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 36);
  c.printlnBase();
  c.addBase(a);
  
  BigInt d("A", 16);
  a.addBase(d);
  a.printlnBase();

  return 0;
}
