#include <bits/stdc++.h>

using namespace std;

vector<int> parseLine(const string& line) {
    vector<int> values;
    istringstream iss(line);

    string word;
    iss >> word;

    int value;
    while (iss >> value) {
        values.push_back(value);
    }

    return values;
}

int solve1(vector<int>& times, vector<int>& distances) {
    int result = 1;

    for (size_t index = 0; index < times.size() && index < distances.size(); ++index) {
        int time = times[index];
        int minDistance = distances[index];
        int possibilities = 0;

        for (int i = 0; i < time; ++i) {
            int distance = (time - i) * i;
            if (distance > minDistance) {
                possibilities += 1;
            }
        }

        result *= possibilities;
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<int> times;
    vector<int> distances;

    string line;

    getline(cin, line);
    times = parseLine(line);
    getline(cin, line);
    distances = parseLine(line);

    int res = solve1(times, distances);

    cout << "Part 1: " << res << endl;

    return 0;
}

