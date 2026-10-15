#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

void printAllLCS(
    int i,
    int j,
    const string& s1,
    const string& s2,
    const vector<vector<int>>& dp,
    string& current,
    int& numberOfAnswers,
    set<string>& seen   // used to avoid duplicate strings
) {
    int n = s1.size();
    int m = s2.size();

    // Reached the end of one of the strings -> current is a complete LCS.
    if (i == n || j == m) {
        if (seen.find(current) == seen.end()) {
            seen.insert(current);
            numberOfAnswers++;
            cout << "\nAnswer " << numberOfAnswers << ": " << current << '\n';
        }
        return;
    }

    // Characters match: this position is forced to be part of the LCS.
    if (s1[i] == s2[j]) {
        current.push_back(s1[i]);
        printAllLCS(i + 1, j + 1, s1, s2, dp, current, numberOfAnswers, seen);
        current.pop_back();
        return;
    }

    // Characters differ: branch wherever the DP value is preserved.

    // POSSIBILITY 1: move down (skip s1[i])
    if (dp[i + 1][j] == dp[i][j]) {
        printAllLCS(i + 1, j, s1, s2, dp, current, numberOfAnswers, seen);
    }

    // POSSIBILITY 2: move right (skip s2[j])
    if (dp[i][j + 1] == dp[i][j]) {
        printAllLCS(i, j + 1, s1, s2, dp, current, numberOfAnswers, seen);
    }
}

int main() {
    string s1, s2;
    cout << "Enter first string: ";
    cin >> s1;
    cout << "Enter second string: ";
    cin >> s2;

    int n = s1.size();
    int m = s2.size();

    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            if (s1[i] == s2[j]) {
                dp[i][j] = 1 + dp[i + 1][j + 1];
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j + 1]);
            }
        }
    }

    cout << "\nLength of LCS = " << dp[0][0] << '\n';

    string current;
    int numberOfAnswers = 0;
    set<string> seen;

    printAllLCS(0, 0, s1, s2, dp, current, numberOfAnswers, seen);

    cout << "\nNumber of distinct LCS strings = " << numberOfAnswers << '\n';

    return 0;
}