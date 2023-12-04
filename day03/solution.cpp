#include <bits/stdc++.h>

using namespace std;

class Part {
public:
    int id;
    int number;
    vector<pair<int, int>> coords;

    Part(int _id, int _number, vector<pair<int, int>> _coords)
        : id(_id), number(_number), coords(_coords) {}
};

vector<Part> parts;

bool isPart(const vector<string>& map, int row, int col) {
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0)
                continue;

            int newRow = row + i;
            int newCol = col + j;

            if (newRow >= 0 && newRow < map.size() && newCol >= 0 && newCol < map[newRow].size()) {
                char currentChar = map[newRow][newCol];

                if (currentChar != '.' && !isdigit(currentChar))
                    return true;
            }
        }
    }

    return false;
}

void solve1(const vector<string>& map) {
    string n;
    bool flag = false;
    vector<pair<int, int>> coords;
    for (auto i = 0; i < map.size(); i++) {
        for (auto j = 0; j < map[0].size(); j++) {
            if (isdigit(map[i][j])) {
                if (isPart(map, i, j)) {
                    flag = true;
                    int col = j;
                    while (isdigit(map[i][col])) {
                        coords.push_back({i, col});
                        if (col == 0)
                            break;
                        col--;
                    }
                    col = j + 1;
                    while (isdigit(map[i][col]) && col < map[i].size()) {
                        coords.push_back({i, col});
                        if (col == map[0].size() - 1)
                            break;
                        col++;
                    }
                }
                n += map[i][j];
            } else if (!n.empty()) {
                if (flag) {
                    sort(coords.begin(), coords.end());

                    auto uniqueEnd = std::unique(coords.begin(), coords.end(),
                        [](const auto& lhs, const auto& rhs) {
                            return lhs.first == rhs.first && lhs.second == rhs.second;
                        });

                    coords.erase(uniqueEnd, coords.end());
                    int id = i * 10 + j;
                    parts.push_back(Part(id, stoi(n), coords));
                    coords.clear();
                }
                n.clear();
                flag = false;
            }
        }
    }

    int res = 0;
    for (auto part : parts) {
        res += part.number;
    }

    cout << "Part 1: " << res << endl;
}

int checkCoords(vector<string> map, vector<Part> parts, pair<int, int> coordsPair) {
    vector<int> gears;
    unordered_set<int> ids;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0)
                continue;

            int newRow = coordsPair.first + i;
            int newCol = coordsPair.second + j;
            pair<int, int> newPair = {newRow, newCol};

            if (newRow >= 0 && newRow < map.size() && newCol >= 0 && newCol < map[newRow].size()) {
                for (const auto& part : parts) {
                    for (const auto& pair : part.coords) {
                        if (pair == newPair) {
                            if (ids.count(part.id) != 0)
                                continue;
                            gears.push_back(part.number);
                            ids.insert(part.id);
                        }
                    }
                }
            }
        }
    }
    if (gears.size() != 2)
        return 0;

    return gears[0] * gears[1];
}

void solve2(const vector<string>& map) {
    int gears = 0;
    for (auto i = 0; i < map.size(); i++) {
        for (auto j = 0; j < map[0].size(); j++) {
            if (map[i][j] == '*') {
                gears += checkCoords(map, parts, {i, j});
            }
        }
    }

    cout << "Part 2: " << gears << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string line;
    vector<string> map;

    while (getline(cin, line)) {
        map.push_back(line);
    }

    solve1(map);
    solve2(map);

    return 0;
}
