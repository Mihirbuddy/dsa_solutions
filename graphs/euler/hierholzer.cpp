/*see this is leetcode question 
2097: valid arrangement of pairs 

now basically the poitn to discuss 

in euler tour of a graph , we have to visit each edge and we can visit them exactly once , 

now there is a confusion here that why do we remove the edges once we are done explorign them 

it is because 
wha i thoguh : why can't we use a simple dfs like a simple for loop , but here there is a problem of duplicacy we might visit again 

secondly i thogyhg of maingtaining a visited array , : now see ineuler tour we can visit a vertex more than once if needed , but edges only one time so visited array marks the exploration of a vertex 

yeah we can assign a id to each edge and keep a visited array on the id of a edge that would work 

what we are doing here is , whenever we are done exploring a edge ,we remove it from the adj, of that node , so that even if we visit that vertex again(maybe due to a cycle) we will not explore that edge again 
*/

class Solution {
public:

    void dfs(
        int node,
        unordered_map<int, vector<int>>& adj,
        stack<int>& s
    ) {
        while(adj[node].size()>0){
            int it=adj[node].back();
            adj[node].pop_back();

            dfs(it,adj,s);
        }

        s.push(node);
    }

    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        unordered_map<int, int> indegree;
        unordered_map<int, int> outdegree;

        unordered_map<int, vector<int>> adj;
        int node = -1;
        

        for (auto& it : pairs) {
            indegree[it[1]]++;
            outdegree[it[0]]++;

            adj[it[0]].push_back(it[1]);
            node = it[0];
        }

        for (auto& it : adj) {
            int node1=it.first;
            if(outdegree[node1]-indegree[node1]==1){
                node=node1;
                break;
            }
        }

        stack<int> s;

        dfs(node, adj, s);

       vector<vector<int>> ans;

        while(!s.empty()){
            int top=s.top();
            s.pop();

            if(!s.empty()){
                int top2=s.top();
                ans.push_back({top,top2});
            }
        }

        return ans;
    }
};
