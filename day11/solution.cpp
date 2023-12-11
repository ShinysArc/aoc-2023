#include <bits/stdc++.h>

using namespace std;

void getGalaxy(vector<string>& map, vector<pair<int, int>>& galaxies, vector<bool>& rowEmpty, vector<bool>& colEmpty) {
    for (int i = 0; i < map[0].size(); i++) {
        for (int j = 0; j < map.size(); j++) {
            if (map[i][j] == '#') {
                galaxies.push_back({ i, j });
                rowEmpty[j] = false;
                colEmpty[i] = false;
            }
        }
    }
}

int solve1(vector<pair<int, int>>& galaxies, vector<bool>& rowEmpty, vector<bool>& colEmpty) {
    int res = 0;
    for (size_t i = 0; i < galaxies.size(); i++) {
        for (size_t j = i + 1; j < galaxies.size(); j++) {
            int xi = galaxies[i].first, yi = galaxies[i].second;
            int xj = galaxies[j].first, yj = galaxies[j].second;

            int x1 = min(xi, xj), y1 = min(yi, yj);
            int x2 = max(xi, xj), y2 = max(yi, yj);

            for (int x = x1; x < x2; x++) {
                if (colEmpty[x])
                    res += 2;
                else
                    res++;
            }

            for (int y = y1; y < y2; y++) {
                if (rowEmpty[y])
                    res += 2;
                else
                    res++;
            }
        }
    }

    return res;
}

long solve2(vector<pair<int, int>>& galaxies, vector<bool>& rowEmpty, vector<bool>& colEmpty) {
    long res = 0;
    for (size_t i = 0; i < galaxies.size(); i++) {
        for (size_t j = i + 1; j < galaxies.size(); j++) {
            int xi = galaxies[i].first, yi = galaxies[i].second;
            int xj = galaxies[j].first, yj = galaxies[j].second;

            int x1 = min(xi, xj), y1 = min(yi, yj);
            int x2 = max(xi, xj), y2 = max(yi, yj);

            for (int x = x1; x < x2; x++) {
                if (colEmpty[x])
                    res += 1000000;
                else
                    res++;
            }

            for (int y = y1; y < y2; y++) {
                if (rowEmpty[y])
                    res += 1000000;
                else
                    res++;
            }
        }
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string line;
    vector<string> map;
    while (getline(cin, line)) {
        map.push_back(line);
    }

    vector<pair<int, int>> galaxies;
    int N = map[0].size(), M = map.size();

    vector<bool> rowEmpty(N, true), colEmpty(M, true);
    getGalaxy(map, galaxies, rowEmpty, colEmpty);

    int sum1 = solve1(galaxies, rowEmpty, colEmpty);
    long sum2 = solve2(galaxies, rowEmpty, colEmpty);

    cout << "Part 1: " << sum1 << endl;
    cout << "Part 2: " << sum2 << endl;

    return 0;
}
