#include <bits/stdc++.h>

using namespace std;

vector<string> transpose(vector<string> grid) {
    vector<string> v(grid[0].size());

    for (int i = 0; i < grid[0].size(); i++) {
        for (int j = 0; j < grid.size(); j++)
            v[i] += grid[j][i];
    }

    return v;
}

int solve1(const vector<string>& grid) {
    int count = 0;
    for (int i = 0; i < grid.size() - 1; i++) {
        int j = 0;
        int reflection = 0;
        while (i - j >= 0 && i + j + 1 < grid.size() && grid[i - j] == grid[i + j + 1]) {
            reflection++;
            j++;
        }

        if (i - j + 1 == 0 || i + j + 1 == grid.size())
            count = max(count, reflection + i - j + 1);
    }

    return count;
}

bool fix_smudge(string_view line1, string_view line2) {
    bool updated = false;
    for (int i = 0; i < line1.size(); i++)
        if (line1[i] != line2[i]) {
            if (updated)
                return false;
            else
                updated = true;
        }
    return true;
}

int solve2(const vector<string>& grid) {
    int count = 0;
    for (int i = 0; i < grid.size() - 1; i++) {
        int j = 0, reflection = 0;
        bool updated = false;
        while (i - j >= 0 && i + j + 1 < grid.size()) {
            if (grid[i - j] == grid[i + j + 1])
                reflection++;
            else if (!updated && fix_smudge(grid[i - j], grid[i + j + 1])) {
                updated = true;
                reflection++;
            } else
                break;
            j++;
        }
        if ((i - j + 1 == 0 || i + j + 1 == grid.size()) && updated)
            count = max(count, reflection + i - j + 1);
    }
    return count;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string line;
    vector<vector<string>> grids;
    vector<string> grid;

    while (getline(cin, line)) {
        if (line.size() == 0) {
            grids.push_back(grid);
            grid.clear();
        }
        else
            grid.push_back(line);
    }

    if (grid.size() > 0)
        grids.push_back(grid);

    int sum1 = 0, sum2 = 0;
    for (auto grid : grids) {
        sum1 += 100 * solve1(grid) + solve1(transpose(grid));
        sum2 += 100 * solve2(grid) + solve2(transpose(grid));
    }

    cout << "Part 1: " << sum1 << endl;
    cout << "Part 2: " << sum2 << endl;

    return 0;
}
