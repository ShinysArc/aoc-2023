#include <bits/stdc++.h>

using namespace std;

int solve1(string directions, unordered_map<string, string> left_of, unordered_map<string, string> right_of) {
    int res = 0;
    string node = "AAA";

    while (true) {
        for (auto& direction : directions) {
            if (node == "ZZZ")
                return res;

            res++;
            if (direction == 'L')
                node = left_of[node];
            else
                node = right_of[node];
        }
    }

    return res;
}

uint64_t solve2(vector<string> startingPoints, string directions, unordered_map<string, string> left_of, unordered_map<string, string> right_of) {
    uint64_t res = 1;
    for (auto& node : startingPoints) {
        uint64_t steps = 0;

        bool flag = true;
        while (flag) {
            for (auto& direction : directions) {
                if (node[node.size() - 1] == 'Z') {
                    flag = false;
                    break;
                }

                steps++;
                if (direction == 'L')
                    node = left_of[node];
                else
                    node = right_of[node];
            }
        }
        res = lcm(res, steps);
    }

    return res;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string directions;
    string line;
    getline(cin, directions);
    getline(cin, line);
    unordered_map<string, string> left_of;
    unordered_map<string, string> right_of;
    vector<string> startingPoints;

    while (getline(cin, line)) {
        stringstream ss(line);

        string source, left, right;
        ss >> source;

        if (source[source.size() - 1] == 'A')
            startingPoints.push_back(source);

        ss.ignore(4);
        getline(ss, left, ',');
        ss.ignore(1);
        getline(ss, right, ')');

        left_of[source] = left;
        right_of[source] = right;
    }

    //int res1 = solve1(directions, left_of, right_of);
    //cout << "Part 1: " << res1 << endl;

    uint64_t res2 = solve2(startingPoints, directions, left_of, right_of);
    cout << "Part 2: " << res2 << endl;

    return 0;
}
