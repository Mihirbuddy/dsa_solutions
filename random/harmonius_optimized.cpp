#include <iostream>
#include <vector>
#include <algorithm>


// O(n)
using namespace std;

int main()
{
  int n;
  cin >> n;

  vector<int> dp(n);
  dp[0] = 1;

  int i2 = 0;
  int i3 = 0;
  int i5 = 0;

  for (int i = 1; i < n; i++)
  {

    int a = dp[i2] * 2;
    int b = dp[i3] * 3;
    int c = dp[i5] * 5;

    dp[i] = min({a, b, c});

    if (a == dp[i])
    {
      i2++;
    }

    if (b == dp[i])
    {
      i3++;
    }

    if (c == dp[i])
    {
      i5++;
    }
  }

  cout << dp[n - 1];
  return 0;
}

/*
Problem Statement
After the poor performance of students in the last DSAPS slip test, the head TA Abhijith 🐐 sat down and thought very hard about what had gone wrong. It was not the questions. It was not the students. It was, obviously, the timing.

So the TA consulted an astrologer just outside campus, who — for a modest fee — delivered his verdict: a slip test may only be held on a day that is harmonious. Counting days from the start of the semester, day d is harmonious if d can be built by multiplying together only 2s, 3s and 5s. If any other prime sneaks into its factorisation, the day is cursed and the test is off.

Day 12 is harmonious, since 12 = 2 × 2 × 3. Day 7 is cursed, because 7 is a prime nobody on the faculty trusts. Day 14 is also cursed, since 14 = 2 × 7 and that 7 ruins everything. Day 1 is declared harmonious by decree — the astrologer's fee covered it.

The TAs will hold their slip tests on harmonious days, in order: the first test on the first harmonious day, the second on the second, and so on. The batch would very much like to know how much time it has left.

Given n, find the day number on which the n-th slip test will be held.

Input Format
A single integer n, the index of the slip test you are dreading.

Output Format
A single integer: the day number of the n-th harmonious day.

Constraints
1 <= n <= 1690
Sample Input 1
Copy
10
Sample Output 1
Copy
12
Explanation
Walking through the first twelve days of the semester: days 1, 2, 3, 4, 5 and 6 are all harmonious. Day 7 is cursed by the prime 7. Days 8, 9 and 10 are harmonious again. Day 11 is cursed by the prime 11. Day 12 = 2 × 2 × 3 is harmonious.

That gives the harmonious days in order as 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 — so the 10th slip test lands on day 12, and the batch has just under a fortnight to prepare.

Sample Input 2
Copy
1
Sample Output 2
Copy
1
Explanation
Day 1 is harmonious by decree, so the very first slip test is held on the first day of the semester. The TAs consider this excellent motivation.
*/




/*
approach->

see earlier we tried to solve this prblem usign recursion , buthte problem with that code is that , we ought to generate 
all the day s , like we were incrementing day by 1 and checking it , so for a large value fo n we have to check many thousands of days , and even if we apprly dp to that solution we still need to find thousand of days once 

now the optimized approach is we know the first har.. day is 1 , the next harmonius days are multiple of either 2,3 or 5 
so multiply 1 by 2 ,3,5 this will generate the next 3 harmonius day then do the same for 2 and so on 

this is the main idea , to solve this there are twoo methods 
brute force -> do for 1 -> 2,3,5 then for 2->4,6,10  and os on 
and keep storing the new days coming , also we have to maintain a certain order 
for let suppose 2 generated 4,6,10 and 3 generated 6,9,15  
first we have to take 4 then 6 then 9 then 10 , so we have to maintain there ordering like which is the next smallest that we have to process 
second we have to keep the check for duplilcates , like 6 is coming two times , so we dont have to process it twice 
so we can take a priority queue for minimum and a set for putting the incoming days uniquely

this will take a lot of space


optimized 

take 3 pointers 
i2,i3,i5 -> 
i2 means , ham jis bhi day pe hai uska 2 se multiply karne pe konsa day aayega , same for 3(3 se multiple )and for 5 

now maintain a days or a dp array like which all days we have got so far 
we know the first day is 1 so dp[0]=1
now i2 ,i3,i5 would be pointing to the 0th element (i.e. the first day )
int a = dp[i2] * 2-> dp[0] * 2 ;
int b = dp[i3] * 3 ->dp[0] * 3;
int c = dp[i5] * 5 ->dp[0] * 5;

minimm is 2 so the next days is 2 store it in dp 
i2 gave this minimum 2, so increment i2 

now i2=1
i3=0
i5=0

see this menas , ki 1st day ka hamne 2 se mulitly vala day nikal lia so i2 aage badahe do , 
which means ham aage next day ka 2th multiple dekhenge
now 1st day ka hamne 3* multiple and 5* multiple day nahi liya so abhi unko mat badhao ,, as it is rehne do 

now 
so far
dp={1,2}

int a = dp[i2] * 2-> dp[1] * 4 ;
int b = dp[i3] * 3 ->dp[0] * 3;
int c = dp[i5] * 5 ->dp[0] * 5;

3 is the minimum so increment it 

now hamne 1st dya ka 3th multiple bhi dekh liya so increment it 
which means ham aage next day ka 3th multiple dekhenge


so see is manner me ham hamesha minimum element hi dekh rahe hai 

also see these 3 conditions are in if , not else if or else 
which means we have to process all these conditions independently

 if (a == dp[i])
    {
      i2++;
    }

    if (b == dp[i])
    {
      i3++;
    }

    if (c == dp[i])
    {
      i5++;
    }

this is becasue suppose 2 ke 3th multiple ne 6 diya and 3 ke 2th multiple ne bhi 6diya , now we have to process 6 only one time 
so dono ke pointer increment kardo , ki hamne dono ke 6 ko process kar liya to dono aage badho 


*/