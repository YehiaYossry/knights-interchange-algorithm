#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <set>
#include <map>
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

vector<string> nextstate( char arr[4][3]  ){
    int i,j;
    vector<string> states;
for (i=0;i < 4 ;i++){
    for (j=0;j <3; j++){
        if (arr[i][j] == 'B' || arr[i][j] == 'W'){
            vector<pair<int,int>> validMoves = getValidMoves(arr, i, j);
            for (const auto& move : validMoves) {
                char newState[4][3];
                memcpy(newState, arr, 12*sizeof(char));
                swap(newState[i][j], newState[move.first][move.second]);
                string newStateStr = fromboard(newState);
                states.push_back(newStateStr);
            }
        }
    }
} 
    return states;
}
string bredthfirstsearch(char board[4][3], string target){
    set<string> visited;
    map<string,string> parent;
    queue<string> q;
    string start = fromboard(board);
    q.push(start);
    visited.insert(start);
    while (!q.empty()) {
        string currentState = q.front();
        q.pop();
        if (currentState == target) {
            return currentState; // Found the target state
        }
        char currentBoard[4][3];
        fromstring(currentState, currentBoard);
        vector<string> nextStates = nextstate(currentBoard);
        for (const string& nextState : nextStates) {
            if (visited.find(nextState) == visited.end()) {
                visited.insert(nextState);
                q.push(nextState);
                parent[nextState]=  currentState; // Store the parent state for path reconstruction]
            }
        }

    }
return "no solution found";
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
int main() {
    char board[4][3] = {
        {'B','B','B'},
        {'.','.','.'},
        {'.','.','.'},
        {'W','W','W'}
    };
    cout << "-------------Breadth-First Search-------------" << endl;
     cout << "starting state:" << endl;
    printboard(board);
    cout << "-------------" << endl;
    string target = "WWW......BBB";
    string result = bredthfirstsearch(board, target);
    char finalBoard[4][3];
    fromstring(result, finalBoard);
    cout << "Target state:" << endl;
    printboard(finalBoard);
    return 0;
}
