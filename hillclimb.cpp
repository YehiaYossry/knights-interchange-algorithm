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
void hillclimb(char board[4][3], string target){
    vector<string> path;
int sidewaysCount = 0;
int MAX_SIDEWAYS = 1000;
    int restarts = 0;
    int i = 1;
    int MAX_RESTARTS = 1000;
    string currentState = fromboard(board);
    path.push_back(currentState);
    while (true) { 
        if (currentState == target) {
            cout << "Solution found in " << path.size() << " steps." << endl;
            int step = 1;
            for (const auto& state : path) {
               fromstring(state, board);
                cout << "--- step " << step++ << " ---" << endl;
                printboard(board);
}
           
            return;
        }
        else {
            vector<string> nextStates = nextstate(board);
            string bestState = currentState;
            int bestScore = score(board,target);
            for (const auto& state : nextStates) {
                    char newBoard[4][3];
                fromstring(state, newBoard);
                int newScore = score(newBoard,target);
                if (newScore > bestScore) {
                    bestScore = newScore;
                    bestState = state;
                    sidewaysCount=0;
                }
            }
          if (bestState == currentState) {
    if (sidewaysCount < MAX_SIDEWAYS) {
        vector<string> equalStates;
        for (const auto& state : nextStates) {
            char newBoard[4][3];
            fromstring(state, newBoard);
            if (score(newBoard, target) == bestScore) {
                equalStates.push_back(state);
            }
        }
        if (!equalStates.empty()) {
            currentState = equalStates[rand() % equalStates.size()];
            fromstring(currentState, board);
            path.push_back(currentState);
            sidewaysCount++;
        }
        else {
            sidewaysCount = MAX_SIDEWAYS; 
    } }else {
        restarts++;
if (restarts > MAX_RESTARTS) {
    cout << "Maximum restarts reached. NO solution found." << endl;
   cout << "Total restarts attempted: " << restarts << endl;
    cout << "tried " << path.size() << " steps." << endl;
    return;
}
//randomize the board to try to escape local minumum
for (int k = 0; k < 40; k++) {
    currentState = randomshuffle(currentState);
}
fromstring(currentState, board);
path.clear();
path.push_back(currentState);
sidewaysCount = 0;
    }
}
            
            
            else {
                currentState = bestState;
                path.push_back(currentState);
                fromstring(currentState, board);
                
            }
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
        cout << "starting state:" << endl;
    printboard(board);
    string target = "WWW......BBB";
    hillclimb(board, target);
    return 0;
}
