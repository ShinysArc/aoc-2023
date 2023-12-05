#include <bits/stdc++.h>

using namespace std;

vector<tuple<long, long>> parseSeeds(const string& line) {
    vector<tuple<long, long>> seeds;

    istringstream ss(line);

    vector<long> numbers;
    long num;
    string token;
    ss >> token;
    while (ss >> num)
        numbers.push_back(num);

    for (long i = 0; i < numbers.size(); i += 2) {
        long start = numbers[i];
        long length = numbers[i + 1];
        seeds.push_back(make_tuple(start, start + length));
    }

    return seeds;
}

vector<tuple<long, long>> processSection(vector<tuple<long, long>>& seeds) {
    vector<tuple<long, long>> resultSeeds;
    vector<tuple<long, long>> remainingSeeds = seeds;
    string line;

    while (getline(cin, line)) {
        if (line[0] == '\0')
            break;
        stringstream stream(line);
        long destination, source, length;
        stream >> destination >> source >> length;

        long delta = destination - source;
        long end = source + length;

        remainingSeeds.clear();
        for (const auto& seed : seeds) {
            long start, stop;
            tie(start, stop) = seed;

            if (source <= start && start < stop && stop <= end)
                resultSeeds.push_back(make_tuple(start + delta, stop + delta));
            else if (start < source && source < stop && stop <= end) {
                remainingSeeds.push_back(make_tuple(start, source));
                resultSeeds.push_back(make_tuple(source + delta, stop + delta));
            } else if (source <= start && start < end && end < stop) {
                resultSeeds.push_back(make_tuple(start + delta, end + delta));
                remainingSeeds.push_back(make_tuple(end, stop));
            } else if (start < source && source <= end && end < stop) {
                remainingSeeds.push_back(make_tuple(start, source));
                resultSeeds.push_back(make_tuple(source + delta, end + delta));
                remainingSeeds.push_back(make_tuple(end, stop));
            } else
                remainingSeeds.push_back(make_tuple(start, stop));
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
    vector<tuple<long, long>> seeds = parseSeeds(line);
    getline(cin, line);

    while (getline(cin, line)) {
        seeds = processSection(seeds);
    }

    auto minSeed = min_element(seeds.begin(), seeds.end(),
        [](const auto& a, const auto& b) {
            return get<0>(a) < get<0>(b);
        });

    int minValue = get<0>(*minSeed);
    cout << "Part 2: " << minValue << endl;

    return 0;
}
