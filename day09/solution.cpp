#include <bits/stdc++.h>

using namespace std;

vector<long> parseLine(const string& line) {
    stringstream ss(line);
    vector<long> res;
    long token;

    while (ss >> token)
        res.push_back(token);

    return res;
}

bool allZeroes(vector<long>& sequence) {
    for (auto& s : sequence) {
        if (s != 0)
            return false;
    }

    return true;
}

vector<vector<long>> getDiff(vector<long>& sequence) {
    vector<vector<long>> differences;
    vector<long> diff = sequence;
    vector<long> curr = sequence;

    while (!allZeroes(diff)) {
        diff.clear();
        for (auto i = 1; i < curr.size(); i++)
            diff.push_back(curr[i] - curr[i - 1]);
        differences.push_back(diff);
        curr = diff;
    }
    return differences;
}

long getNextValue(vector<long>& sequence) {
    vector<vector<long>> differences = getDiff(sequence);

    for (auto i = differences.size() - 1; i > 0; i--) {
        long last = differences[i - 1][differences[i - 1].size() - 1];
        long last2 = differences[i][differences[i].size() - 1];
        differences[i - 1].push_back(last + last2);
    }

    return sequence[sequence.size() - 1] + differences[0][differences[0].size() - 1];
}

long getPreviousValue(vector<long>& sequence) {
    vector<vector<long>> differences = getDiff(sequence);

    for (auto i = differences.size() - 1; i > 0; i--) {
        long first = differences[i - 1][0];
        long first2 = differences[i][0];
        differences[i - 1].insert(differences[i - 1].begin(), 1, first - first2);
    }

    return sequence[0] - differences[0][0];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string line;
    vector<vector<long>> sequences;

    while (getline(cin, line)) {
        sequences.push_back(parseLine(line));
    }
    
    long res1 = 0;
    long res2 = 0;

    for (auto& s : sequences)
        res1 += getNextValue(s);

    for (auto& s : sequences)
        res2 += getPreviousValue(s);

    cout << "Part 1: " << res1 << endl;
    cout << "Part 2: " << res2 << endl;

    return 0;
}
