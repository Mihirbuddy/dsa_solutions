#include <bits/stdc++.h>

using namespace std;

int solve(string s1,string s2, int i,int j,int n,int m){
  if(i==n || j==m)
    return 0;

  int ans=0;
  if(s1[i]==s2[j])
    ans=1+solve(s1,s2,i+1,j+1,n,m);

  else{
    ans=max(solve(s1,s2,i+1,j,n,m),solve(s1,s2,i,j+1,n,m));
  }

  return ans;
}

void solvemem(string s1,string s2){

  int n=s1.size();
  int m=s2.size();

  vector<vector<int>> dp(n+1,vector<int>(m+1,0));
  vector<vector<int>> count(n+1,vector<int>(m+1,0));

  for(int i=0;i<=n;i++){
    count[i][m]=1;
  }
  for(int i=0;i<=m;i++){
    count[n][i]=1;
  }

  for(int i=n-1;i>=0;i--){
    for(int j=m-1;j>=0;j--){
     
      if(s1[i]==s2[j]){
        dp[i][j]=1+dp[i+1][j+1];
        count[i][j]=count[i+1][j+1];
      }
      else{
        dp[i][j]=max(dp[i+1][j],dp[i][j+1]);

        if(dp[i+1][j]>dp[i][j+1])
          count[i][j]=count[i+1][j];

        else if(dp[i+1][j]<dp[i][j+1])
          count[i][j]=count[i][j+1];

        else{
          count[i][j]=count[i+1][j]+count[i][j+1];

          if(dp[i][j]==dp[i+1][j+1]){
            count[i][j]-=count[i+1][j+1];
          }
          
        }
      }

    }
  }
  

  cout<<"length of the longest substring is"<<dp[0][0]<<endl;
  cout<<"total possible lcs is"<<count[0][0]<<endl;
  int i=0;
  int j=0;
  string ans="";

  while(i<n && j<m){
    if(s1[i]==s2[j]){
      ans+=s1[i];
      i++;
      j++;
    }

    else if(dp[i+1][j]>dp[i][j+1])
      i++;
    else
      j++;
  }

  cout<<"the lcs is"<<ans<<endl;

  
}

void shortest_common_supersequence(string s1,string s2){
  int n=s1.size();
  int m=s2.size();

  vector<vector<int>> dp(n+1,vector<int>(m+1,0));
  


  for(int i=n-1;i>=0;i--){
    for(int j=m-1;j>=0;j--){
     
      if(s1[i]==s2[j]){
        dp[i][j]=1+dp[i+1][j+1];
      }
      else{
        dp[i][j]=max(dp[i+1][j],dp[i][j+1]);
          
        }
      }

    }

  cout<<"length of the longest substring is"<<dp[0][0]<<endl;
  
  int i=0;
  int j=0;
  string ans="";

  while(i<n && j<m){
    if(s1[i]==s2[j]){
      ans+=s1[i];
      i++;
      j++;
    }

    else if(dp[i+1][j]>dp[i][j+1]){
      ans+=s1[i];
      i++;
    }
    else{
      ans+=s2[j];
      j++;
    }
  }

  while(i<n){
    ans+=s1[i];
    i++;
  }

  while(j<m){
    ans+=s2[j];
    j++;
  }


  cout<<"the supersequence is"<<ans<<endl;

  
}

int main()
{
  int t;
  cin>> t;

  while(t--){
    string s1,s2;
    cin>>s1>>s2;

    int n=s1.length();
    int m=s2.length();

    // int result=solve(s1,s2,0,0,n,m);
    shortest_common_supersequence(s1,s2);
    
  }

  return 0;
}