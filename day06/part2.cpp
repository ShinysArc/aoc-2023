#include <bits/stdc++.h>

using namespace std;

long parseLine(const string& line) {
    string parsed = regex_replace(line, regex("[^0-9]"), "");

    long res;
    istringstream(parsed) >> res;

    return res;
}

long solve2(const long& time, const long& distance) {
    long a = -1;
    long b = time;
    long c = -distance;

    long delta = b * b - 4 * a * c;

    long x1 = (-b - sqrt(delta)) / (2 * a);
    long x2 = (-b + sqrt(delta)) / (2 * a);

    return x1 - x2;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    long time;
    long distance;

    string line;

    getline(cin, line);
    time = parseLine(line);
    getline(cin, line);
    distance = parseLine(line);

    long res = solve2(time, distance);

    cout << "Part 2: " << res << endl;

    return 0;
}

