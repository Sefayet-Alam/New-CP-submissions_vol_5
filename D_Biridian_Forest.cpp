#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

void bfs(const vector<string>& grid, vector<vector<int>>& dist, int startX, int startY, int R, int C) {
    queue<pair<int, int>> q;
    q.push({startX, startY});
    dist[startX][startY] = 0;

    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        int x = current.first;
        int y = current.second;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < R && ny >= 0 && ny < C && grid[nx][ny] != 'T' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.push({nx, ny});
            }
        }
    }
}

int main() {
    int R, C;
    cin >> R >> C;
    vector<string> grid(R);
    int startX, startY, exitX, exitY;

    for (int i = 0; i < R; ++i) {
        cin >> grid[i];
        for (int j = 0; j < C; ++j) {
            if (grid[i][j] == 'S') {
                startX = i;
                startY = j;
            } else if (grid[i][j] == 'E') {
                exitX = i;
                exitY = j;
            }
        }
    }

    vector<vector<int>> distS(R, vector<int>(C, -1));
    bfs(grid, distS, startX, startY, R, C);

    int shortestLength = distS[exitX][exitY];
    if (shortestLength == -1) {
        cout << 0 << endl;
        return 0;
    }

    vector<vector<int>> distE(R, vector<int>(C, -1));
    bfs(grid, distE, exitX, exitY, R, C);

    vector<int> creatures;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (distS[i][j] != -1 && distE[i][j] != -1 && 
                distS[i][j] + distE[i][j] == shortestLength) {
                if (isdigit(grid[i][j]) && grid[i][j] != '0') {
                    creatures.push_back(grid[i][j] - '0');
                }
            }
        }
    }

    sort(creatures.begin(), creatures.end());
    int total = 0;
    int count = 0;
    for (int val : creatures) {
        if (total + val <= shortestLength) {
            total += val;
            count++;
        } else {
            break;
        }
    }

    cout << count << endl;

    return 0;
}