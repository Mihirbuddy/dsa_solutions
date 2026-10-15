#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * This function moves backwards through the DP table
 * and prints every optimal selection.
 */
void printAllAnswers(
    int i,
    int w,
    const vector<int>& weight,
    const vector<int>& value,
    const vector<vector<int>>& dp,
    vector<int>& selectedItems,
    int& numberOfAnswers
) {
    // No more items are left to check.
    if (i == 0) {
        numberOfAnswers++;

        cout << "\nAnswer " << numberOfAnswers << ":\n";

        int totalWeight = 0;
        int totalValue = 0;

        // selectedItems contains items in reverse order.
        for (int j = selectedItems.size() - 1; j >= 0; j--) {
            int index = selectedItems[j];

            cout << "Item " << index + 1
                 << ": weight = " << weight[index]
                 << ", value = " << value[index]
                 << '\n';

            totalWeight += weight[index];
            totalValue += value[index];
        }

        cout << "Total weight = " << totalWeight << '\n';
        cout << "Total value = " << totalValue << '\n';

        return;
    }

    /*
     * POSSIBILITY 1: Do not take item i.
     *
     * If the answer remains the same without item i,
     * then skipping item i is a valid optimal choice.
     */
    if (dp[i][w] == dp[i - 1][w]) {
        printAllAnswers(
            i - 1,
            w,
            weight,
            value,
            dp,
            selectedItems,
            numberOfAnswers
        );
    }

    /*
     * POSSIBILITY 2: Take item i.
     *
     * Item i is stored at index i - 1.
     */
    int index = i - 1;

    if (weight[index] <= w &&
        dp[i][w] == value[index] +
                     dp[i - 1][w - weight[index]]) {

        // Select the current item.
        selectedItems.push_back(index);

        // Continue with the remaining items
        // and reduced capacity.
        printAllAnswers(
            i - 1,
            w - weight[index],
            weight,
            value,
            dp,
            selectedItems,
            numberOfAnswers
        );

        /*
         * Remove the current item before checking
         * another possible answer.
         */
        selectedItems.pop_back();
    }
}

int main() {
    int n, capacity;

    cout << "Enter number of items: ";
    cin >> n;

    vector<int> weight(n);
    vector<int> value(n);

    cout << "Enter weights:\n";
    for (int i = 0; i < n; i++) {
        cin >> weight[i];
    }

    cout << "Enter values:\n";
    for (int i = 0; i < n; i++) {
        cin >> value[i];
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    // dp[i][w] = maximum value obtained using the first i items
    // with maximum capacity w.
    vector<vector<int>> dp(
        n + 1,
        vector<int>(capacity + 1, 0)
    );

    // Build the DP table.
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {

            // Do not take the current item.
            dp[i][w] = dp[i - 1][w];

            // Take the current item if it fits.
            if (weight[i - 1] <= w) {
                dp[i][w] = max(
                    dp[i][w],
                    value[i - 1] +
                        dp[i - 1][w - weight[i - 1]]
                );
            }
        }
    }

    cout << "\nMaximum value = "
         << dp[n][capacity] << '\n';

    vector<int> selectedItems;

    // This variable counts the number of optimal answers.
    int numberOfAnswers = 0;

    printAllAnswers(
        n,
        capacity,
        weight,
        value,
        dp,
        selectedItems,
        numberOfAnswers
    );

    cout << "\nNumber of optimal answers = "
         << numberOfAnswers << '\n';

    return 0;
}