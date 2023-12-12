#include <bits/stdc++.h>

using namespace std;
using config = tuple<int, int, int>;

long countOptions(map<config, long> &map, string &line, vector<int> &sizes, config conf) {
    if (map.contains(conf))
        return map[conf];

    long res = 0;
    bool groupEnd = false;

    int lineSize = get<0>(conf);
    int curBroken = get<1>(conf);
    int sizeOff = get<2>(conf);
    if (curBroken) {
        if (curBroken == sizes[sizeOff]) {
            curBroken = 0;
            sizeOff++;
            groupEnd = true;
        } else if (curBroken > sizes[sizeOff])
            return 0;
    }

    if (lineSize == line.size()) {
        if (!curBroken && sizeOff == sizes.size())
            return 1;

        return 0;
    }

    if (line[lineSize] == '.') {
        if (!curBroken)
            res = countOptions(map, line, sizes, make_tuple(lineSize + 1, 0, sizeOff));
    } else if (line[lineSize] == '#') {
        if (!groupEnd && sizeOff < sizes.size())
            res = countOptions(map, line, sizes, make_tuple(lineSize + 1, curBroken + 1, sizeOff));
    } else if (line[lineSize] == '?') {
        if (!groupEnd && sizeOff < sizes.size())
            res += countOptions(map, line, sizes, make_tuple(lineSize + 1, curBroken + 1, sizeOff));

        if (curBroken == 0)
            res += countOptions(map, line, sizes, make_tuple(lineSize + 1, 0, sizeOff));
    }

    map[conf] = res;
    return res;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<pair<string, vector<int>>> m;
    string line;

    while (getline(cin, line)) {
        istringstream ss(line);
        string map;
        ss >> map;
        int num;
        vector<int> sizes;
        while (ss >> num) {
            sizes.push_back(num);
            char comma;
            ss >> comma;
        }

        m.push_back({map, sizes});
    }

    long sum1 = 0;
    for (auto& p : m) {
        map<config, long> map;
        sum1 += countOptions(map, p.first, p.second, make_tuple(0, 0, 0));
    }

    cout << "Part 1: " << sum1 << endl;

    long sum2 = 0;
    for (auto& p : m) {
        vector<int> newSizes;
        string unfolded;
        for (int i = 0; i < 5; i++) {
            newSizes.insert(newSizes.end(), p.second.begin(), p.second.end());
            unfolded.append(p.first);
            if (i < 4)
                unfolded.append("?");
        }

        map<config, long> map;
        sum2 += countOptions(map, unfolded, newSizes, make_tuple(0, 0, 0));
    }

    cout << "Part 2: " << sum2 << endl;

    return 0;
}
