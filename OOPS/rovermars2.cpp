#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <unordered_set>

using namespace std;


// created a list that stores the final coordinates of the possible position. Then will display the number of unique positions
class coordinates{
public:
    int x;
    int y;
    coordinates(int X, int Y) : x(X), y(Y){}

    bool operator==(const coordinates &other) const {
        return x == other.x && y == other.y;
    }
};

vector<coordinates> VisitedList;



const int MAX_STEPS = 64; // maximum steps to move


bool isValid(int r, int c, vector<vector<char>>& mapMatrix, int ROWS, int COLS) {
    return r >= 0 && r < ROWS && c >= 0 && c < COLS && mapMatrix[r][c] != '#';
}
namespace std {
    template <>
    struct hash<coordinates> {
        std::size_t operator()(const coordinates &c) const {
            // Use a simple hashing method for demonstration
            return std::hash<int>()(c.x) ^ (std::hash<int>()(c.y) << 1);
        }
    };
}

void doTask(int r, int c, vector<vector<char>>& mapMatrix, int ROWS, int COLS, int NumberOfStepsLeft){
    if(isValid(r, c, mapMatrix, ROWS, COLS)){
        if(NumberOfStepsLeft == 0){
            VisitedList.push_back(coordinates(r , c));
        }
        else if(NumberOfStepsLeft > 0){
            doTask(r-1, c, mapMatrix, ROWS, COLS, NumberOfStepsLeft-1 );
            doTask(r, c-1, mapMatrix, ROWS, COLS, NumberOfStepsLeft-1 );
            doTask(r+1, c, mapMatrix, ROWS, COLS, NumberOfStepsLeft-1 );
            doTask(r, c+1, mapMatrix, ROWS, COLS, NumberOfStepsLeft-1 );
        }
    }
    else return;
}

int main() {
    int rows;
    int columns;

    cout << "Enter the number of rows: "; cin >> rows;
    cout << "Enter the number of columns: "; cin >> columns;

    vector<vector<char>> mapMatrix(rows, vector<char>(columns));

    cout << "Provide the map: " << endl;
    for(int i=0;i<rows;i++){
        for(int j=0; j<columns; j++){
            cin >> mapMatrix[i][j];
        }
    }

    // Find the starting position 'S'
    int startR, startC;
    bool found = false;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (mapMatrix[r][c] == 'S') {
                startR = r;
                startC = c;
                found = true;
                break;
            }
        }
        if (found) break;
    }

    doTask(startR, startC, mapMatrix, rows, columns, MAX_STEPS);

    unordered_set<coordinates> uniqueElements(VisitedList.begin(), VisitedList.end());
    cout << "Number of possible positions: " << uniqueElements.size() << endl;

    return 0;
}
