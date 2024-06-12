#include "common.h"

namespace solve1 {
  int cache[100] = {0};
  int solve_t(int m, int n, int t) {
    if (t == 0) return 0;
    if (t < 0) return -1;
    int& tr = cache[t];
    if (tr) return tr;
    int a = solve_t(m, n, t - m);
    int b = solve_t(m, n, t - n);
    if (a < 0 && b < 0) { return tr = -1; };
    return tr = 1 + std::max(a, b);
  }
  int solve(int m, int n, int t) {
    if (m > n) std::swap(m, n);
    for (int x = t; x > 0; x--) {
      int ans = solve_t(m, n, x);
      if (ans > 0) return ans;
    }
    return 0;
  }
} // namespace solve1

namespace solve2 {
  int solve(int m, int n, int t) {
    int dp[100] = {0};
    if (m > n) std::swap(m, n);
    for (int i = 1; i <= t; ++i) {
      if (i < m) {
        dp[i] = -1;
        continue;
      }
      int a = dp[i - m];
      int b = i >= n ? dp[i - n] : -1;
      if (a == -1 && b == -1) {
        dp[i] = -1;
      } else {
        dp[i] = std::max(a, b) + 1;
      }
    }
    for (int i = t; i >= 0; --i) {
      if (dp[i] > 0) return dp[i];
    }
    return 0;
  }
} // namespace solve2

void run(int m, int n, int t) {
  println("{}", solve1::solve(4, 2, 88));
  println("{}", solve2::solve(4, 2, 88));
}

int main() { run(4, 2, 88); }
