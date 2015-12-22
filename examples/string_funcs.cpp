#include <iostream>
using namespace std;

int strlen(char str[]);
void strcpy(char dst[], char src[]);

int main(int argc, char *argv[])
{
  char mystr[51];
  char copiedstr[51];
  cout << "Enter a string of less than 50 characters" << endl;
  cin >> mystr;
  cout << "Length of provided string is " << strlen(mystr) << endl;
  strcpy(copiedstr, mystr);
  cout << "Copied string is\n" << copiedstr << endl;
  
  return 0;
}

int strlen(char str[])
{
  int i = 0;

  while(str[i] != '\0') {i++;}

  return i;
}

void strcpy(char dst[], char src[])
{
  int stringLength = strlen(src);

  for(int i = 0; i < stringLength; i++)
    {
      dst[i] = src[i];
    }
  dst[stringLength] = '\0';
}
