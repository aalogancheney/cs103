#include <iostream>
#include <vector>

using namespace std;

int *zip(const vector<int> &vector1, const vector<int> &vector2);

int main(int argc, char *argv[]) {
  vector<int> v1;
  v1.push_back(7); v1.push_back(6); v1.push_back(5); v1.push_back(9);
  v1.push_back(2);
  vector<int> v2;
  v2.push_back(4); v2.push_back(5); v2.push_back(8);
  
  int *zipped = zip(v1, v2);
  
  if(zipped == NULL) {
    cout << "There was nothing in the vectors." << endl;
  } else {
    cout << *(zipped) << " " << *(zipped + 1) << " " << *(zipped + 2) << " ";
    cout << endl;
  }
  
  return 0;
}

int *zip(const vector<int> &vector1, const vector<int> &vector2) {
  unsigned int totalSize = vector1.size() + vector2.size();
  if(totalSize == 0) {
    return NULL;
  } 
  
  int *returnArray = new int[totalSize];
  
  for(unsigned int i = 0; i < totalSize; i++) {
    if(i / 2 == 0) {
      if(i / 2 < vector1.size() - 1) {
        *(returnArray + i) = vector1[i / 2];
      } else {
        *(returnArray + i) = vector2[i / 2];
      }
    } else {
      if(i / 2 < vector2.size() - 1) {
        *(returnArray + i) = vector2[i / 2];
      } else {
        *(returnArray + i) = vector1[i / 2];
      }
    }
  }
  
  return returnArray;
}
