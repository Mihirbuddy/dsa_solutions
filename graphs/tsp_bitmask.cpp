#include<iostream>
#include<vector>

using namespace std;

typedef long long ll;
int main(){

  int n;
  cin>>n;

  int m=n+1;
  //m is the total no. of cities including the city 0 and then 1 to n

  //building the cost matrix

  const ll INF=(ll)(1e18);
  vector<vector<ll>>cost(m,vector<ll>(m,INF));
  
  for(int i=0;i<m;i++){
    for(int j=0;j<m;j++){
      if(i==j)continue;
      else{
        ll x;
        cin>>x;
        cost[i][j]=x;
      }
    }
  }

  int full=(1<<n)-1;

  vector<vector<ll>>dp(1<<n,vector<ll>(m,INF));//take care one is 2^n and one is m , see we are not including city 0 in the mask but when at last we will go back to city 0
  
  //base case , difrectly go from bangalore to each city u 
  for(int i=1;i<=n;i++){
    int mask=(1<<(i-1));
    dp[mask][i]=cost[0][i];

  }

  /*now we will explore each path poossible ,a nd whatever is the lastt city of tthat path we will try to reach to a different city which is not explored in that path */

  
  for(int mask=0;mask<=full;mask++){
    //see we can also start with mask 1 , it will not matter ,because for mask 0 there will be no u from 1 to n that will be satisfying this i.e. no u will be in this path 

    for(int u=1;u<=n;u++){
      if(!mask &(1<<(u-1)))continue;
      
      ll cur=dp[mask][u];
      if(cur==INF)continue;

      for(int v=1;v<=n;v++){
        if(mask&(1<<(v-1)))continue;//v already visited

        int newmask=mask | (1<<(v-1));
        ll newcost=cur+cost[u][v];

        if(newcost<dp[newmask][v]){
          dp[newmask][v]=newcost;
        }
      }
    }
  }

  //now we have visited all cities from 1 to n 
  //now from the last node of each path we will try to reach back to city 0 bangalore 
  ll ans=INF;

  for(int u=1;u<=n;u++){
    ll tourcost=dp[full][u]+cost[u][0];
    if(tourcost<ans)ans=tourcost;
  }

  cout<<ans<<endl;

  
  return 0;
}

/*see there are n cities(excluding city 0 : bangalore) so to represent these cities we need logn bits , like if there are 8 cities then we need 3 bits
  
  now see city index is from 1 to n 
  but see we are solving this question using bits to represent 8 we need 3 bits i.e. from 0 to 7  
  */

  

  /*
WHY ARE WE USING dp[mask][u]?

1. WHY MASK INSTEAD OF A VISITED ARRAY?

- In TSP, we explore many different routes. Different routes can visit
  the same set of cities in different orders.

- A visited[] array can track visited cities for one route, but our DP
  needs to store costs for many different subsets of visited cities.

- We could use a separate visited array for every subset, but ordinary
  C++ arrays cannot directly be used as DP indices.

- Instead, we use a bitmask. Each bit represents a city:
      1 -> city is visited
      0 -> city is not visited

  For example, mask = 101 means cities 1 and 3 are visited.

- A mask is simply an integer, so we can use it directly as an index:
      dp[mask][u]

2. WHY DO WE NEED THE SECOND DIMENSION u?

- The mask only tells us WHICH cities have been visited. It does not
  tell us the order in which they were visited or where we currently are.

- For example, these routes visit the same cities:
      0 -> 1 -> 2 -> 3
      0 -> 1 -> 3 -> 2

  Both have the same mask {1, 2, 3}, but the first ends at city 3
  and the second ends at city 2.

- The next travel cost depends on the last city. Going from city 3
  to city 4 can have a different cost than going from city 2 to city 4.

- Therefore, we also store u, the last city visited.

3. MEANING OF THE DP STATE:

  dp[mask][u] = minimum cost to start at city 0, visit exactly the
                cities represented by mask, and end at city u.

In short:
  mask -> Which cities have been visited?
  u    -> Where are we currently?

We need both to correctly calculate the cost of visiting the next city.
*/