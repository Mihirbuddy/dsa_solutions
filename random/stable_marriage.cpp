#include<bits/stdc++.h>
using namespace std;

bool isValidPreferenceList(const vector<int>& list, int n) {
    if (list.size() != n) return false;
    unordered_set<int> seen;
    for (int x : list) {
        if (x < 0 || x >= n || seen.count(x)) {
            return false; // Contains out-of-bounds index or duplicate entry
        }
        seen.insert(x);
    }
    return true;
}

bool preference(int new_partner,int curr_partner,vector<vector<int>> &pref,int person,int n){

  if(new_partner==curr_partner){
    return false;
    //see solve function won't require this as the man is already paired up with his desired woman then he would be in the queue
    //this condition is only for check function
  }

  for(int i=0;i<n;i++){
    if(pref[person][i]==curr_partner){
      //pehle husband aagaya list me so false;
      return false;
    }
    if(pref[person][i]==new_partner){return true;}
  }
  return false;
}
bool check(vector<vector<int>>& men_pref,vector<vector<int>> &women_pref,vector<int>&husband_of_woman,vector<int>& wife_of_men,int n){

  //check for all the 3 conditions 

  //fisrt check if all the man and woman are paired up or not 

  for(int i=0;i<n;i++){
    if(husband_of_woman[i]==-1 || wife_of_men[i]==-1){
      return false;
    }
  }

  for(int m=0;m<n;m++){
    for(int w=0;w<n;w++){
      //current wife of m is 
      int curr_wife=wife_of_men[m];
      //curr husband of w is 
      int curr_husband=husband_of_woman[w];

      //now for this m(man) check every woman against his curr_wife
      bool left=preference(w,curr_wife,men_pref,m,n);

      //now for this w(woman) check every man against his curr_husband
      bool right=preference(m,curr_husband,women_pref,w,n);

      //see in the notes we wrote this logic that left can be true that is might be possible then man has some other preference over woman or right can be true that woman has some other preferece ,but both won't be true together , otherwise the marriage will not hold 

      if(left && right)return false;
    }
  }
  
  return true;
}

bool solve(vector<vector<int>>& men_pref,vector<vector<int>> &women_pref,vector<int>&husband_of_woman,vector<int>& wife_of_men,int n){

  vector<int>next_woman(n,0);
  queue<int>q;

  //initially all men are single
  for(int i=0;i<n;i++){
    q.push(i);
  }

  while(!q.empty()){
    int man=q.front();

    if(next_woman[man]>=n){
      q.pop();
      continue;
    }

    int woman=men_pref[man][next_woman[man]];
    next_woman[man]++;
    int old_partner=husband_of_woman[woman];

    if(old_partner==-1){
      //this woman has not been paired yet
      husband_of_woman[woman]=man;
      wife_of_men[man]=woman;
      q.pop();
    }
    else{
      if(preference(man,old_partner,women_pref,woman,n)){
        //current man has more preference over the husband
        q.pop();  
        wife_of_men[old_partner]=-1;
        q.push(old_partner);
        husband_of_woman[woman]=man;
        wife_of_men[man]=woman;
        //the woman has dumped her current husband so  
      }
      //else do nothing this man can't be paired with this woman let him remain in the queue
    }
  }
  bool result=check(men_pref,women_pref,husband_of_woman,wife_of_men,n);
  return result;
}

int main(){
  int n;
  cout<<"how many men/women are there: ";
  cin>>n;

  vector<vector<int>> men_pref(n,vector<int>(n));
  vector<vector<int>> women_pref(n,vector<int>(n));

  for(int i=0;i<n;i++){
    cout<<"enter the preference of men: "<<i+1<<endl;
    for(int j=0;j<n;j++){
      int ele;
      cin>>ele;
      men_pref[i][j]=ele-1;
    }
    if(!isValidPreferenceList(men_pref[i],n)){
        cout<<"enter valid preference"<<endl;
        return -1;
    }
  }

  for(int i=0;i<n;i++){
    cout<<"enter the preference of women: "<<i+1<<endl;
    for(int j=0;j<n;j++){
      int ele;
      cin>>ele;
      women_pref[i][j]=ele-1;
    }
    if(!isValidPreferenceList(women_pref[i],n)){
        cout<<"enter valid preference"<<endl;
        return -1;
    }
  }

  vector<int> husband_of_woman(n,-1);
  vector<int> wife_of_men(n,-1);

  bool possible=solve(men_pref,women_pref,husband_of_woman,wife_of_men,n);

  if(possible){
    for(int i=0;i<n;i++){
      int man=i;
      int woman=wife_of_men[man];
      cout<<"man "<<man+1<<" married to "<<woman+1<<endl;
    }
  }
  else{
    cout<<"stable marriages not possible"<<endl;
  }
  return 0;
}
