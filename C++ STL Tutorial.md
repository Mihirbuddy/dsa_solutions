
## File I/O

When solving problems locally, typing input into the terminal every time you run your program is slow and annoying. File I/O lets you read input from a file and write output to a file instead.

### Approach 1: Shell redirection (no code changes needed)

If your program reads from `cin` and writes to `cout` normally, you can redirect input/output at the terminal itself — no changes to your code required.

```bash
./a.out < input.txt > output.txt
```

- `<` redirects `input.txt` as stdin
- `>` redirects stdout to `output.txt`

Compile and run together:

```bash
g++ solution.cpp -o a.out
./a.out < input.txt > output.txt
```

This is the fastest way — zero code changes. `cin`/`cout` silently read/write from the files instead of the terminal.

### Approach 2: `freopen` in code

Useful when you want file I/O hardcoded into your program (e.g. a local testing template).

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    for (int x : a) cout << x << " ";
    cout << endl;

    return 0;
}
```

Run normally, no redirection needed:

```bash
g++ solution.cpp -o a.out
./a.out
```

**Note:** `freopen` is common in local testing templates, but shell redirection (`<` `>`) is generally preferred for interviews/labs — you don't need to remember to remove it before submitting to an online judge (some judges reject programs with `freopen` calls, or the paths simply won't exist on the judge's machine and the program will silently fail).


## Vectors

`vector` is a dynamic array — it can grow and shrink at runtime, unlike a plain C++ array. Most operations run in **amortized O(1)** for end-insertion, O(1) for random access, and O(n) for insertion/deletion in the middle.

### Declaration and initialization

```cpp
vector<int> v;                  // empty vector
vector<int> v(5);               // size 5, all elements 0
vector<int> v(5, 10);           // size 5, all elements 10
vector<int> v = {1, 2, 3, 4};   // initializer list
vector<vector<int>> grid(3, vector<int>(4, 0)); // 3x4 2D vector, all 0
```

### Basic operations

```cpp
v.push_back(x);       // insert x at the end - O(1) amortized
v.pop_back();          // remove last element - O(1)
v.size();              // number of elements
v.empty();             // true if size == 0
v[i];                  // access element at index i - O(1), no bounds check
v.at(i);               // access element at index i - O(1), throws if out of bounds
v.front();             // first element
v.back();              // last element
v.clear();             // remove all elements
v.insert(v.begin() + i, x);        // insert x at index i - O(n)
v.erase(v.begin() + i);            // erase element at index i - O(n)
v.erase(v.begin(), v.begin() + k); // erase first k elements - O(n)
```

**Note:** Insert/erase anywhere except the end shifts subsequent elements (O(n)), and invalidates existing iterators — don't reuse an old iterator after modifying the vector.

### Iterating

```cpp
for (int i = 0; i < v.size(); i++) cout << v[i] << " ";

for (int x : v) cout << x << " ";              // range-based for loop

for (auto it = v.begin(); it != v.end(); it++) cout << *it << " ";
```

### Sorting

```cpp
sort(v.begin(), v.end());                    // ascending
sort(v.begin(), v.end(), greater<int>());    // descending
reverse(v.begin(), v.end());                 // reverse in place
```

### Lambda functions

A lambda is an inline, unnamed function — very useful for passing custom logic to STL algorithms like `sort`, `find_if`, etc.

```cpp
// [capture](parameters) -> return_type { body }
auto add = [](int a, int b) { return a + b; };
cout << add(2, 3);   // 5

int threshold = 10;
auto isAboveThreshold = [threshold](int x) { return x > threshold; }; // capture by value
auto isAboveThreshold2 = [&threshold](int x) { return x > threshold; }; // capture by reference
```

- `[]` — capture nothing
- `[x]` — capture `x` by value
- `[&x]` — capture `x` by reference
- `[&]` — capture everything used, by reference
- `[=]` — capture everything used, by value

### Custom sorting with lambdas

```cpp
vector<int> v = {5, 2, 8, 1};
sort(v.begin(), v.end(), [](int a, int b) {
    return a > b;   // descending order
});

// sorting pairs by second element
vector<pair<int,int>> p = {{1,5}, {2,2}, {3,8}};
sort(p.begin(), p.end(), [](pair<int,int> &a, pair<int,int> &b) {
    return a.second < b.second;
});

// sorting strings by length
vector<string> words = {"banana", "kiwi", "apple"};
sort(words.begin(), words.end(), [](string &a, string &b) {
    return a.size() < b.size();
});
```

**Note on comparators:** the comparator function must return `true` if the first argument should come _before_ the second. Getting this backwards (or non-strict, e.g. using `>=`) can cause undefined behavior in `sort`.

### Searching — `find`

```cpp
auto it = find(v.begin(), v.end(), x);
if (it != v.end()) {
    int index = it - v.begin();   // found
} else {
    // not found
}
```

`find` works on **unsorted** vectors — it's a linear scan, O(n). You can also pass a lambda-based condition using `find_if`:

```cpp
auto it = find_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; }); // first even number
```

### Counting — `count`

```cpp
int c = count(v.begin(), v.end(), x);   // number of times x appears - O(n)

// count_if with a lambda
int evenCount = count_if(v.begin(), v.end(), [](int x) { return x % 2 == 0; });
```

### Binary search on sorted vectors — `lower_bound` / `upper_bound`

Require the vector to be **sorted** first. Both run in O(log n).

```cpp
auto it = lower_bound(v.begin(), v.end(), x);  // first element >= x
auto it2 = upper_bound(v.begin(), v.end(), x); // first element > x

int idx = lower_bound(v.begin(), v.end(), x) - v.begin();  // convert to index

bool exists = binary_search(v.begin(), v.end(), x);  // check if x exists
```

**Common use:** counting occurrences of x in a sorted vector in O(log n):

```cpp
int cnt = upper_bound(v.begin(), v.end(), x) - lower_bound(v.begin(), v.end(), x);
```

### min, max, accumulate

```cpp
*max_element(v.begin(), v.end());   // largest element - O(n)
*min_element(v.begin(), v.end());   // smallest element - O(n)

