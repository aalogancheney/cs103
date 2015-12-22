#include <iostream>
#include <sstream>

using namespace std;

class Change {
  public:
    Change(int total);
    int getQuarters();
    int getDimes();
    int getPennies();
    string getString();
    void addChange(Change &otherAmmount);
  private:
    int _quarters;
    int _dimes;
    int _pennies;
}

Change::Change(int total) {
  _quarters = total / 25;
  total %= 25;
  _dimes = total / 10;
  _pennies = total % 10;
}

int Change::getQuarters() {
  return _q;
}

int Change::getDimes() {
  return _d;
}

int Change::getPennies() {
  return _p;
}

string Change::getString() {
  stringstream ss;
  ss << "Q: " << _q << ", D: " << _d << ", P: " << _p;
  return ss.str();
}

int main(int argc, char *argv[]) {
  

  return 0;
}
