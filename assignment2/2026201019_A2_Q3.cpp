#include <cstdio>

int n;
long long freq[90];
long long prefix[90];          // prefix[i] = freq[1] + ... + freq[i]

long long moveCost;            // cost per unit of distance
long long scanCost;            // cost of scanning one bin
long long turnCost;            // extra cost for changing direction


long long memo[90][90][2][2];
bool visited[90][90][2][2];

long long solve(int l, int r, int from, int dir) {
    if (l > r) return 0;

    if (visited[l][r][from][dir]) return memo[l][r][from][dir];

    // where the robot is standing right now
    int pos;
    if (from == 0) pos = l - 1;
    else pos = r + 1;

    long long total = prefix[r] - prefix[l - 1];

    long long best = -1;

    for (int root = l; root <= r; root++) {
        int distance;
        int newDir;
        if (root > pos) {
            distance = root - pos;
            newDir = 0;
        } else {
            distance = pos - root;
            newDir = 1;
        }

        long long stepCost = moveCost * distance + scanCost;
        if (newDir != dir) stepCost += turnCost;

        long long cost = total * stepCost;
        cost += solve(l, root - 1, 1, newDir);   // left part, robot is at root (right of it)
        cost += solve(root + 1, r, 0, newDir);   // right part, robot is at root (left of it)

        if (best == -1 || cost < best) best = cost;
    }

    visited[l][r][from][dir] = true;
    memo[l][r][from][dir] = best;
    return best;
}

int main() {
    int type;

    // keeps reading queries until the input ends (a single query works too)
    while (scanf("%d", &type) == 1) {
        scanf("%d", &n);

        // clear the memo from the previous query
        for (int a = 0; a < 90; a++)
            for (int b = 0; b < 90; b++)
                for (int c = 0; c < 2; c++)
                    for (int d = 0; d < 2; d++)
                        visited[a][b][c][d] = false;

        prefix[0] = 0;
        for (int i = 1; i <= n; i++) {
            scanf("%lld", &freq[i]);
            prefix[i] = prefix[i - 1] + freq[i];
        }

        long long returnCost = 0;

        if (type == 1) {
            // only count the number of bins checked
            moveCost = 0;
            scanCost = 1;
            turnCost = 0;
        } else if (type == 2) {
            // only count the distance driven
            moveCost = 1;
            scanCost = 0;
            turnCost = 0;
        } else {
            scanf("%lld %lld %lld", &moveCost, &scanCost, &turnCost);

            // driving back home from bin i costs moveCost * i, no turn penalty
            for (int i = 1; i <= n; i++) {
                returnCost += freq[i] * i;
            }
            returnCost *= moveCost;
        }

        // robot starts at bin 0 and its first move is to the right
        long long answer = solve(1, n, 0, 0) + returnCost;

        printf("%lld\n", answer);
    }
    return 0;
}
