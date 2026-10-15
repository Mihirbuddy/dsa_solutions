#include<bits/stdc++.h>

using namespace std; 


int solve(int amount,vector<int> coins){

  vector<int> dp(amount+1,amount+1);
  dp[0]=0;

  for(int i=1;i<=amount;i++){
    for(int j=0;j<coins.size();j++){
      if(i-coins[j]>=0 && dp[i-coins[j]]<amount+1){
        dp[i]=min(dp[i],1+dp[i-coins[j]]);
      }
    }
  }

  return dp[amount]==amount+1?-1:dp[amount];
}

int solve_limited(int amount,vector<int> coins,int k){

  //for the highest denomination coin we have only k no. of that coin
  sort(coins.begin(),coins.end());

  vector<int> dp(amount+1,amount+1);
  dp[0]=0;

  for(int i=1;i<=amount;i++){
    for(int j=0;j<coins.size()-1;j++){
      if(i-coins[j]>=0 && dp[i-coins[j]]<amount+1){
        dp[i]=min(dp[i],1+dp[i-coins[j]]);
      }
    }
  }


  //see kya pata jo amount hame diya hai usko banane me highest denomination vale coin ka use hi na ho , aur vo lesser deno.. vale coin se hi ban jae , so when cnt=0 , ye vahi case hai 
  int ans=amount+1;

  for(int cnt=0;cnt<=k;cnt++){
    int remaining=amount-cnt*coins[coins.size()-1];

    if(remaining<0)break;

    if(dp[remaining]<amount+1)
      ans=min(ans,cnt+dp[remaining]);

  }




  return ans==amount+1?-1:ans;
}

int main(){

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);


  int t;
  cin>>t;

  while(t--){
    int amount;
    int n;
    int k;
    cin>>amount>>n>>k;
    cout<<endl;
    vector<int> coins(n);
    for(int i=0;i<n;i++){
      cin>>coins[i];
    }    

    int result=solve(amount,coins);
    int result1=solve_limited(amount,coins,k);
    cout<<"unilimited"<<result<<endl;
    cout<<"limited"<<result1<<endl;
  }
  return 0;
}