
//Approach
//1Initialize the Grid: Create a 10x10 grid to represent the airspace, filling it with dots to indicate empty spaces.

// 2Define Flight Paths: Represent each flight path as a vector of coordinate pairs, where each pair corresponds to a point in the grid.

// 3Check for Intersections:
//    - Implement a function to check if two line segments (flight paths) intersect.
//    - For each pair of flight paths, check all segments to see if they intersect.

// 4.Adjust Paths:
//    - If an intersection is detected, adjust the position of the second flight path slightly (e.g., by moving it up or down) to avoid the intersection.
//    - Recheck the adjusted path to ensure it does not create new intersections.

// 5.Mark the Grid**: For each flight path, mark its coordinates on the grid with a unique character (e.g., 'A', 'B', 'C').

// 6.Display the Grid**: Print the grid representation, showing the marked flight paths and any empty spaces.



#include <iostream>
#include <vector>
#include <utility>

using namespace std;


bool doIntersect(pair<int, int> start1, pair<int, int> end1, pair<int, int> start2, pair<int, int> end2) {
    auto orientation = [](pair<int, int> p, pair<int, int> q, pair<int, int> r) {
        int val = (q.second - p.second) * (r.first - q.first) - (q.first - p.first) * (r.second - q.second);
        if (val == 0) return 0;
        return (val > 0) ? 1 : 2; 
    };

    int o1 = orientation(start1, end1, start2);
    int o2 = orientation(start1, end1, end2);
    int o3 = orientation(start2, end2, start1);
    int o4 = orientation(start2, end2, end1);

    return (o1 != o2 && o3 != o4);
}


void printFlightPath(const vector<pair<int, int>>& flightPath, char marker, char grid[10][10]) {
    for (size_t i = 0; i < flightPath.size(); ++i) {
        int x = flightPath[i].first;
        int y = flightPath[i].second;
        grid[y][x] = marker; 
    }
}

void drawGrid(char grid[10][10]) {
    cout << "Grid Representation:\n";
    for (int i = 9; i >= 0; --i) {
        for (int j = 0; j < 10; ++j) {
            cout << grid[i][j] << ' ';
        }
        cout << endl;
    }
}

int main() {
   
    vector<vector<pair<int, int>>> flightPaths = {
        {{2, 2}, {4, 4}, {6, 6}}, // Flight A
        {{3, 1}, {5, 3}, {7, 1}}, // Flight B
        {{1, 3}, {1, 6}, {4, 5}}  // Flight C
    };

 
    vector<char> flightMarkers = {'A', 'B', 'C'};

   
    char grid[10][10];
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            grid[i][j] = '*'; 
        }
    }

    for (size_t i = 0; i < flightPaths.size(); ++i) {
        for (size_t j = i + 1; j < flightPaths.size(); ++j) {
            bool adjusted = false;
            for (size_t k = 0; k < flightPaths[i].size() - 1; ++k) {
                for (size_t l = 0; l < flightPaths[j].size() - 1; ++l) {
                    if (doIntersect(flightPaths[i][k], flightPaths[i][k + 1], flightPaths[j][l], flightPaths[j][l + 1])) {
                        
                        flightPaths[j][l + 1].second += 1; 
                        adjusted = true;
                    }
                }
            }
            if (adjusted) {
                
                j--; 
            }
        }
    }

   
    for (size_t i = 0; i < flightPaths.size(); ++i) {
        printFlightPath(flightPaths[i], flightMarkers[i], grid);
    }

   
    drawGrid(grid);

    return 0;
}

