#include <iostream>
#include "maze_io.h"
using namespace std;

// This function searches the maze for the shortest path. It will return an
// integer to indicate whether or not it was successful. It takes a char ** as
// its first argument, which is the maze. It also takes the size of the
// maze in row and col, which are the second and third arguments.
int maze_search(char **, int, int);

// This function is used to recursively search the maze for the shortest
// path. The arguments, in order, are: the maze to be searched, the number
// of rows in the maze, the number of columns in the maze, the BFSQ array that
// holds our priority queue, the current row, the current col, the head that
// deletes items from the BFSQ array, the tail used to write to the BFSQ array,
// the array of visited locations, and the predecessor array.
void findPath(char **maze, int row, int col, int **BFSQ,
              int currentRow, int currentCol, int *head, int *tail,
              bool **visitedLocations, int *predecessor);

// This function is used to recursively trace back through the predecessor
// array to write the '*' symbol in the maze to indicate the shortest path.
void tracePath(char **maze, int **BFSQ, int *predecessor, int trace);

// This function is used to delete the dynamically allocated arrays used in
// this program. A function is used because there are multiple points where
// we might need to deallocate the memory.
void deallocateMemory(int **BFSQ, int *predecessor, bool **visitedLocations,
                      int rows, int cols);

int main(int argc, char *argv[])
{
    // Declares the three integer variables used here in main.
    int rows, cols, result;

    // Checks to see if the number of arguments is less than 3, in which case
    // it will show the user what they need to enter for a valid function call.
    if(argc < 3) {
        cerr << "Usage: ./maze in_filename out_filename" << endl;
        return 1;
    }

    // Declares the array mymaze by calling the function read_maze(), which will
    // read the maze from the file name given by argv[1]. The second and third
    // arguments are passed by reference so that the variables rows and cols
    // from above are filled from the information in the file.
    char** mymaze = read_maze(argv[1], &rows, &cols);

    // This will give us the result of searching the maze given by mymaze for
    // the shortest path.
    result = maze_search(mymaze, rows, cols);

    // If the result is 1, then we have found a path through the maze, which is
    // the shortest path because of our algorithm.
    if(result == 1) {
        cout << "Path successfully found!" << endl;
        // This function will print the maze to the screen, which now has the
        // appropriate characters replaced with '*'.
        print_maze(mymaze, rows, cols);
        // This function will write the resulting maze to the file given as the
        // third command line argument.
        write_maze(argv[2], mymaze, rows, cols);
    }
    // If the result is 0, this means that there was no path that could be
    // found for the given maze. this could be because the start and end points
    // are unconnectable because of walls in the maze.
    else if (result == 0) {
        cout << "No path could be found!" << endl;
    }
    // The function maze_search() will return -1 if there was an error, such as
    // there being no start or end points in the maze.
    else {
        cout << "Error occurred during search!" << endl;
    }

    // Since the array mymaze is a dynamically allocated 2D array
    // we need to delete each element of that array as well as the
    // array itself. The 'for' loop here goes through each element of
    // the array, and the final delete statement gets rid of the whole
    // array itself. If we did not use the 'for' loop here, we would
    // lose access to each element of the array and have no way to
    // deallocate the memory.
    for(int i = 0; i < rows; i++) {
        delete [] *(mymaze + i);
    }

    delete [] mymaze;

    return 0;
}

