#include<iostream>
#include<string>
#include<stack>
#include<algorithm>


using namespace std;

string remove_zeros(string &s){

  
  int i=0;
  while(i<(int)s.size()-1 && s[i]=='0')i++;

  /*
  see jo size hoti hai vo unsigned hoti hai so suppose if size is 0 and we do -1 on it , it will become a substantially a very large no. , so usko range me laane ke liye we typecasted it to -1 , 
  also why are we going onlyy till n-2 , because we want to return the last character anyhow , if it is 00001 then we return 1 and if it is 00000 then we want to return 0 instead of returning a empty string */
  return s.substr(i);
}


/*
see if b>a then we return -1 , 
if a>b then 1 
if both are same then 0 */

int compare(string &a, string &b){
  a=remove_zeros(a);
  b=remove_zeros(b);

  //this function is meant to return which no. is bigger 
  //if their size is different then the one with greater size would be bigger mathematically also 
  if(a.size() != b.size())return a.size()<b.size()?-1:1;
  if(a==b)return 0;

  return a<b?-1:1;  
}

string add(string &s1,string &s2){
  string result="";
  int carry=0;

  s1=remove_zeros(s1);
  s2=remove_zeros(s2);

  int i=(int)s1.size()-1;
  int j=(int)s2.size()-1;

  while(i>=0 || j>=0 || carry>0){
    int sum=carry;
    if(i>=0)sum+=s1[i--]-'0';
    if(j>=0)sum+=s2[j--]-'0';
    
    result.push_back((sum%10)+'0');
    carry=sum/10;
  }


  reverse(result.begin(),result.end());

  return remove_zeros(result);
}

string subtract(string &s1,string &s2){
  s1=remove_zeros(s1);
  s2=remove_zeros(s2);

  string result="";
  int i=(int)s1.size()-1,j=(int)s2.size()-1,borrow=0;

  while(i>=0 && j>=0 && borrow>0){
    int diff=s1[i--]-'0'-borrow;
    diff-=s2[j--]-'0';

    if(diff<0){
      diff+=10;
      borrow=1;
    }
    else borrow=0;
    result.push_back(diff);
  }

  reverse(result.begin(),result.end());

  return remove_zeros(result);
}


string multiply(string &s1,string& s2){
  
}
int main(){

  return 0;
}