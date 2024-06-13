#include "common.h"

using Score = pair<bool, int>;
using Scores = vector<Score>;

template <size_t N>
struct Access {
  int (&p)[N][N];
  int get(int a, int b) const { return (a >= 0 && b >= 0) ? p[a][b] : 0; }
  int operator()(int a, int b) const { return get(a, b); }
};

namespace solve1 {
  int solve(const Scores& sc1, const Scores& sc2) {
    const int len = std::size(sc1);
    int dp[100][100] = {0};
    Access dpp{dp};
    for (int i = 0; i < len; ++i) {
      for (int j = 0; j < len; ++j) {
        const auto& [b1, v1] = sc1[i];
        const auto& [b2, v2] = sc2[j];
        int sc = ((b1 && !b2 && v1 > v2) || !b1 && b2 && v1 < v2) ? v1 + v2 : 0;
        int _1st = sc + dpp(i - 1, j - 1);
        int _2nd = dpp(i, j - 1);
        int _3rd = dpp(i - 1, j);
        dp[i][j] = std::max({_1st, _2nd, _3rd});
      }
    }
    return dp[len - 1][len - 1];
  }
} // namespace solve1

namespace solve2 {
  int memo[100][100];
  int solve(const Scores& sc1, const Scores& sc2, int i, int j) {
    if (i < 0 || j < 0) return 0;
    if (memo[i][j] > 0) return memo[i][j];
    const auto& [b1, v1] = sc1[i];
    const auto& [b2, v2] = sc2[j];
    int sc = ((b1 && !b2 && v1 > v2) || !b1 && b2 && v1 < v2) ? v1 + v2 : 0;
    int _1st = sc + solve(sc1, sc2, i - 1, j - 1);
    int _2nd = solve(sc1, sc2, i, j - 1);
    int _3rd = solve(sc1, sc2, i - 1, j);
    return memo[i][j] = std::max({_1st, _2nd, _3rd});
  }
  int solve(const Scores& sc1, const Scores& sc2) {
    const int len = std::size(sc1);
    return solve2::solve(sc1, sc2, len, len);
  }
} // namespace solve2

int main() {
  int n;
  std::cin >> n;
  auto read_one = [n]() -> vector<Score> {
    string line;
    std::cin.ignore();
    std::getline(std::cin, line);
    vector<Score> res;
    res.reserve(n);
    for (int i = 0, val; i < n; ++i) {
      std::cin >> val;
      bool r = line[i] == 'W';
      res.push_back({r, val});
    }
    return res;
  };
  auto geese = read_one();
  auto hawks = read_one();
  println("{}\n{}", geese, hawks);
  println("{}", solve1::solve(geese, hawks));
  println("{}", solve2::solve(geese, hawks));
}
