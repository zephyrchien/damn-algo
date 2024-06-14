#include "common.h"

int solve(vector<int>& nums) {
  std::sort(nums.begin(), nums.end());
  int cnt = 0;
  int n = 0;
  for (const int num : nums) {
    if (num >= n) {
      n = num + 1;
      continue;
    }
    cnt += (n++ - num);
  }
  return cnt;
}

int solve2(vector<int>& nums) {
  map<int, int> map;
  for (int num : nums) { map[num]++; }
  int ans = 0;
  int n = 0;
  for (const auto& [num, cnt] : map) {
    ans += cnt * (cnt - 1) / 2 + cnt * std::max(n - num, 0);
    n = std::max(n, num) + cnt;
  }
  return ans;
}

int main() {
  vector<int> input[] = {{0}, {1, 2, 2}, {3, 2, 1, 2, 1, 7}};
  for (auto in : input) { println("{}", solve(in)); }
  println("---");
  for (auto in : input) { println("{}", solve2(in)); }
}
