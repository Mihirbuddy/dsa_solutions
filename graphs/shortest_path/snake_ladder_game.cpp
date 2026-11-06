/*
First line contains n and m, size of 2D matrix ladders and snakes respectively.
The next n lines contain the start and end positions of the ladders on the board, i.e., ladders[i][0], ladders[i][1].
The next m lines contain the start and end positions of the snakes on the board, i.e., snakes[i][0], snakes[i][1].

*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class compare
{
public:
  bool operator()(const pair<int, int> &a, const pair<int, int> &b) const
  {
    if (a.first == b.first)
      return a.second < b.second;
    else
      return a.first > b.first;
  }
};

int main()
{

  int n, m;
  cin >> n >> m;

  // vector<vector<int>> grid(n,vector<int>(m));

  unordered_map<int, int> ladder, snake;

  for (int i = 0; i < n; i++)
  {
    int u, v;

    cin >> u >> v;
    ladder[u] = v;
  }
  for (int i = 0; i < m; i++)
  {
    int u, v;

    cin >> u >> v;
    snake[u] = v;
  }

  priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq;

  pq.push({0, 1});
  vector<int> dist(103, 1e9);

  int ans = -1;
  while (!pq.empty())
  {
    auto top = pq.top();

    pq.pop();

    int block = top.second;
    int steps = top.first;

    // cout << block << " " << steps << endl;

    if (dist[block] < steps)
    {
      continue;
    }

    if (block == 100)
    {
      ans = steps;
      break;
    }

    for (int i = 1; i <= 6; i++)
    {
      int new_block = block + i;
      if (new_block > 100)
        break;
      if (ladder.count(new_block) > 0)
      {
        new_block = ladder[new_block];
      }
      else if (snake.count(new_block) > 0)
      {
        new_block = snake[new_block];
      }
      // see there is no need for snake , becasue vo down hi leke jaega , aur jis bhi block pe leke jaega vo ham pehle se hi uska shortest distance calculate kar chuke honge , like iss distance se to chota hi pehle explore kar chuke honge ,

      /*see above what i though is wrong , see snakes ki bhi zarurat hai , because consider ham block 3 pe hai udhar se ek ladder li vo 85 pe leke gayi , now suppose 85 leke +6 tak saanp hai , so now ham kisi saanp ki vajah se neeche 67 pe aagaye let suppose , now 67 pe ham pehli baar aaye hai aur ye minimum distance hai 67 pe pohochne ka so we will store it , kya pata 67 se 68 jaye aur 68 se 100 ka ek ladder mil jae.*/

      if (dist[new_block] > steps + 1)
      {
        dist[new_block] = steps + 1;
        pq.push({dist[new_block], new_block});
      }
    }
  }

  cout << ans << endl;

  return 0;
}