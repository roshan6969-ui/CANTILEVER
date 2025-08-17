#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Leaderboard {
public:
    vector<pair<string, int>> scores;

    void addScore(string playerName, int attempts) {
        scores.push_back(make_pair(playerName, attempts));
        sort(scores.begin(), scores.end(), [](pair<string, int>& a, pair<string, int>& b) {
            return a.second < b.second; // Sort by attempts (ascending)
        });
    }

    void display() {
        cout << "\nLeaderboard:\n";
        for (int i = 0; i < (int)scores.size(); i++) {
            cout << i + 1 << ". " << scores[i].first << " - " << scores[i].second << " attempts\n";
        }
    }
};

int main() {
    int lower = 1, upper = 100, guess, target, attempts = 0;
    int difficulty, range;
    char playAgain;
    string playerName;
    Leaderboard leaderboard;

    srand(time(0));

    do {
        // Player enters name
        cout << "Enter your name: ";
        cin >> playerName;

        // Select difficulty
        cout << "\nChoose difficulty level:\n";
        cout << "1. Easy (1 to 50)\n2. Medium (1 to 100)\n3. Hard (1 to 200)\n";
        cout << "Enter choice (1-3): ";
        cin >> difficulty;

        switch(difficulty) {
            case 1: range = 50; break;
            case 2: range = 100; break;
            case 3: range = 200; break;
            default: range = 100; cout << "Invalid choice. Defaulting to Medium.\n"; break;
        }

        upper = range;

        target = rand() % (upper - lower + 1) + lower;
        attempts = 0;

        cout << "\nGuess the number between " << lower << " and " << upper << ".\n";

        // Game loop
        do {
            cout << "Enter your guess: ";
            cin >> guess;
            attempts++;

            if (guess > target) {
                cout << "Too high! Try again.\n";
                if (target % 2 == 0) cout << "Hint: The number is even.\n";  // Use target here
                else cout << "Hint: The number is odd.\n";
            } else if (guess < target) {
                cout << "Too low! Try again.\n";
                if (target % 3 == 0) cout << "Hint: The number is divisible by 3.\n";
            } else {
                cout << "Congratulations! You guessed the correct number: " << target << endl;
                cout << "It took you " << attempts << " attempts.\n";
            }
        } while (guess != target);

        leaderboard.addScore(playerName, attempts);

        cout << "\nWould you like to play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    // Display leaderboard
    leaderboard.display();

    cout << "Thanks for playing!" << endl;

    return 0;
}

