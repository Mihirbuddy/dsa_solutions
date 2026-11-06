#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>


using namespace std;

typedef long long ll;
typedef pair<int,int> p;



class Solution {
public:

    const int INF = 1e9;

    int solve(int i, int j, int p,
              vector<int>& stones, int k) {

        // Base case: already one pile
        if (i == j) {
            if (p == 1) return 0;
            return INF;
        }

        // Case 1: We want exactly one pile
        if (p == 1) {

            int cost = solve(i, j, k, stones, k);

            if (cost == INF) return INF;

            int sum = 0;

            for (int x = i; x <= j; x++) {
                sum += stones[x];
            }

            return cost + sum;
        }

        // Case 2: We want p piles
        int ans = INF;

        for (int m = i; m < j; m++) {

            int left = solve(i, m, 1, stones, k);

            int right = solve(m + 1, j, p - 1, stones, k);

            if (left == INF || right == INF)
                continue;

            ans = min(ans, left + right);
        }

        return ans;
    }

    int mergeStones(vector<int>& stones, int k) {

        int n = stones.size();

        if ((n - 1) % (k - 1) != 0)
            return -1;

        return solve(0, n - 1, 1, stones, k);
    }
};


int main() {
    
    return 0;
}