accumulate(v.begin(), v.end(), 0);       // sum of elements (needs <numeric>)
accumulate(v.begin(), v.end(), 0, [](int a, int b) { return a + b*b; }); // sum of squares, using a lambda
```

**Tip:** `find`/`count` are O(n) linear scans — fine for small inputs or unsorted data. For repeated lookups on a large sorted vector, prefer `lower_bound`/`binary_search` for O(log n).

---

## Lambdas as recursive functions

A tempting pattern is to write a recursive function as a lambda, right where you need it:

```cpp
auto fib = [](int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);   // ERROR: fib not visible inside itself
};
```

This **won't compile**. Inside the lambda body, the name `fib` doesn't exist yet — the variable `fib` is only fully defined _after_ the initialization finishes. A lambda can't refer to itself by name the way a normal function can.

### Workaround 1: `std::function` + capture by reference

Declare the type first, then capture it by reference so the lambda can call itself through that reference:

```cpp
function<int(int)> fib = [&](int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
};
```

This works because `fib` (the `std::function` wrapper) already exists by the time the lambda body runs — capturing it by reference (`[&]`) lets the lambda look it up at call time instead of at definition time. Downside: `std::function` has some overhead compared to a plain function, so avoid this in tight recursive loops with large inputs.

### Workaround 2: just use a regular function

If the recursion is more than a one-off, a normal named function is simpler and faster:

```cpp
int fib(int n) {
    if (n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}
```

**Tip:** use a lambda when the logic is short and only used once inline (e.g. as a comparator). If you find yourself needing recursion, it's usually simpler — and faster — to just write a normal function instead of fighting the lambda syntax.


## Stacks

`stack` is a LIFO (Last In, First Out) container adapter — built on top of `deque` by default. All operations are O(1).

```cpp
stack<int> st;
st.push(x);      // insert x on top - O(1)
st.pop();         // remove top element - O(1), does NOT return it
st.top();         // access top element - O(1)
st.size();
st.empty();
```

**Note:** `pop()` doesn't return the removed value (unlike many other languages) — if you need the value, read it with `top()` before calling `pop()`:

```cpp
int val = st.top();
st.pop();
```

There's no iteration or random access on a `stack` — it only exposes the top. If you need to see all elements, you generally shouldn't be using a `stack`.

**Common use:** balanced parentheses check, expression evaluation, "next greater element" style problems.

---

## Queues

`queue` is a FIFO (First In, First Out) container adapter. All operations are O(1).

```cpp
queue<int> q;
q.push(x);       // insert x at the back - O(1)
q.pop();          // remove front element - O(1), does NOT return it
q.front();        // access front element - O(1)
q.back();         // access back element - O(1)
q.size();
q.empty();
```

Like `stack`, `queue` doesn't support iteration or random access — only front and back.

**Common use:** BFS traversal, level-order processing.

---

## Deque

`deque` (double-ended queue) allows O(1) insertion/removal at **both** ends, plus O(1) random access — unlike `vector`, which is only O(1) at the back.

```cpp
deque<int> dq;
dq.push_back(x);    // insert at back - O(1)
dq.push_front(x);   // insert at front - O(1)
dq.pop_back();        // remove from back - O(1)
dq.pop_front();       // remove from front - O(1)
dq.front();           // access front element
dq.back();            // access back element
dq[i];                // random access - O(1)
dq.size();
dq.empty();
```

### Iterating

```cpp
for (int x : dq) cout << x << " ";

for (auto it = dq.begin(); it != dq.end(); it++) cout << *it << " ";
```

`deque` also supports `sort()`, `find()`, etc. via `dq.begin()`/`dq.end()`, same as `vector`.

**Common use:** sliding window problems (e.g. sliding window maximum using a monotonic deque), when you need to push/pop from both ends efficiently.

**Note:** internally, `deque` is a sequence of fixed-size blocks (not one contiguous array like `vector`), so elements aren't guaranteed to be contiguous in memory. This makes it slightly slower than `vector` for pure sequential access, but that's rarely noticeable in practice.

### Why is random access O(1) if a deque isn't contiguous?

A `deque` is implemented as fixed-size **blocks** of contiguous elements, referenced through a **map** (array of pointers to blocks). Accessing `dq[i]` is computed directly — `block_index = i / block_size`, `offset = i % block_size` — both constant-time, so it's O(1), just with a slightly larger constant than `vector`'s direct `base_ptr + i`.

A `list` (linked list) can't do this — there's no way to compute an address from an index, so it must walk `i` nodes from the head, which is O(n). The key distinction isn't "contiguous vs not," it's "can the address be computed in constant time from the index."

### Can we insert in the middle of a deque like a linked list?

Syntactically, yes — `deque` supports `insert()`/`erase()` at arbitrary positions just like `vector`:

```cpp
dq.insert(dq.begin() + i, x);   // insert x at index i
dq.erase(dq.begin() + i);       // erase element at index i
```

But this is **not O(1) like a linked list** — it's **O(min(i, n-i))**, not constant time.

When you insert in the middle, the elements within and after the insertion point (up to the nearer end) need to be shifted, similar to how `vector` shifts elements on a middle insert. Deque implementations are smart about it — they shift whichever side is shorter (front half or back half) rather than always shifting toward the back, so it's often faster in practice than a vector for middle inserts, but it's still linear, not constant.

A linked list gets true O(1) insertion because inserting a node only means relinking a couple of pointers — no data ever moves:

```cpp
newNode->next = current->next;
current->next = newNode;
```

But that O(1) is conditional — it only holds if you already have an iterator/pointer to the insertion point. Finding that position by index is itself O(n) for a linked list, since there's no random access. So `list::insert` is O(1) _at_ a known position, but getting there is the expensive part.

### Quick comparison

|Operation|`deque`|`list`|
|---|---|---|
|Random access `[i]`|O(1)|O(n)|
|Insert at known position|O(min(i, n-i))|O(1)|
|Insert at index i (from scratch)|O(min(i, n-i))|O(n) to find + O(1) to insert = O(n)|

So `deque` trades true O(1) middle-insertion for O(1) random access — it's a middle ground between `vector` and `list`, not a replacement for either.

### Comparison across the three

|Container|Insert front|Insert back|Random access|Iteration|
|---|---|---|---|---|
|`stack`|—|O(1) (top only)|—|No|
|`queue`|—|O(1) push, O(1) pop front|—|No|
|`deque`|O(1)|O(1)|O(1)|Yes|
|`vector`|O(n)|O(1) amortized|O(1)|Yes|

## List

`list` is a doubly linked list — each element has pointers to both the previous and next element. Unlike `vector`/`deque`, elements are **not** stored contiguously or in blocks; they're scattered in memory and linked via pointers.

```cpp
list<int> l;
l.push_back(x);     // insert at back - O(1)
l.push_front(x);    // insert at front - O(1)
l.pop_back();          // remove from back - O(1)
l.pop_front();         // remove from front - O(1)
l.front();             // access front element
l.back();              // access back element
l.size();
l.empty();
```

### No random access

```cpp
l[i];        // does NOT compile - list has no operator[]
```

There's no O(1) indexing — to reach the i-th element you must walk the list from an end, which is O(n). This is the key trade-off vs `deque`.

### Insertion/deletion at a known position — O(1)

```cpp
auto it = l.begin();
advance(it, 2);              // move iterator 2 steps forward - O(n) for a list

l.insert(it, x);             // insert x before it - O(1)
l.erase(it);                 // erase element at it - O(1)
```

This is the main reason to use `list`: if you already hold an iterator to the position (e.g. while traversing), insertion/deletion there is genuinely O(1) — no shifting of other elements, unlike `vector`/`deque`. The cost is only in _finding_ that position.

### Iterating

```cpp
for (int x : l) cout << x << " ";

for (auto it = l.begin(); it != l.end(); it++) cout << *it << " ";
```

Only forward/backward iteration is supported — no `it + 2`, since list iterators aren't random-access. Use `advance(it, k)` or `next(it, k)` instead.

### Other useful member functions

```cpp
l.sort();                 // O(n log n) - list has its OWN sort(), global sort() won't work
l.reverse();               // O(n)
l.unique();                // removes consecutive duplicates - O(n)
l.remove(x);                // removes all elements equal to x - O(n)
l.merge(otherList);         // merges two SORTED lists - O(n)
```

**Note:** `sort(l.begin(), l.end())` (the global algorithm) won't compile on a `list`, because it requires random-access iterators. You must call `l.sort()` — the member function — instead.

**Common use:** rare in competitive programming (vector/deque usually win), but useful when you need frequent middle insertions/deletions and are willing to give up random access — e.g. maintaining an LRU cache's usage order.

---

## Similar containers

### `forward_list`

A **singly** linked list — each node only points to the _next_ node, not the previous one. More memory-efficient than `list` (one pointer per node instead of two), but more restrictive.

```cpp
forward_list<int> fl;
fl.push_front(x);    // O(1) - this is the ONLY end-insertion allowed
fl.pop_front();
fl.front();
```

- No `push_back()`, no `.size()` (by design, to keep it minimal), no backward iteration
- Insertion/erase uses `insert_after()` / `erase_after()` instead of `insert()`/`erase()`, since you can't look at "the element before" a given iterator

```cpp
fl.insert_after(it, x);   // insert after it - O(1)
fl.erase_after(it);       // erase the element after it - O(1)
```

**Common use:** memory-constrained scenarios needing a simple linked structure — rarely used in typical DSA/contest problems, but good to know it exists since interviewers sometimes ask "what's the difference between `list` and `forward_list`."

### Quick comparison

|Container|Structure|Random access|Insert at known position|Insert/erase style|
|---|---|---|---|---|
|`list`|doubly linked|No — O(n)|O(1)|`insert`/`erase`|
|`forward_list`|singly linked|No — O(n)|O(1)|`insert_after`/`erase_after`|
|`deque`|blocks + pointer map|O(1)|O(min(i, n-i))|`insert`/`erase`|
|`vector`|contiguous array|O(1)|O(n)|`insert`/`erase`|

## List

`list` is a doubly linked list — each element has pointers to both the previous and next element. Unlike `vector`/`deque`, elements are **not** stored contiguously or in blocks; they're scattered in memory and linked via pointers.

```cpp
list<int> l;
l.push_back(x);     // insert at back - O(1)
l.push_front(x);    // insert at front - O(1)
l.pop_back();          // remove from back - O(1)
l.pop_front();         // remove from front - O(1)
l.front();             // access front element
l.back();              // access back element
l.size();
l.empty();
```

### No random access

```cpp
l[i];        // does NOT compile - list has no operator[]
```

There's no O(1) indexing — to reach the i-th element you must walk the list from an end, which is O(n). This is the key trade-off vs `deque`.

### Insertion/deletion at a known position — O(1)

```cpp
auto it = l.begin();
advance(it, 2);              // move iterator 2 steps forward - O(n) for a list

l.insert(it, x);             // insert x before it - O(1)
l.erase(it);                 // erase element at it - O(1)
```

This is the main reason to use `list`: if you already hold an iterator to the position (e.g. while traversing), insertion/deletion there is genuinely O(1) — no shifting of other elements, unlike `vector`/`deque`. The cost is only in _finding_ that position.

### Iterating

```cpp
for (int x : l) cout << x << " ";

for (auto it = l.begin(); it != l.end(); it++) cout << *it << " ";
```

Only forward/backward iteration is supported — no `it + 2`, since list iterators aren't random-access. Use `advance(it, k)` or `next(it, k)` instead.

### Other useful member functions

```cpp
l.sort();                 // O(n log n) - list has its OWN sort(), global sort() won't work
l.reverse();               // O(n)
l.unique();                // removes consecutive duplicates - O(n)
l.remove(x);                // removes all elements equal to x - O(n)
l.merge(otherList);         // merges two SORTED lists - O(n)
```

**Note:** `sort(l.begin(), l.end())` (the global algorithm) won't compile on a `list`, because it requires random-access iterators. You must call `l.sort()` — the member function — instead.

**Common use:** rare in competitive programming (vector/deque usually win), but useful when you need frequent middle insertions/deletions and are willing to give up random access — e.g. maintaining an LRU cache's usage order.

---

## Forward List

### `forward_list`

A **singly** linked list — each node only points to the _next_ node, not the previous one. More memory-efficient than `list` (one pointer per node instead of two), but more restrictive.

```cpp
forward_list<int> fl;
fl.push_front(x);    // O(1) - this is the ONLY end-insertion allowed
fl.pop_front();
fl.front();
```

- No `push_back()`, no `.size()` (by design, to keep it minimal), no backward iteration
- Insertion/erase uses `insert_after()` / `erase_after()` instead of `insert()`/`erase()`, since you can't look at "the element before" a given iterator

```cpp
fl.insert_after(it, x);   // insert after it - O(1)
fl.erase_after(it);       // erase the element after it - O(1)
```

**Common use:** memory-constrained scenarios needing a simple linked structure — rarely used in typical DSA/contest problems, but good to know it exists since interviewers sometimes ask "what's the difference between `list` and `forward_list`."

### Quick comparison

|Container|Structure|Random access|Insert at known position|Insert/erase style|
|---|---|---|---|---|
|`list`|doubly linked|No — O(n)|O(1)|`insert`/`erase`|
|`forward_list`|singly linked|No — O(n)|O(1)|`insert_after`/`erase_after`|
|`deque`|blocks + pointer map|O(1)|O(min(i, n-i))|`insert`/`erase`|
|`vector`|contiguous array|O(1)|O(n)|`insert`/`erase`|

## Set

`set` stores **unique** elements in sorted order, implemented as a self-balancing BST (red-black tree). Insert, erase, and find are **O(log n)**.

```cpp
set<int> s;
s.insert(x);        // insert x - O(log n), no-op if already present
s.erase(x);          // erase x by value - O(log n)
s.count(x);          // returns 0 or 1 (elements are unique)
s.find(x);           // returns iterator to x, or s.end() if not found
s.size();
s.empty();
s.clear();
```

### Iterating (always sorted order)

```cpp
for (int x : s) cout << x << " ";

for (auto it = s.begin(); it != s.end(); it++) cout << *it << " ";
```

### Useful operations

```cpp
*s.begin();          // smallest element
*s.rbegin();         // largest element

s.lower_bound(x);    // iterator to first element >= x - O(log n)
s.upper_bound(x);    // iterator to first element > x - O(log n)
```

---

## Multiset

Same as `set` but allows duplicate elements.

```cpp
multiset<int> ms;
ms.insert(x);            // O(log n)
ms.count(x);              // number of occurrences - O(log n + count)
```

**Pitfall — `erase(value)` deletes ALL occurrences:**

```cpp
ms.erase(x);              // erases EVERY occurrence of x - O(log n + count)
ms.erase(ms.find(x));     // erases only ONE occurrence - O(log n)
```

This trips people up constantly — if you only want to remove a single instance of `x`, you must erase via an iterator, not the value directly.

---

## unordered_set

Same interface as `set`, backed by a **hash table**. O(1) average for insert/erase/find, but:

- **No ordering** — iteration order is unspecified and can change between insertions
- No `lower_bound`/`upper_bound` (those need order)
- Worst case O(n) per operation, due to hash collisions (rare in practice, but exploitable — see pitfall below)

```cpp
unordered_set<int> us;
us.insert(x);
us.find(x);
us.count(x);
```

Use `set` when you need sorted order or `lower_bound`/`upper_bound`. Use `unordered_set` when you just need fast membership checks and don't care about order.

---

## unordered_multiset

`unordered_set` + duplicates allowed — same relationship as `multiset` is to `set`.

```cpp
ums.insert(x);
ums.count(x);          // number of occurrences
ums.erase(x);           // erases ALL occurrences - same pitfall as multiset
ums.erase(ums.find(x)); // erases only ONE
```

---

## Common pitfalls (across the whole set family)

### 1. Erasing while iterating

```cpp
for (auto it = s.begin(); it != s.end(); it++) {
    if (*it % 2 == 0) {
        s.erase(it);     // BUG: it is now invalidated, next it++ is undefined behavior
    }
}
```

`erase()` invalidates the iterator passed to it. The fix: `erase()` returns the next valid iterator, so use that instead of a separate `it++`:

```cpp
for (auto it = s.begin(); it != s.end(); ) {
    if (*it % 2 == 0) {
        it = s.erase(it);   // erase returns iterator to the next element
    } else {
        it++;
    }
}
```

### 2. `multiset`/`unordered_multiset` — `erase(value)` removes everything

Already covered above, but worth repeating since it's the single most common bug: `ms.erase(x)` is not "erase one `x`", it's "erase all `x`". Use `ms.erase(ms.find(x))` for a single removal.

### 3. Assuming `unordered_set` preserves insertion order

```cpp
unordered_set<int> us = {5, 1, 3};
for (int x : us) cout << x << " ";   // order is NOT guaranteed to be 5 1 3, or sorted
```

If you need predictable order, use `set` (sorted) — never rely on `unordered_set`'s iteration order for correctness.

### 4. Custom objects need a hash function for `unordered_set`

```cpp
unordered_set<pair<int,int>> us;   // does NOT compile - no default hash for pair
```

`set` works out of the box for `pair`/custom types (via `operator<`), but `unordered_set` needs an explicit hash specialization for anything beyond built-in types. If this comes up, it's usually simpler to just use `set<pair<int,int>>` instead.

### 5. Adversarial worst-case for `unordered_set` (competitive programming specific)

On judges like Codeforces, `unordered_set`/`unordered_map` can be deliberately hash-flooded by an adversarial test case, degrading every operation to O(n) and causing TLE — this has actually happened in real contests. Safer default in contests: prefer `set`/`map` unless you specifically need the speed and know how to guard against it (e.g. custom hash with a random seed).

### 6. Global vs member `lower_bound`

Always call `.lower_bound()`/`.upper_bound()` as **member functions** (`s.lower_bound(x)`), not the global `lower_bound(s.begin(), s.end(), x)`. The global version needs random-access iterators to jump efficiently — on a `set`, it silently falls back to walking one element at a time, making it O(n) instead of O(log n), even though it still compiles and runs.

### 7. Global vs member `find`

Same issue applies to `find`. `s.find(x)` (member function) is O(log n), using the tree structure directly. `find(s.begin(), s.end(), x)` (the global algorithm, the one used on `vector`) is a linear scan — O(n) — since it has no knowledge of the set's internal ordering. Both compile, both "work," but only the member version is efficient. Always prefer `s.find(x)`.

### 8. Computing "elements greater than `*it`" with iterator subtraction

A common instinct carried over from `vector` is to write `s.end() - it` to count elements after `it`. This **does not compile** on a `set` — set iterators are bidirectional, not random-access, so `-` isn't defined on them.

The correct tool is `distance(it, s.end())` from `<iterator>`:

```cpp
int countGreater = distance(it, s.end());   // number of elements after it (exclusive)
```

**Time complexity note:** `distance` is O(1) only for random-access iterators (`vector`, `deque`). For `set`/`list` (bidirectional iterators), it's **O(n)** — it steps through elements one at a time internally, same as manually incrementing a counter in a loop. So `distance` fixes the compile error, but doesn't give O(log n)/O(1) speed.

**Real fix — PBDS ordered_set:** If you need this kind of "rank" query frequently (elements greater/smaller than x, or "what's the k-th smallest element"), GCC's Policy-Based Data Structures (PBDS) provide an `ordered_set` that supports these in O(log n):

```cpp
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

ordered_set os;
os.insert(x);

os.order_of_key(x);      // number of elements STRICTLY LESS than x - O(log n)
*os.find_by_order(k);    // k-th smallest element (0-indexed) - O(log n)
```

So "elements greater than x" becomes:

```cpp
int countGreater = os.size() - os.order_of_key(x + 1);   // adjust +1 depending on whether x itself should count
```

PBDS isn't part of standard STL (it's a GCC extension, so it won't work on non-GCC compilers or some online judges), but it's very commonly used in competitive programming specifically to solve this class of problem — worth mentioning as "the tool for this job" even if the syntax looks unfamiliar at first.

## Map

`map` stores key-value pairs, sorted by key, implemented as a self-balancing BST. Insert, erase, and find are **O(log n)**.

```cpp
map<string, int> mp;
mp[key] = value;              // insert or update - O(log n)
mp.insert({key, value});      // insert only if key doesn't exist - O(log n)
mp.erase(key);                  // erase by key - O(log n)
mp.count(key);                  // 0 or 1 (keys are unique)
mp.find(key);                   // returns iterator, or mp.end() if not found
mp.size();
mp.empty();
```

### Iterating (sorted by key)

```cpp
for (auto &p : mp) cout << p.first << " " << p.second << endl;

for (auto &[key, value] : mp) cout << key << " " << value << endl;   // structured bindings (C++17)

for (auto it = mp.begin(); it != mp.end(); it++) cout << it->first << " " << it->second << endl;
```

### Useful operations

```cpp
mp.lower_bound(key);   // iterator to first key >= given key - O(log n)
mp.upper_bound(key);   // iterator to first key > given key - O(log n)
```

Same rule as `set`: always call these as **member functions**, not the global algorithm — same O(n) vs O(log n) trap applies here too.

---

## Multimap

Same as `map` but allows duplicate keys.

```cpp
multimap<string, int> mm;
mm.insert({key, value});
mm.count(key);            // number of entries with this key

// getting all values for a key
auto range = mm.equal_range(key);
for (auto it = range.first; it != range.second; it++) {
    cout << it->second << endl;
}
```

**Note:** `multimap` has no `operator[]` — since a key can map to multiple values, `mm[key]` wouldn't make sense, so it simply isn't defined.

---

## unordered_map

Same interface as `map`, backed by a hash table. O(1) average for insert/erase/find, but no ordering and no `lower_bound`/`upper_bound` — same trade-off as `unordered_set` vs `set`.

```cpp
unordered_map<string, int> ump;
ump[key] = value;
ump.find(key);
ump.count(key);
```

---

## unordered_multimap

`unordered_map` + duplicate keys allowed — same relationship as `multimap` is to `map`.

```cpp
umm.insert({key, value});
umm.count(key);
auto range = umm.equal_range(key);
```

---

## Common pitfalls (across maps)

### 1. `operator[]` silently inserts

```cpp
map<string, int> mp;
if (mp["hello"] > 0) { ... }   // BUG: this INSERTS "hello" -> 0 if it doesn't already exist
```

Using `mp[key]` to just _check_ a value is a very common bug — it creates the key with a default value (0 for `int`) as a side effect, even in a plain read-like context. If you only want to check without inserting, use `find` or `count`:

```cpp
if (mp.find("hello") != mp.end()) { ... }   // safe, doesn't insert
if (mp.count("hello")) { ... }               // also safe
```

This matters a lot when you're counting distinct keys later, or iterating — you can end up with unexpected extra entries.

### 2. Erasing while iterating

Same issue as `set`/`multiset` — `erase()` invalidates the iterator passed to it.

```cpp
for (auto it = mp.begin(); it != mp.end(); ) {
    if (it->second == 0) {
        it = mp.erase(it);   // use the returned iterator
    } else {
        it++;
    }
}
```

### 3. `multimap`/`unordered_multimap` — `erase(key)` removes all entries for that key

```cpp
mm.erase(key);   // removes EVERY entry with this key, not just one
```

Same trap as `multiset`. To remove a single entry, erase via an iterator obtained from `find`/`equal_range`.

### 4. Structured bindings modify through reference only with `&`

```cpp
for (auto [key, value] : mp) value = 0;    // modifies a COPY, doesn't change mp
for (auto &[key, value] : mp) value = 0;   // modifies the actual map - correct
```

Forgetting the `&` is a quiet bug — the loop compiles and "runs," but any modification is lost since you're iterating over copies of the pairs.

### 5. Global vs member `lower_bound`/`find`

Exactly the same trap as with `set`: `mp.lower_bound(key)`/`mp.find(key)` are O(log n); the global `<algorithm>` versions on `mp.begin()`/`mp.end()` degrade to O(n) since map iterators aren't random-access. Always use the member functions.

### 6. Adversarial hash flooding (competitive programming specific)

Same as `unordered_set` — `unordered_map` can be hash-flooded on judges like Codeforces to force O(n) behavior. Prefer `map` unless the extra speed of `unordered_map` is actually needed and you're prepared to guard against it.

### 7. `unordered_map` needs a hash function for non-built-in key types

`std::hash` only has built-in specializations for primitive types, `string`, and pointers. Keys like `pair`, `tuple`, or a custom struct won't compile in an `unordered_map` without extra work:

```cpp
unordered_map<pair<int,int>, int> ump;   // does NOT compile - no std::hash<pair<int,int>>
```

Fix — provide a custom hash functor:

```cpp
struct pair_hash {
    size_t operator()(const pair<int,int>& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};
unordered_map<pair<int,int>, int, pair_hash> ump;   // now compiles
```

`map<pair<int,int>, int>` works immediately with zero setup, since `pair` already has `operator<`, which is all a BST-based `map` needs. When the key is a `pair`/`tuple`/struct and you're short on time in a contest, it's often simpler to just use `map` instead of writing a custom hash.

### 8. Custom struct keys need `operator<` for `map` (the `unordered_map` equivalent problem)

The flip side of #7 — if you use a custom struct as a key in a regular `map` (not `unordered_map`), it needs `operator<` defined, or it won't compile either:

```cpp
struct Point { int x, y; };
map<Point, int> mp;   // does NOT compile - no operator< for Point

struct Point {
    int x, y;
    bool operator<(const Point& other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};
map<Point, int> mp;   // now compiles
```

### 9. `mp[key]` vs `mp.at(key)` for reading

```cpp
cout << mp[key];        // if key doesn't exist, inserts it with default value, then prints that default
cout << mp.at(key);     // if key doesn't exist, throws std::out_of_range instead
```

If you want a _read_ that fails loudly instead of silently inserting garbage, `mp.at(key)` is the safer choice — especially useful while debugging, since a wrong/missing key throws immediately instead of quietly corrupting your map with an extra zero-valued entry.

### 10. Erasing one entry doesn't invalidate the rest of your iterators (unlike `vector`)

Worth knowing as a contrast, not really a bug: for `map`/`set`, erasing an iterator only invalidates _that_ iterator — every other iterator, pointer, and reference into the map stays valid. This is different from `vector`, where erasing/inserting anywhere can invalidate iterators past that point due to reallocation/shifting. It's why the erase-in-a-loop pattern (`it = mp.erase(it)`) works cleanly for maps/sets — you only ever need to worry about the one iterator you just erased.

## Priority Queue

`priority_queue` is a heap — it always gives you access to the largest (or smallest, if configured) element in O(1), with O(log n) push/pop. Internally, it's usually implemented on top of a `vector`.

### Basic usage — max-heap by default

```cpp
priority_queue<int> pq;
pq.push(x);       // insert x - O(log n)
pq.pop();          // remove the top (largest) element - O(log n), does NOT return it
pq.top();          // access the largest element - O(1)
pq.size();
pq.empty();
```

```cpp
priority_queue<int> pq;
pq.push(3); pq.push(1); pq.push(4); pq.push(1); pq.push(5);
while (!pq.empty()) {
    cout << pq.top() << " ";   // 5 4 3 1 1
    pq.pop();
}
```

**Pitfall:** just like `stack`/`queue`, `pop()` doesn't return the value. Read `top()` before calling `pop()` if you need it.

### Min-heap

The most common thing people get wrong: `priority_queue` template signature.

```cpp
priority_queue<int, vector<int>, greater<int>> pq;
```

Three template parameters:

1. `int` — the type of element stored
2. `vector<int>` — the underlying container (almost always `vector`, rarely changed)
3. `greater<int>` — the comparator

**Why `greater<int>` gives a min-heap, not a max-heap, is the part people find confusing:** the comparator answers "does the first argument have lower priority than the second?" With `greater<int>`, `greater(a, b)` is true when `a > b` — meaning larger elements are treated as "lower priority," so they sink down and the smallest ends up on top. It feels backwards at first because `greater` sounds like it should give you the greatest on top, but it's about ordering priority, not literal size.

If this is confusing, an easier mental model: **default (`less`) → max-heap, `greater` → min-heap.** Just remember it as a fixed swap, without overthinking the internal logic during a live test.

### Custom comparator — struct with `operator()`

For anything beyond plain `int`/`greater`/`less`, define a struct with `operator()`:

```cpp
struct Compare {
    bool operator()(int a, int b) {
        return a > b;   // same effect as greater<int> - min-heap
    }
};
priority_queue<int, vector<int>, Compare> pq;
```

**The rule to remember:** if your comparator returns `true` when `a` should be **lower priority** than `b` (i.e., `a` should come out later), you get a heap where the "smallest by this rule" comes out first... but this is exactly where people get confused, so here's the concrete way to think about it instead:

> **Return `true` if `a` should be popped _after_ `b`.**

That's it. If you want the smallest sum to be on top, return `true` when `a`'s sum is greater than `b`'s sum (meaning `a` goes later).

### Custom comparator — pairs

Very common in problems (e.g. Dijkstra: `{distance, node}`):

```cpp
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
// min-heap by pair's default comparison: compares .first first, then .second
pq.push({5, 10});
pq.push({2, 7});
pq.push({2, 3});
// pop order: {2,3}, {2,7}, {5,10}  -- ties broken by .second
```

`pair`'s built-in `<`/`>` compares `.first` first, then `.second` as a tiebreaker — this is often exactly what you want (e.g. distance first, node ID as tiebreaker), so you frequently don't need a custom comparator at all when using pairs.

### Custom comparator — struct/class objects

```cpp
struct Task {
    string name;
    int priority;
};

struct CompareTask {
    bool operator()(const Task& a, const Task& b) {
        return a.priority < b.priority;   // higher priority value = comes out first (max-heap on priority)
    }
};

priority_queue<Task, vector<Task>, CompareTask> pq;
pq.push({"Email", 2});
pq.push({"Fire", 10});
pq.push({"Meeting", 5});
// pop order: Fire(10), Meeting(5), Email(2)
```

### Custom comparator — lambda (C++11 onwards)

Lambdas need slightly different syntax since the comparator becomes part of the _type_, not just a value:

```cpp
auto cmp = [](const pair<int,int>& a, const pair<int,int>& b) {
    return a.second > b.second;   // min-heap based on .second
};
priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(cmp)> pq(cmp);
```

Two things people forget here:

1. `decltype(cmp)` — you need the _type_ of the lambda as the template parameter (lambdas have unique unnamed types, so you can't write the type directly).
2. `pq(cmp)` — you must also pass the lambda **instance** to the constructor. Just having the type isn't enough; the priority queue needs an actual comparator object to call.

### Quick reference — comparator logic

|Comparator|Result|Mental model|
|---|---|---|
|(none, default)|Max-heap|`less<T>` used internally|
|`greater<T>`|Min-heap|Built-in flip|
|Custom struct/lambda returning `a < b`|Max-heap on that field|Same as default logic|
|Custom struct/lambda returning `a > b`|Min-heap on that field|Same as `greater` logic|

### Common pitfalls

**1. Forgetting the second template argument when providing a custom comparator**

```cpp
priority_queue<int, greater<int>> pq;   // WRONG - this treats greater<int> as the CONTAINER type, doesn't compile
priority_queue<int, vector<int>, greater<int>> pq;  // correct
```

**2. Using `priority_queue` when you need to see/modify arbitrary elements**

`priority_queue` only exposes `top()` — no iteration, no access to the second-largest, no way to decrease a specific element's priority (the classic "decrease-key" problem in Dijkstra). The common workaround in competitive programming is _lazy deletion_: push a new (updated) entry and just skip over stale entries when popped, rather than trying to modify the heap in place.

**3. Comparator must be a strict weak ordering**

If your comparator isn't consistent (e.g. `cmp(a,b)` and `cmp(b,a)` both return `true`), you get undefined behavior — heap corruption, crashes, or silently wrong output. Common cause: using `<=`/`>=` instead of `<`/`>` in a comparator. Always use strict inequality.


## Strings

`std::string` is a dynamic character array with a lot of built-in convenience over raw C-strings/char arrays.

### Basic operations

```cpp
string s = "hello";
s.length();      // or s.size() - same thing, O(1)
s.empty();
s += " world";    // concatenation - O(n) (may reallocate)
s[i];             // access character at index i - O(1)
s.at(i);          // bounds-checked access - throws if out of range
s.front();        // first character
s.back();         // last character
```

### Substrings and searching

```cpp
s.substr(pos);          // substring from pos to end - O(n)
s.substr(pos, len);     // substring of length len starting at pos - O(n)

s.find("wor");           // returns index of first occurrence, or string::npos if not found - O(n*m)
s.find("wor", 3);        // search starting from index 3
s.rfind("o");             // last occurrence, searching backwards

if (s.find("wor") != string::npos) { ... }   // standard pattern to check "does substring exist"
```

**Pitfall:** `string::npos` is a huge unsigned value (essentially -1 cast to `size_t`), not an index. Comparing `s.find(x) == -1` instead of `== string::npos` is a common near-miss — it actually still works because of how `-1` converts, but it's fragile and easy to get wrong if you change the comparison slightly. Always use `string::npos` explicitly.

### Comparison

```cpp
s1 == s2;        // value comparison (unlike C strings, no need for strcmp)
s1 < s2;          // lexicographic comparison - works directly with sort(), map keys, etc.
```

### Sorting a string's characters

```cpp
sort(s.begin(), s.end());              // sorts characters in place - O(n log n)
```

**Common use:** checking anagrams by sorting both strings and comparing.

### Reversing

```cpp
reverse(s.begin(), s.end());   // in-place reverse - O(n)
```

### Converting between string and number

```cpp
string s = to_string(123);          // int -> string
string s2 = to_string(3.14);        // double -> string

int x = stoi("123");                 // string -> int
long long y = stoll("123456789012"); // string -> long long
double d = stod("3.14");             // string -> double
```

**Pitfall:** `stoi`/`stoll` throw `std::invalid_argument` if the string doesn't start with a valid number (e.g. `stoi("abc")`), and `std::out_of_range` if the number is too large to fit the target type. Worth wrapping in a try/catch if input isn't guaranteed clean — but in most CP problems, input is well-formed, so this is more of a "know it exists" than something to handle every time.

### Character checks (`<cctype>`)

```cpp
isdigit(c);       // true if c is '0'-'9'
isalpha(c);        // true if c is a letter
isupper(c);         // true if c is uppercase
islower(c);          // true if c is lowercase
toupper(c);           // converts to uppercase
tolower(c);            // converts to lowercase
```

**Note:** these take an `int`, and technically expect the value to be representable as `unsigned char` or `EOF` — passing a plain (signed) `char` with a negative value (can happen with non-ASCII input) is undefined behavior. In practice, for standard ASCII input in CP problems this is rarely an issue, but casting to `unsigned char` first is the "correct" way: `isdigit((unsigned char)c)`.

### Common pitfalls

**1. Concatenation in a loop is O(n²) if done carelessly**

```cpp
string result = "";
for (int i = 0; i < n; i++) {
    result = result + someChar;   // creates a new string each time - O(n) per iteration, O(n²) total
}
```

Prefer `+=` or `push_back`, which the standard library can grow more efficiently (amortized O(1) per append, same idea as `vector::push_back`):

```cpp
string result;
for (int i = 0; i < n; i++) {
    result += someChar;   // or result.push_back(someChar);
}
```

**2. Modifying a string while iterating with a range-based for loop by value**

```cpp
for (char c : s) c = toupper(c);   // modifies a COPY, s is unchanged
for (char &c : s) c = toupper(c);  // correct - modifies s in place
```

Same `&`-forgetting trap as with `map`/`pair` structured bindings.

**3. Comparing `char` and `int` implicitly**

```cpp
char c = '5';
if (c == 5) { ... }        // BUG: compares ASCII value of '5' (53) with int 5 - always false
if (c == '5') { ... }       // correct - compares character to character
if (c - '0' == 5) { ... }   // correct way to compare digit VALUE to 5
```

This trips people up specifically when converting digit characters to their numeric value — `c - '0'` is the idiomatic way to do it.

**4. `substr` with an out-of-range starting position throws**

```cpp
string s = "hello";
s.substr(10);   // throws std::out_of_range - pos must be <= s.length()
```

Worth a mental note if you're computing substring positions dynamically (e.g. `s.substr(i, len)` where `i` might exceed the string length due to an off-by-one).

## Algorithms (`<algorithm>` / `<numeric>` / `<cmath>`)

### `min` / `max` / `minmax`

```cpp
min(a, b);            // smaller of two values
max(a, b);            // larger of two values
minmax(a, b);         // returns {min, max} as a pair

min({1, 5, 3, 2});    // works with initializer lists too - returns 1
max_element(v.begin(), v.end());   // iterator to largest element in a range - O(n)
```

### `rotate`

Rotates elements left, so the specified element becomes the new first element.

```cpp
vector<int> v = {1, 2, 3, 4, 5};
rotate(v.begin(), v.begin() + 2, v.end());
// v is now {3, 4, 5, 1, 2} - the element at index 2 becomes the new first element
```

### `fill` / `fill_n`

```cpp
vector<int> v(5);
fill(v.begin(), v.end(), 7);       // sets every element to 7
fill_n(v.begin(), 3, 7);           // sets first 3 elements to 7
```

### `gcd` / `lcm` (`<numeric>`, C++17)

```cpp
gcd(12, 18);   // 6
lcm(4, 6);      // 12
```

Before C++17, people wrote their own Euclidean algorithm for this — now it's built in.

### `log2` / `pow` (`<cmath>`)

```cpp
log2(x);        // logarithm base 2, returns a double
pow(base, exp); // base^exp, returns a double
```

**Pitfall — `pow` returns a `double`, not an `int`:** even `pow(2, 10)` can come back as `1023.9999...` due to floating-point imprecision, so casting it directly to `int` can silently give the wrong answer. For integer powers, prefer a manual loop or fast exponentiation instead of relying on `pow`:

```cpp
int result = (int)pow(2, 10);       // risky - may round down due to floating point error
int result2 = 1 << 10;               // safe for powers of 2 - bit shift
```

**Pitfall — `log2` on 0:** `log2(0)` returns `-inf`, not an error — easy to silently propagate a bad value through later calculations if you don't check for it explicitly.

### Bit tricks (`__builtin_*`, GCC extensions — not technically STL, but ubiquitous in CP)

```cpp
__builtin_popcount(x);     // number of set bits (1s) in x - for int
__builtin_popcountll(x);   // same, for long long
__builtin_clz(x);          // count leading zeros (from MSB) - for int
__builtin_ctz(x);          // count trailing zeros (from LSB) - for int
```

**Pitfall:** `__builtin_popcount` and friends are GCC/Clang-specific — they're not standard C++ and won't compile on MSVC. Fine for Codeforces/most judges (which use GCC), but not portable in general.

## Modular Arithmetic

When numbers get large (common in counting/DP problems), results are usually taken modulo a large prime like `1e9 + 7` or `998244353` to keep them within integer range. A few operations need special care to avoid overflow or incorrect negative results.

```cpp
const int MOD = 1e9 + 7;
```

### Mod addition

```cpp
int modAdd(int a, int b) {
    return (a % MOD + b % MOD) % MOD;
}
```

Taking `% MOD` on each operand before adding guards against `a`/`b` already being negative or larger than expected — cheap insurance even if you believe they're already reduced.

### Mod subtraction

```cpp
int modSub(int a, int b) {
    return ((a % MOD - b % MOD) + MOD) % MOD;
}
```

**Pitfall — negative results:** in C++, `%` can return a **negative** value when the left operand is negative (unlike Python, where `%` always returns a non-negative result for a positive modulus). So `(a - b) % MOD` can come out negative even though a "mod result" should always be in `[0, MOD-1]`. Adding `MOD` before the final `% MOD` shifts it back into the correct positive range:

```cpp
int a = 3, b = 5, MOD = 7;
(a - b) % MOD;         // -2 % 7 = -2 in C++  (WRONG if you expected a value in [0, MOD-1])
((a - b) + MOD) % MOD; // (-2 + 7) % 7 = 5     (correct)
```

### Mod multiplication

```cpp
long long modMul(long long a, long long b) {
    return ((a % MOD) * (b % MOD)) % MOD;
}
```

**Pitfall — overflow before the mod is applied:** if `a` and `b` are both close to `MOD` (~1e9), their product can be as large as ~1e18, which **overflows a 32-bit `int`** (max ~2.1e9) instantly, and even overflows if you forget to use `long long` for the multiplication step. Always multiply using `long long`, even if `a`/`b` themselves are declared as `int`:

```cpp
int a = 1e9, b = 1e9;
int bad = (a * b) % MOD;              // WRONG - overflows int before the multiplication even completes
long long good = ((long long)a * b) % MOD;  // correct - cast at least one operand to long long first
```

This overflow bug is extremely common — the multiplication happens in `int` arithmetic _before_ the assignment to a `long long` variable even takes place, so simply declaring the result as `long long` isn't enough; the cast has to happen on the operands themselves.

### Quick reference

|Operation|Formula|
|---|---|
|Add|`(a % MOD + b % MOD) % MOD`|
|Subtract|`((a % MOD - b % MOD) + MOD) % MOD`|
|Multiply|`((long long)(a % MOD) * (b % MOD)) % MOD`|

Division is a bit complicated and involves a bit of number theory. Please explore it on your own.


## Practice Set for STL

### HackerRank
https://www.hackerrank.com/domains/cpp?filters%5Bsubdomains%5D%5B%5D=stl
### Github
https://github.com/Salf1-Sabit/STL-Problems
### STL problems
- Task 1: https://codeforces.com/group/MWSDmqGsZm/contest/219432/problem/Z
- ⁠Task 2: https://codeforces.com/group/MWSDmqGsZm/contest/219432/problem/K
- Task 3: https://www.codechef.com/LRNDSA02/problems/STUPMACH
- Task 4: https://codeforces.com/problemset/problem/734/A
- Task 5: https://codeforces.com/group/MWSDmqGsZm/contest/219432/problem/E
- Task 6: https://codeforces.com/group/MWSDmqGsZm/contest/219158/problem/X 
- ⁠Task 7: https://codeforces.com/problemset/problem/4/A
- Task 8: https://codeforces.com/problemset/problem/71/A
- Task 9: https://codeforces.com/problemset/problem/50/A
- Task 10: https://leetcode.com/problems/kth-largest-element-in-a-stream/
- Task 11: https://leetcode.com/problems/valid-parentheses/ 
- ⁠Task 12: https://www.codechef.com/LRNDSA02/problems/ZCO12001 
- ⁠Task 13: https://www.codechef.com/LRNDSA02/problems/COMPILER
- Task 14: https://codeforces.com/problemset/problem/1345/B
- Task 15: https://www.codechef.com/LRNDSA03/problems/SAVKONO


## Lecture Links

https://youtu.be/RRVYpIET_RU?si=gVz-Bnmlnz6L-wqh

https://www.youtube.com/watch?v=R5BEcvTVZj0&list=PLauivoElc3gh3RCiQA82MDI-gJfXQQVn

https://youtu.be/JUp_6L12l1U?si=MX1pn2RDwtm_xoaG


