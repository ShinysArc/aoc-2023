#include <bits/stdc++.h>

using namespace std;

void moveNorth(vector<string>& map) {
    int height = map.size();
    int width = map[0].size();

    for (int x = 0; x < width; x++) {
        int src = 0;
        for (int dst = 0; dst < height; dst++) {
            src = max(src, dst);

            while (map[dst][x] == '.' && map[src][x] != '#') {
                if (map[src][x] == 'O') {
                    map[dst][x] = 'O';
                    map[src][x] = '.';
                }

                src++;
            }
        }
    }
}

void rotate(vector<string>& map) {
    int rows = map.size();
    int cols = map[0].size();

    vector<string> transposed(cols, string(rows, ' '));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            transposed[j][i] = map[i][j];
    }

    for (int i = 0; i < cols; ++i)
        reverse(transposed[i].begin(), transposed[i].end());

    map = transposed;
}

void spinCycle(vector<string>& map) {
    for (auto i = 0; i < 4; i++) {
        moveNorth(map);
        rotate(map);
    }
}

size_t mapHash(const vector<string>& map) {
    size_t result = 0;

    for (size_t y = 0; y < map.size(); ++y) {
        const string& line = map[y];
        hash<string> stringHash;
        result ^= hash<size_t>()(y) ^ stringHash(line);
    }

    return result;
}

pair<size_t, size_t> getLoop(vector<string>& map) {
    size_t i;
    size_t curr = mapHash(map);
    unordered_map<size_t, size_t> seen;

    for (i = 0; seen.find(curr) == seen.end(); i++) {
        seen[curr] = i;
        spinCycle(map);
        curr = mapHash(map);
    }

    return { i - seen[curr], i };
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string line;
    vector<string> map;

    string sentinel;

    while (getline(cin, line)) {
        string newLine = '#' + line + '#';
        map.push_back(newLine);
    }

    for (auto i = 0; i < map[0].size(); i++)
        sentinel.push_back('#');

    map.insert(map.begin(), sentinel);
    map.push_back(sentinel);

    auto loop = getLoop(map);
    for (size_t i = loop.second; (1000000000 - i) % loop.first != 0; i++)
        spinCycle(map);

    int res = 0;
    for (int y = 0; y < map.size(); y++) {
        res += count(map[y].begin(), map[y].end(), 'O') * (map.size() - y - 1);
    }

    cout << "Part 2: " << res << endl;

    return 0;
}