// This function is used to search the maze. It will return a 1 if it is
// successful in finding the shortest path, a 0 if no path exists, and a -1 if
// there is an error in the maze (i.e., there is no start or end point).
// If a path is found, we will overwrite the '.' with '*', leaving the S
// and F characters.
int maze_search(char **maze, int rows, int cols)
{
    // These two boolean variables indicate whether or not we have found the
    // start and finish points in the maze. They are initially set to false,
    // and will be changed later as appropriate.
    bool foundStart = false;
    bool foundFinish = false;

    // Here we dynamically allocate the Breadth First Search Queue array, which
    // will hold rows * cols, 2 dimensional elements. This is the worst case
    // scenario where we will have to read through each element of the maze in
    // order to find the shortest path.
    int **BFSQ = new int*[rows * cols];
    for(int i = 0; i < rows * cols; i++) {
        *(BFSQ + i) = new int[2];
    }

    // This statement declares the predecessor array, which keeps track of how
    // each element in the BFSQ array was reached, i.e. what element came before
    // it.
    int *predecessor = new int[rows * cols];

    // These are the two variables which point to locations inside the BFSQ array,
    // where the tail will indicate where the array is currently writing, and
    // the head points to the coordinate being read.
    int tail = 0;
    int head = 0;

    // This array is dynamically allocated to keep track of the places we have
    // visited so far. The array consists of booleans because all we need to
    // know is whether or not we have visited there. Each element is filled
    // with a false value, since we still have to visit spaces.
    bool **visitedLocations = new bool*[rows];
    for(int i = 0; i < rows; i++) {
        *(visitedLocations + i) = new bool[cols];
        for(int j = 0; j < cols; j++) {
            *(*(visitedLocations + i) + j) = false;
        }
    }

    // Here we look to see where the starting position is. We walk through each
    // coordinate of the maze, and when we find the 'S' character we make the
    // foundStart variable true, we remember where it is by storing
    // the coordinate in the BFSQ as the first element, and we also mark it as
    // a location we have visited.
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            // cout << *(*(maze + i) + j) << endl;
            if(*(*(maze + i) + j) == 'S') {
                foundStart = true;
                **(BFSQ) = i;
                *(*(BFSQ) + 1) = j;
                *(predecessor + tail) = head;
                *(*(visitedLocations + i) + j) = true;
                tail++;
            }
            // Here we check to see if we can find the finish tile, and if so we set
            // the foundFinish variable to true.
            if(*(*(maze + i) + j) == 'F') {
                foundFinish = true;
            }
        }
    }

    // This checks to see if we have successfully found the start and finish of
    // the maze. If one or both are not found, then we return -1, which indicates
    // to main() there was an error in the maze file.
    if(!foundStart || !foundFinish) {
        deallocateMemory(BFSQ, predecessor, visitedLocations, rows, cols);
        return -1;
    }

    findPath(maze, rows, cols, BFSQ, **(BFSQ), *(*(BFSQ) + 1), &head, &tail,
             visitedLocations, predecessor);

    // This statement looks to see if we have read all of the possible neighbors
    // from the start of the array, but could not get to the finish, which means
    // there are walls blocking the path to F. If this is the case we return 0.
    if(head == tail &&
            *(*(maze + **(BFSQ + tail - 1)) + *(*(BFSQ + tail - 1) + 1)) != 'F') {
        deallocateMemory(BFSQ, predecessor, visitedLocations, rows, cols);
        return 0;
    }

    // Otherwise, a path exists, and we use this function to recursively trace
    // the path. Notice that we use the head variable as our last parameter.
    // This is because the element that found the end of the maze was the
    // coordinate stored at the position pointed to by head.
    tracePath(maze, BFSQ, predecessor, head);

    deallocateMemory(BFSQ, predecessor, visitedLocations, rows, cols);

    // The only other option at this point is that we have found a path, and
    // therefore we return 1.
    return 1;
}

// This function will deallocate the memory that was dynamically created in
// the maze_search() function.
void deallocateMemory(int **BFSQ, int *predecessor, bool **visitedLocations,
                      int rows, int cols) {
    for(int i = 0; i < rows * cols; i++) {
        delete [] *(BFSQ + i);
    }
    delete [] BFSQ;

    delete [] predecessor;

    for(int i = 0; i < rows; i++) {
        delete [] *(visitedLocations + i);
    }
    delete [] visitedLocations;
}

// This function recursively fills in the information in our array maze with
// the shortest path.
void tracePath(char **maze, int **BFSQ, int *predecessor, int trace) {
    // This is our base case, for when we have reached the front of the BFSQ
    // array.
    if(trace == 0) {
        return;
    }
    // This other portion will run and replace the information in the array with
    // the '*' as appropriate, change the trace variable as necessary, and call
    // the function again with the updated trace value. The trace variable is
    // dependent on the value in the predecessor array.
    else {
        *(*(maze + *(*(BFSQ + trace))) + *(*(BFSQ + trace) + 1)) = '*';
        trace = *(predecessor + trace);
        tracePath(maze, BFSQ, predecessor, trace);
    }
    return;
}

