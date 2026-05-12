#include <iostream>
constexpr int p[15] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
// The product of primes in p exceeds 1e18

int n;
long long ans = 2e18;

// u: index in p of the prime currently being considered
// num: current constructed value
// cnt: number of divisors of the current value
// pre: exponent of the previous factor, limiting the exponent chosen this time
void dfs(int u, long long num, long long cnt, int pre) {
  if (cnt > n || u >= 15) return;
  if (cnt == n) return ans = std::min(ans, num), void();
  for (int i = 1; i <= pre; ++i) {
    if (num * p[u] > ans) break;  // Pruning
    dfs(u + 1, num *= p[u], cnt * (i + 1), i);
  }
}

int main() {
  std::cin >> n;
  dfs(0, 1, 1, 59);  // floor(log2(1e18))=19
  std::cout << ans << std::endl;
  return 0;
}
