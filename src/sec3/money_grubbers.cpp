#include "common.h"

using PriceTB = vector<pair<int, float>>;

namespace solve1 {
  float memo[100] = {0};
  float solve(const PriceTB& ptb, int buyn) {
    if (buyn == 0) return 0;
    if (memo[buyn]) return memo[buyn];
    float money = numeric_limits<float>::max();
    for (const auto& [nx, px] : ptb) {
      if (nx > buyn) continue;
      float mx = solve(ptb, buyn - nx) + px;
      money = std::min(money, mx);
    }
    return memo[buyn] = money;
  }
} // namespace solve1

namespace solve2 {
  float solve(const PriceTB& ptb, int buyn) {
    float dp[100] = {0};
    for (int i = 1; i <= buyn; ++i) {
      float money = numeric_limits<float>::max();
      for (const auto& [nx, px] : ptb) {
        if (nx > i) continue;
        money = std::min(money, dp[i - nx] + px);
      }
      dp[i] = money;
    }
    return dp[buyn];
  }
} // namespace solve2

// clang-format off
int main() {
  int m; float p;
  PriceTB ptb; vector<int> buyn;
  std::cin >> p >> m;
  ptb.reserve(m + 1);
  ptb.push_back({1, p});
  for (int i = 0; i < m; i++) {
    int n; std::cin >> n >> p;
    ptb.push_back({n, p});
  }
  while(std::cin >> m) {
    buyn.push_back(m);
  }
  println("{} || {}", ptb, buyn);
  for(int n: buyn) {
    println("Buy {} for ${:.2f}", n ,solve1::solve(ptb, n));
  }
  println("====");
  for(int n: buyn) {
    println("Buy {} for ${:.2f}", n ,solve2::solve(ptb, n));
  }
}
