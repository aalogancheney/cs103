#include <string>
#include <iostream>
using namespace std;

class recorder {
  public:
    recorder(string initialMessage);
    string playback();
    void record(string newMessage);
  private:
    string savedMessage;
};

// Normally, this would go in recorder.cpp
// This is the constructor.
recorder::recorder(string initialMessage) {
  savedMessage = initialMessage;
}

// Accessor: get back the saved message.
string recorder::playback() {
  return savedMessage;
}

// Mutator: replace saved message.
void recorder::record(string newMessage) {
  savedMessage = newMessage;
}

int main(int argc, char *argv[]) {
  // This initializes the message.
  recorder r("hello");
  // This shows what the message is.
  cout << "The recorded message is: " << r.playback() << endl;
  // This shows the message again.
  cout << "Let's play it again:     " << r.playback() << endl;
  // This puts the string "bonjour" into the saved message.
  r.record("bonjour");
  // This shows what the message now is.
  cout << "The changed message is:  " << r.playback() << endl;  
  // This makes a new recorder variable and initializes it to the string
  // "happy birthday!";     
  recorder card("happy birthday!");
  // This shows the message saved in the object card.
  cout << "The new recorder says:   " << card.playback() << endl; 
  // This reminds us what we have in the object r.      
  cout << "The old one still says:  "  + r.playback() << endl;
  
  return 0;
}
