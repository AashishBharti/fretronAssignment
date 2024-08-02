// approch (partially)

// Create a Chessboard class to manage the game state.
// In the class, define methods to add soldiers and set the castle's position.
// Implement a recursive function to explore all possible paths for the castle:
// If the castle reaches its starting position, add the path to the list of unique paths.
// Move the castle forward (down the column):
// If a soldier is encountered, "kill" the soldier and add it to the current path.
// Turn left (move to the left column) if possible.
// Continue exploring paths.
// Jump over soldiers (if any) by moving to the left column.
// Display the number of unique paths and the details of each path.





#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Chessboard {
public:
    Chessboard(int size = 8) : size(size) {}

    void addSoldier(int x, int y) {
        if (find(soldiers.begin(), soldiers.end(), make_pair(x, y)) == soldiers.end()) {
            soldiers.push_back(make_pair(x, y));
        }
    }

    void setCastle(int x, int y) {
        castlePosition = make_pair(x, y);
    }

    vector<vector<string>> findPaths() {
        vector<vector<string>> paths;
        vector<string> currentPath;
        explorePaths(castlePosition.first, castlePosition.second, currentPath, paths);
        return paths;
    }

private:
    int size;
    vector<pair<int, int>> soldiers;
    pair<int, int> castlePosition;

    void explorePaths(int x, int y, vector<string>& currentPath, vector<vector<string>>& paths) {
        // Check if we have returned to the starting position
        if (make_pair(x, y) == castlePosition && currentPath.size() > 1) {
            paths.push_back(currentPath);
            return;
        }

        // Move forward (down the column)
        for (int i = x + 1; i <= size; i++) {
            auto soldierPos = make_pair(i, y);
            auto it = find(soldiers.begin(), soldiers.end(), soldierPos);
            if (it != soldiers.end()) {
                // Kill the soldier
                currentPath.push_back("Kill " + to_string(i) + "," + to_string(y));
                soldiers.erase(it);

                // Turn left (move to the left column)
                if (y > 1) {
                    currentPath.push_back("Turn Left " + to_string(i) + "," + to_string(y - 1));
                    explorePaths(i, y - 1, currentPath, paths);
                    currentPath.pop_back(); // Backtrack
                }

              
                explorePaths(i, y, currentPath, paths);
                currentPath.pop_back();
                soldiers.push_back(soldierPos); 
            }
        }

        
        for (int j = y - 1; j > 0; j--) {
            auto soldierPos = make_pair(x, j);
            auto it = find(soldiers.begin(), soldiers.end(), soldierPos);
            if (it != soldiers.end()) {
                // Kill the soldier
                currentPath.push_back("Kill " + to_string(x) + "," + to_string(j));
                soldiers.erase(it);

                // Turn left (move to the left column)
                if (j > 1) {
                    currentPath.push_back("Turn Left " + to_string(x) + "," + to_string(j - 1));
                    explorePaths(x, j - 1, currentPath, paths);
                    currentPath.pop_back(); // Backtrack
                }

                currentPath.pop_back(); // Backtrack
                soldiers.push_back(soldierPos); // Restore soldier
            }
        }
    }
};

int main() {
    Chessboard board;
    int numSoldiers;

    cout << "Enter number of soldiers: ";
    cin >> numSoldiers;
    cin.ignore(); // Clear the newline character from the buffer

    for (int i = 0; i < numSoldiers; i++) {
        string coords;
        cout << "Enter coordinates for soldier " << (i + 1) << ": ";
        getline(cin, coords);
        int x, y;
        char comma;
        stringstream ss(coords);
        ss >> x >> comma >> y;
        board.addSoldier(x, y);
    }

    string castleCoords;
    cout << "Enter the coordinates for your \"special\" castle: ";
    getline(cin, castleCoords);
    int x, y;
    char comma;
    stringstream ss(castleCoords);
    ss >> x >> comma >> y;
    board.setCastle(x, y);

    auto paths = board.findPaths();
    int numPaths = paths.size();
    cout << "\nThanks. There are " << numPaths << " unique paths for your 'special castle'\n";

    for (size_t idx = 0; idx < paths.size(); idx++) {
        cout << "Path " << (idx + 1) << "\n";
        cout << "=======\n";
        for (const auto& action : paths[idx]) {
            cout << action << "\n";
        }
        cout << "\n";
    }

    return 0;
}