#include <bits/stdc++.h>

using namespace std;

class Card {
    public:
        int id;
        vector<int> winnings;
        vector<int> have;
        size_t copies = 1;
};

vector<Card> cards;

Card parseCard(string line) {
    Card card;
    stringstream ss(line);
    string token;
    ss >> token >> token;
    card.id = stoi(token);

    while (ss >> token && token != "|")
        card.winnings.push_back(stoi(token));

    ss.ignore();

    while (ss >> token)
        card.have.push_back(stoi(token));

    card.copies = 1;

    return card;
}

void showCards(const vector<Card>& cards) {
    for (const auto& card : cards) {
        cout << "Card " << card.id << ":" << endl;
        cout << "Winnings: " << endl;
        for (const auto& win : card.winnings) {
            cout << win << endl;
        }

        cout << "Haves: " << endl;
        for (const auto& h : card.have) {
            cout << h << endl;
        }
    }
}

int countPoints(const Card& card) {
    int points = 0;
    for (const auto& win : card.winnings) {
        for (const auto& h : card.have) {
            if (win == h) {
                if (points == 0) {
                    points = 1;
                    break;
                }
                points *= 2;
            }
        }
    }

    return points;
}

int countCards() {
    for (const auto& card : cards) {
        int count = 0;
        for (const auto& h : card.have) {
            if (find(begin(card.winnings), end(card.winnings), h) !=  end(card.winnings))
                count++;
        }
        for (int i = card.id; i < min(cards.size() , size_t(card.id + count)); i++)
            cards[i].copies += card.copies;
    }

    return accumulate(begin(cards), end(cards), 0, [](size_t total, const Card& card) {return total + card.copies;});
}


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    string line;

    while (getline(cin, line)) {
        cards.push_back(parseCard(line));
    }

    int sum1 = 0;
    for (const auto& card : cards) {
        sum1 += countPoints(card);
    }

    cout << "Part 1: " << sum1 << endl;
    cout << "Part 2: " << countCards() << endl;

    return 0;
}
