#include <iostream>

int p[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
unsigned long long n;
unsigned long long ans,
    ans_num;  // ans is the largest anti-prime not exceeding n (updated continuously), ans_sum is
              // the number of divisors of ans.

// depth: which prime is currently being enumerated
// temp: current value when the divisor count is num
// num: current divisor count
// up: power of the previous prime, limiting the current exponent upper bound
void dfs(int depth, unsigned long long temp, unsigned long long num, int up) {
  if (depth >= 16 || temp > n) return;
  if (num > ans_num) {  // Update the answer
    ans = temp;
    ans_num = num;
  }
  if (num == ans_num && ans > temp) ans = temp;  // Update the answer
  for (int i = 1; i <= up; i++) {
    if (temp * p[depth] > n)
      break;  // Pruning: if adding this multiplier exceeds ans, it cannot be optimal
    dfs(depth + 1, temp *= p[depth], num * (i + 1),
        i);  // Take this multiplier and search the next multiplier
  }
  return;
}

using std::cin;
using std::cout;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  while (cin >> n) {
    ans_num = 0;
    dfs(0, 1, 1, 60);
    cout << ans << '\n';
  }
  return 0;
}
