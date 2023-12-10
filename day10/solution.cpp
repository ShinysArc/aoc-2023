#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

using namespace std;

map<char, vector<long>> nav = {{'|', {0, -1, 0, 1}}, {'-', {-1, 0, 1, 0}}, {'L', {0, -1, 1, 0}},
        {'J', {0, -1, -1, 0}}, {'7', {0, 1, -1, 0}}, {'F', {0, 1, 1, 0}}};

vector<long> findStart(const vector<string>& lines) {
    for (size_t i = 0; i != lines.size(); ++i) {
        size_t pos = lines[i].find('S');
        if (pos != string::npos)
            return {static_cast<long>(pos), static_cast<long>(i)};
    }

    return {-1, -1};
}

vector<vector<long>> getPointers(const vector<string>& lines, long start_x, long start_y, long width, long height) {
    vector<vector<long>> pointers;

    for (int i = -1; i <= 1; ++i) {
        long flag_x = start_x + i;
        for (int j = -1; j <= 1; ++j) {
            long flag_y = start_y + j;
            if ((flag_y < 0 || flag_y >= height) || (flag_x < 0 || flag_x >= width))
                continue;

            char c = lines[flag_y][flag_x];
            if (c == '.' || c == 'S')
                continue;

            auto off = nav[c];
            if ((flag_x + off[0] == start_x && flag_y + off[1] == start_y) ||
                (flag_x + off[2] == start_x && flag_y + off[3] == start_y))
                pointers.push_back({flag_x, flag_y});
        }
    }

    return pointers;
}

long getSilver(vector<string>& lines, long width, long height, vector<bool>& visited) {
    long silver = 1;
    vector<long> start = findStart(lines);
    visited[start[1] * width + start[0]] = true;

    vector<vector<long>> pointers = getPointers(lines, start[0], start[1], width, height);

    while (true) {
        for (auto &p : pointers) {
            visited[p[1] * width + p[0]] = true;
            auto off = nav[lines[p[1]][p[0]]];
            if (visited[(p[1] + off[1]) * width + (p[0] + off[0])]) {
                p[0] += off[2];
                p[1] += off[3];
            } else {
                p[0] += off[0];
                p[1] += off[1];
            }
        }

        silver++;

        if (pointers[0][0] == pointers[1][0] && pointers[0][1] == pointers[1][1])
            break;
    }
    visited[pointers[0][1] * width + pointers[0][0]] = true;

    return silver;
}

vector<vector<char>> getExpanded(const vector<string>& lines, long width, long height, const vector<bool>& visited) {
    vector<vector<char>> expanded(height * 3, vector<char>(width * 3, '.'));

    for (size_t x = 0; x != width; ++x) {
        for (size_t y = 0; y != height; ++y) {
            if (!visited[y * width + x])
                continue;

            char   c   = lines[y][x];
            size_t e_x = x * 3;
            size_t e_y = y * 3;

            expanded[e_y + 1][e_x + 1] = '#';
            if (c == 'S' || c == '-' || c == 'J' || c == '7') // W
                expanded[e_y + 1][e_x] = '#';
            if (c == 'S' || c == '|' || c == 'J' || c == 'L') // N
                expanded[e_y][e_x + 1] = '#';
            if (c == 'S' || c == '-' || c == 'F' || c == 'L') // E
                expanded[e_y + 1][e_x + 2] = '#';
            if (c == 'S' || c == '|' || c == 'F' || c == '7') // S
                expanded[e_y + 2][e_x + 1] = '#';
        }
    }

    stack<vector<long>> s;
    s.push({0, 0});

    while (!s.empty()) {
        long x = s.top()[0];
        long y = s.top()[1];
        s.pop();
        expanded[y][x] = 'X';

        for (int i = -1; i <= 1; ++i) {
            long flag_x = x + i;
            for (int j = -1; j <= 1; ++j) {
                long flag_y = y + j;
                if ((flag_y < 0 || flag_y >= expanded.size()) ||
                        (flag_x < 0 || flag_x >= expanded[0].size()))
                    continue;

                if (expanded[flag_y][flag_x] == '.')
                    s.push({flag_x, flag_y});
            }
        }
    }

    return expanded;
}


long getGold(vector<string> &lines, long width, long height, vector<bool>& visited)
{
    long gold = 0;
    vector<vector<char>> expanded = getExpanded(lines, width, height, visited);

    for (size_t x = 1; x < width * 3; x += 3) {
        for (size_t y = 1; y < height * 3; y += 3) {
            if (expanded[y][x] == '.')
                gold++;
        }
    }

    return gold;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string line;
    vector<string> lines;
    while (getline(cin, line)) {
        lines.push_back(line);
    }

    long width = lines[0].size(), height = lines.size();
    vector<bool> visited(width * height, false);

    long silver = getSilver(lines, width, height, visited);
    long gold = getGold(lines, width, height, visited);

    cout << "Part 1: " << silver << endl;
    cout << "Part 2: " << gold << endl;

    return 0;
}

