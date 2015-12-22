#include <string>
#include <vector>
using namespace std;

class BigInt {
   public:
      BigInt(string s);   // convert string to BigInt
      BigInt(string s, int b);
      void println();     // print this BigInt and a newline
      void printlnBase();
      void add(BigInt c); // add another BigInt to this one
      void addBase(BigInt d);
   private:
      vector<int> vInt;
      int base;
};
