#include <bits/stdc++.h>

using namespace std;

vector<long> parseSeeds(const string& line) {
    vector<long> seeds;

    istringstream ss(line);

    long num;
    string token;
    ss >> token;
    while (ss >> num)
        seeds.push_back(num);

    return seeds;
}

vector<long> processSection(vector<long> seeds) {
    vector<long> resultSeeds;
    vector<long> remainingSeeds = seeds;
    string line;

    while (getline(cin, line)) {
        if (line[0] == '\0')
            break;
        stringstream stream(line);
        long destination, source, length;
        stream >> destination >> source >> length;

        long end = source + length;

        remainingSeeds.clear();
        for (auto seed : seeds) {
            if (source <= seed && seed < end)
                resultSeeds.push_back(seed + destination - source);
            else
                remainingSeeds.push_back(seed);
        }

        seeds = remainingSeeds;
    }

    resultSeeds.insert(resultSeeds.end(), remainingSeeds.begin(), remainingSeeds.end());
    return resultSeeds;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string line;

    getline(cin, line);
    vector<long> seeds = parseSeeds(line);
    getline(cin, line);

    while (getline(cin, line)) {
        seeds = processSection(seeds);
    }

    for (auto s : seeds)
        cout << s << endl;

    cout << "Part 1: " << *(min_element(seeds.begin(), seeds.end())) << endl;

    return 0;
}
