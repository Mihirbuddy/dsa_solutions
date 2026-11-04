#include<iostream> 
#include<vector> 

using namespace std;


long long sumXOR(vector<int> &arr) {
        // code here
        long long sum=0;
        
        int n=arr.size();
        
        for(int i=0;i<32;i++){
            int set=0;
            int unset=0;
            for(int j=0;j<n;j++){
                if(arr[j]&(1<<i)){
                    set++;
                }
                else{
                    unset++;
                }
            }
            long long pairs=1LL*set*unset;
            sum+=(1LL*pairs*(1<<i));
        }
        
        return sum;

    }
int main(){


  int n;
  cin>>n;

  vector<int> arr;
  for(int i=0;i<n;i++){
    int x;
    cin>>x;
    arr.push_back(x);
  }


  long long result=sumXOR(arr);

  cout<<result<<endl;
  return 0;
}