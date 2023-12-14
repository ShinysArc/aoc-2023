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

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string line;
    vector<string> map;

    while (getline(cin, line)) {
        map.push_back(line);
    }
    string sentinel;
    for (auto i = 0; i < map[0].size(); i++)
        sentinel += '#';
    map.push_back(sentinel);

    moveNorth(map);

    int res = 0;
    for (int y = 0; y < map.size(); y++) {
        res += count(map[y].begin(), map[y].end(), 'O') * (map.size() - y - 1);
    }

    cout << "Part 1: " << res << endl;

    return 0;
}
