#include<iostream>

using namespace std;

typedef long long ll;

ll gcd;

ll find_gcd(int a,int b){

  if(a==0)return b;

  return find_gcd(b%a,a);

}

ll find_lcm(int a,int b){

  ll prod=a*b;
  return prod/gcd;

}

int main(){


  int a,b;
  cin>>a>>b;

  gcd = find_gcd(a,b);
  ll lcm=find_lcm(a,b);
  cout<<gcd<<" "<<lcm;

  return 0;
}