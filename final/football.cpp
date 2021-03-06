#include <iostream>

using namespace std;

void print_all_possibilities(int times_scored);
void print_scores(int sum, int scores_left);

int main(int argc, char *argv[]) {
  print_all_possibilities(3);

  return 0;
}

void print_all_possibilities(int times_scored) {
  int score = 0;
  print_scores(score + 7, times_scored - 1);
  print_scores(score + 3, times_scored - 1);
  print_scores(score + 2, times_scored - 1);
}

void print_scores(int sum, int scores_left) {
  if(scores_left == 0) {
    cout << sum << endl;
  } else {
    print_scores(sum + 7, scores_left - 1);
    print_scores(sum + 3, scores_left - 1);
    print_scores(sum + 2, scores_left - 1);
  }
}
