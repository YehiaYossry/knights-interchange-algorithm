#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <set>
#include <map>
#include <algorithm> 
#include <cstdlib>
#include <random>
#include <ctime>
#include <cmath>
using namespace std;
void intizalise (){
    char arr[4][3]={
  {'B','B','B'},  // (top)
  {'.','.','.'},  
  {'.','.','.'},  
  {'W','W','W'}   // (bottom)
}
;}
vector<pair<int,int>> getValidMoves(char board[4][3], int row, int col) {
    vector<pair<int,int>> validMoves;
    if(row+2 < 4 && col+1 < 3 && board [row+2][col+1] == '.' ){
        validMoves.push_back(make_pair(row+2,col+1)); // up right
    }
     if(row+2 < 4 && col-1 >= 0 && board [row+2][col-1] == '.' ){
        validMoves.push_back(make_pair(row+2,col-1)); // up left
    }
       if(row-2 >= 0 && col-1 >= 0 && board [row-2][col-1] == '.'){
        validMoves.push_back(make_pair(row-2,col-1)); // down left
    }
       if(row-2 >= 0 && col+1 < 3 && board [row-2][col+1] == '.'){
        validMoves.push_back(make_pair(row-2,col+1)); // down right
    }
     if(row+1 < 4 && col+2 < 3 && board [row+1][col+2] == '.'){
        validMoves.push_back(make_pair(row+1,col+2)); // right up
    }
     if(row-1 >= 0 && col+2 < 3 && board [row-1][col+2] == '.'){
        validMoves.push_back(make_pair(row-1,col+2)); // right down
    }
         if(row+1 < 4 && col-2 >= 0 && board [row+1][col-2] == '.'){
        validMoves.push_back(make_pair(row+1,col-2)); // left up
    }
     if(row-1 >= 0 && col-2 >= 0 && board [row-1][col-2] == '.'){
        validMoves.push_back(make_pair(row-1,col-2));} // left down

    return validMoves;
}
 void fromstring(string state, char arr[4][3] ) {    
    int counter = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            arr[i][j] = state[counter++];
        }
    }
}
string fromboard(char board[4][3]){
    string state;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            state += board[i][j];
        }
    }
    return state;
}
int score(char board[4][3],string target ){
int score =0;
int distance = 0;
char targetboard[4][3] ;
fromstring(target,targetboard);
for (int i=0;i<4;i++){
    for(int j =0 ; j<3 ; j++){
            if (board[i][j] == 'W') {
                distance += abs(i - 3); 
            } else if (board[i][j] == 'B') {
                distance += abs(i - 0); 
            }
            if (board[i][j] == targetboard[i][j] && board[i][j] != '.') {
                score++;
            }
            
        }
    }

return 18-distance+score;
}


vector<string> nextstate( char arr[4][3]  ){
    int i,j;
    vector<string> states;
for (i=0;i < 4 ;i++){
    for (j=0;j <3; j++){
        if (arr[i][j] == 'B' || arr[i][j] == 'W'){
            vector<pair<int,int>> validMoves = getValidMoves(arr, i, j);
            for (const auto& move : validMoves) {
                char newState[4][3];
                memcpy(newState, arr, sizeof(newState));
                swap(newState[i][j], newState[move.first][move.second]);
                string newStateStr = fromboard(newState);
                states.push_back(newStateStr);
            }
        }
    }
} 
    return states;
}
string randomshuffle(string state){
vector <string> nextStates;
char board[4][3];
fromstring(state, board);
nextStates = nextstate(board);
return nextStates[rand() % nextStates.size()];
}

void printboard(char board[4][3]){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        
        cout << endl;
    }
    return;
}
void simulatedAnnealing(char board[4][3], string target) {
    vector<string> path;
    int restarts = 0;
    int MAX_RESTARTS = 200;
    double temperature = 1000.0;
    double coolingRate = 0.995;
    double minTemperature = 0.1;
    
    string currentState = fromboard(board);
    path.push_back(currentState);
    
    while (true) {
       if (currentState == target) {
    cout << "Solution found in " << path.size() << " steps." << endl;
    cout << "Final state:" << endl;
    printboard(board);
    return;
}
        vector<string> nextStates = nextstate(board);
        if (nextStates.empty()) continue;

        string randomState = nextStates[rand() % nextStates.size()];
        char randomBoard[4][3];
        fromstring(randomState, randomBoard);

        int currentScore = score(board, target);
        int randomScore = score(randomBoard, target);
        int delta = randomScore - currentScore;

        if (delta > 0 || (double)rand() / RAND_MAX < exp((double)delta / temperature)) {//a luck chnace to see if to accept the worst state
            currentState = randomState;
            fromstring(currentState, board);
            path.push_back(currentState);
        }

        temperature *= coolingRate; // decreasing the tolerance as time goes

        if (temperature < minTemperature) { // if temprature is too low, we are likely stuck in a local minimum, so we restart
            restarts++;
            if (restarts > MAX_RESTARTS) {
                cout << "No solution found." << endl;
                return;
            }
            temperature = 1000.0; // reset the tempreture to strat from a new place
            for (int k = 0; k < 40; k++) {
                currentState = randomshuffle(currentState);
            }
            fromstring(currentState, board);
            path.clear();
            path.push_back(currentState);
        }
    }
}
int main() {
    srand(time(nullptr));
    char board[4][3] = {
        {'B','B','B'},
        {'.','.','.'},
        {'.','.','.'},
        {'W','W','W'}
    };
    cout << "-------------Simulated Annealing-------------" << endl;
    cout << "Starting state:" << endl;
    printboard(board);
    cout << "-------------" << endl;
    string target = "WWW......BBB";
    simulatedAnnealing(board, target);
    return 0;
}
