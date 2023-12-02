#include <bits/stdc++.h>

using namespace std;

class Round {
public:
    int red;
    int green;
    int blue;

    Round(int _red, int _green, int _blue)
        : red(_red), green(_green), blue(_blue) {}
};

class Game {
public:
    int id;
    vector<Round> rounds;

    Game(int _id, vector<Round> _rounds)
        : id(_id), rounds(_rounds) {}
};

Game createGame(const string& line) {
    istringstream stream(line);
    string token;
    stream >> token >> token;
    int id = stoi(token);

    int red = 0, green = 0, blue = 0;
    vector<Round> rounds;

    while (stream >> token) {
        string color;
        stream >> color;

        if (color[0] == 'r')
            red = stoi(token);
        else if (color[0] == 'g')
            green = stoi(token);
        else if (color[0] == 'b')
            blue = stoi(token);

        if (color[color.size() - 1] != ',') {
            rounds.push_back( Round(red, green, blue));
            red = 0, green = 0, blue = 0;
        }
    }

    return Game(id, rounds);
}

void showGame(Game game) {
    cout << "Game id: " << game.id << endl;
    for (auto i = 0; i < game.rounds.size(); i++) {
        auto round = game.rounds[i];
        cout << "Round " << i + 1 << endl;
        cout << "Reds: " << round.red << endl;
        cout << "Greens: " << round.green << endl;
        cout << "Blues: " << round.blue << endl;
    }
    cout << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string line;
    vector<Game> games;

    while (getline(cin, line)) {
        games.push_back(createGame(line));
    }

    int res1 = 0;
    int res2 = 0;

    for (auto& game : games) {
        bool flag = true;
        showGame(game);
        for (auto& round : game.rounds) {
            if (round.red > 12 || round.green > 13 || round.blue > 14) {
                flag = false;
                break;
            }
        }

        if (flag)
            res1 += game.id;
    }

    int minRed = 0, minGreen = 0, minBlue = 0;
    for (auto& game : games) {
        for (auto& round : game.rounds) {
            minRed = max(round.red, minRed);
            minGreen = max(round.green, minGreen);
            minBlue = max(round.blue, minBlue);
        }

        int power = minRed * minGreen * minBlue;
        cout << "Power of game " << game.id << ": " << power << endl;
        res2 += power;
        minRed = 0, minGreen = 0, minBlue = 0;
    }

    cout << "Part 1: " << res1 << endl;
    cout << "Part 2: " << res2 << endl;

    return 0;
}
