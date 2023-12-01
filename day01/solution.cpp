#include <bits/stdc++.h>

using namespace std;

vector<string> numbers = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int convertToDigit(const string& digitStr) {
    map<string, int> digitMap = {
        {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
        {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8},
        {"nine", 9}
    };

    auto it = digitMap.find(digitStr);
    return (it != digitMap.end()) ? it->second : 0;
}

pair<int, int> firstNumber(const string& input) {
    int res = 0;
    int min = input.size();
    for (const string& number : numbers) {
        size_t found = input.find(number);
        if (found != string::npos)
            if (found < min) {
                min = found;
                res = convertToDigit(number);
            }
    }

    return { res, min };
}

pair <int, int> firstDigit(const string& input) {
    for (size_t i = 0; i < input.size(); i++) {
        if (isdigit(input[i])) {
            return { input[i] - '0', i };
        }
    }
    return { 0, 0 };
}

pair<int, int> lastNumber(const string& input) {
    size_t lastFound = 0;
    int res = 0;

    for (const string& number : numbers) {
        size_t found = input.rfind(number);
        if (found != string::npos) {
            if (lastFound < found) {
                lastFound = found;
                res = convertToDigit(number);
            }
        }
    }

    return { res, lastFound };
}

pair <int, int> lastDigit(const string& input) {
    char last = 0;
    for (auto it = input.rbegin(); it != input.rend(); ++it) {
        if (isdigit(*it))
            return { (*it - '0'), distance(it, input.rend()) - 1 };
    }
    return { 0, 0 };
}

int findFirst(const string& line) {
    auto pair1 = firstNumber(line);
    auto pair2 = firstDigit(line);

    if (pair1.first == 0)
        return pair2.first;

    return pair1.second > pair2.second ? pair2.first : pair1.first;
}

int findLast(const string& line) {
    auto pair1 = lastNumber(line);
    auto pair2 = lastDigit(line);

    if (pair1.first == 0)
        return pair2.first;

    return pair1.second < pair2.second ? pair2.first : pair1.first;
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string line;
    int sum1 = 0;
    int sum2 = 0;

    while (getline(cin, line)) {
        sum1 += firstDigit(line).first * 10 + lastDigit(line).first;
        sum2 += findFirst(line) * 10 + findLast(line);
    }
    
    cout << "Part 1 answer: " << sum1 << endl;
    cout << "Part 2 answer: " << sum2 << endl;

    return 0;
}
