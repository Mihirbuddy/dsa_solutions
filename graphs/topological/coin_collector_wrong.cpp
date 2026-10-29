/*
A game has n rooms and m tunnels between them. Each room has a certain number of coins. What is the maximum number of coins you can collect while moving through the tunnels when you can freely choose your starting and ending room?
Input
The first input line has two integers n and m: the number of rooms and tunnels. The rooms are numbered 1,2,\dots,n.
Then, there are n integers k_1,k_2,\ldots,k_n: the number of coins in each room.
Finally, there are m lines describing the tunnels. Each line has two integers a and b: there is a tunnel from room a to room b. Each tunnel is a one-way tunnel

*/


/*
see the questino workigns is not clear and that why there is a bug in this code , consider the graph 2->3, 3->1 ,3->4
coins be node[1]=5 ,node[2]=1 ,node[3]=1 ,node[4]=1

now see suppose we started from node 2 then we can take coins of node 2 and mark it visited and then we go to node 3 and take the coins , and mark i tvisited then node 1 and same 1, now from 1 we can't go anywhere , becasue node 2 is already visited , so this code we onnly see this path , 2->3->1 and take coins 2->3->1 => 1+1+5=7

yes it will also explore other paths as well like 3,1,2 or 2,3,4 ,3,4 ,1,2,3,4
see this is not a correct couter example as 1,2,3,4 will give the correct answer , 

but the point is what this code allows is we visit 2 then 3 then 1 then we can go back to 2 tthen 3 then 4 
see we can revisit any node , but can take it cooins only once , but due to this ,w e ere able to visit 1,2,3,4 


counter example :2 (correct)

4 5
1 1 1 1
1 2
2 1
1 3
3 1
1 4

see in this graph node 1 is the hub of the graph , like every node is conencted throug on only , 
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

int dfs(int node, unordered_map<int, vector<int>> &adj, vector<int> &visited, vector<int> &coins)
{

  visited[node] = 1;

  int maxans = 0;
  for (auto &it : adj[node])
  {

    if (!visited[it])
    {
      int ans = coins[it] + dfs(it, adj, visited, coins);
      maxans = max(maxans, ans);
    }
  }
  visited[node] = 0;

  return maxans;
}

int main()
{
  int n, m;
  cin >> n >> m;

  vector<int> coins(n + 1);
  for (int i = 1; i <= n; i++)
  {
    cin >> coins[i];
  }

  unordered_map<int, vector<int>> adj;
  for (int i = 0; i < m; i++)
  {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
  }

  vector<int> visited(n + 1, 0);
  int maxans = -1;

  for (int i = 1; i <= n; i++)
  {

    int result = coins[i] + dfs(i, adj, visited, coins);
    maxans = max(maxans, result);
  }

  cout << maxans;

  return 0;
}