#include<iostream>
#include<vector>
#include<queue>


using namespace std;

pair<int,vector<int>> bfs(int node, vector<vector<int>>& adj){

  int n=adj.size();
  vector<int> dist(n,-1);

  queue<int>q;
  q.push(node);

  dist[node]=0;
  int farthest=node;

  while(!q.empty()){
    int top=q.front();
    q.pop();

    for(auto it:adj[top]){
      if(dist[it]!=-1)continue;

      dist[it]=dist[top]+1;

      q.push(it);
      if(dist[it]>dist[farthest]){
        farthest=it;
      }
    }
  }

  return {farthest,dist};


}
int main(){

  int n;
  cin>>n;

  //vector<int>arr(n+1);

  vector<vector<int>> adj(n+1);
  for(int i=1;i<=n;i++){
      int a,b;
      cin>>a>>b;

      adj[a].push_back(b);
      adj[b].push_back(a);
  }

  //find the first fartheset node
  auto first=bfs(1,adj);
  int first_node=first.first;

  //find the second farthest node from this farthest node
  auto second=bfs(first_node,adj);
  int second_node=second.first;

  //see we calculated the second farthest node from the first farthest node and in this process , we have to visit all node from first_node and we calculate the distance of all nodes from this first_node

  vector<int> dist_a(n+1)=second.second;

  //now similarly find the distance of all the node from the second_node

  auto third=bfs(second_node,adj);

  vector<int> dist_b(n+1)=third.second;

  //now har node ka jo max distance hoga kisi bhi node se, vo max distance kis diameter node se hi aayega
  //diameter_node: when we find the longest diameter of a tree , the edges of the end is the diameter edge

  //for each node , find whether its maxdistance is coming from first_node or second_node

  vector<int> ans(n+1);
  for(int i=1;i<=n;i++){
    ans[i]=max(dist_a[i],dist_b[i]);
    cout<<ans[i]<<" ";
  }

  



  
  return 0;

}

/*
You are given a tree consisting of n nodes.
Your task is to determine for each node the maximum distance to another node.
Input
The first input line contains an integer n: the number of nodes. The nodes are numbered 1,2,\ldots,n.
Then there are n-1 lines describing the edges. Each line contains two integers a and b: there is an edge between nodes a and b.
Output
Print n integers: for each node 1,2,....,n, the maximum distance to another node.
Constraints

1 <= n <= 2.10^5
1<=a,b<=n

Example
Input:
5
1 2
1 3
3 4
3 5

Output:
2 3 2 3 3
*/