// This is where the bulk of the program does its magic. The parameters for the
// function are described at the prototype at the top of this file.
void findPath(char **maze, int row, int col, int **BFSQ,
              int currentRow, int currentCol, int *head, int *tail,
              bool **visitedLocations, int *predecessor) {
    // One of our base cases is when the head has caught up to the tail, which
    // means there is no path that can be found.
    if(*head == *tail) {
        return;
    }

    // Each large 'if' statement below checks one of the neighbors of the current
    // position in the maze. I will comment one of the large 'if' statements and
    // leave the others, as they are all similar to each other.
    //
    // This 'if' block checks the neighbor above the current position in
    // the maze. The 'if' statement checks that the value above is within the
    // scope of the maze, and it also checks to see if it has been visited yet.
    if(currentRow - 1 >= 0 &&
            !*(*(visitedLocations + currentRow - 1) + currentCol)) {
        // If the location hadn't been visited, it is now marked as visited.
        *(*(visitedLocations + currentRow - 1) + currentCol) = true;
        // Here we check to see if we have reached the finish of the maze, which is
        // the base case we need to check for each neighbor. If we have found the
        // end, then we return out of the recursive structure.
        if(*(*(maze + currentRow - 1) + currentCol) == 'F') {
            return;
        }
        // Here we check if the location above the current position is a wall, and
        // if it is, it does nothing.
        else if(*(*(maze + currentRow - 1) + currentCol) == '#') {}
        // Here, we have reached the base case of the if-else branch, which is
        // guaranteed to be the only other result, since we haven't visited this
        // location before, since it is not a wall nor is it the finish, and we
        // already checked that it is within the bounds of the maze.
        else {
            // These two lines set the value in the BFSQ at the location pointed to
            // by tail equal to the coordinate of the neighbor above the current
            // location.
            **(BFSQ + *tail) = currentRow - 1;
            *(*(BFSQ + *tail) + 1) = currentCol;
            // Here, we set the predecessor array based on the head variable.
            *(predecessor + *tail) = *head;
            // Finally we increment the tail value to point to the next element of
            // the BFSQ array.
            (*tail)++;
        }
    }
    // Same as above, but we check the lower neighbor.
    if(currentRow + 1 < row &&
            !*(*(visitedLocations + currentRow + 1) + currentCol)) {
        *(*(visitedLocations + currentRow + 1) + currentCol) = true;
        if(*(*(maze + currentRow + 1) + currentCol) == 'F') {
            return;
        } else if(*(*(maze + currentRow + 1) + currentCol) == '#') {}
        else {
            **(BFSQ + *tail) = currentRow + 1;
            *(*(BFSQ + *tail) + 1) = currentCol;
            *(predecessor + *tail) = *head;
            (*tail)++;
        }
    }
    // Same as above, but we check the left neighbor.
    if(currentCol - 1 >= 0 &&
            !*(*(visitedLocations + currentRow) + currentCol - 1)) {
        *(*(visitedLocations + currentRow) + currentCol - 1) = true;
        if(*(*(maze + currentRow) + currentCol - 1) == 'F') {
            return;
        } else if(*(*(maze + currentRow) + currentCol - 1) == '#') {}
        else {
            **(BFSQ + *tail) = currentRow;
            *(*(BFSQ + *tail) + 1) = currentCol - 1;
            *(predecessor + *tail) = *head;
            (*tail)++;
        }
    }
    // Same as above, but we check the right neighbor.
    if(currentCol + 1 < col &&
            !*(*(visitedLocations + currentRow) + currentCol + 1)) {
        *(*(visitedLocations + currentRow) + currentCol + 1) = true;
        if(*(*(maze + currentRow) + currentCol + 1) == 'F') {
            return;
        } else if(*(*(maze + currentRow) + currentCol + 1) == '#') {}
        else {
            **(BFSQ + *tail) = currentRow;
            *(*(BFSQ + *tail) + 1) = currentCol + 1;
            *(predecessor + *tail) = *head;
            (*tail)++;
        }
    }

    // We always move the head forward, because after all of the 'if' statements
    // have executed we have completely processed the location pointed to by the
    // head variable, and we move to the next one.
    (*head)++;

    // The last step is to recursively call this function again. Here, the only
    // parameters that changed are the head and tail variables, which decide what
    // we do with the information we have. We still pass all of the same arrays
    // to the function, but we read/write to different locations based on the
    // head and tail variables.
    findPath(maze, row, col, BFSQ, **(BFSQ + *head), *(*(BFSQ + *head) + 1),
             head, tail, visitedLocations, predecessor);
}
