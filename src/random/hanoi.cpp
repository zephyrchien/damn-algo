#include "common.h"

using Tower = deque<int>;

void show(Tower& a, Tower& b, Tower& c) {
  println("a: {}", a);
  println("b: {}", b);
  println("c: {}", c);
  println("---");
}

void move1(Tower& src, Tower& dst) {
  auto val = src.back();
  src.pop_back();
  dst.push_back(val);
}

void solve(Tower& a, Tower& b, Tower& c) {
  if (a.size() == 1) {
    move1(a, b);
    return;
  }
  auto fin = a.front();
  a.pop_front();
  solve(a, c, b);
  b.push_back(fin);
  solve(c, b, a);
  show(a, b, c);
}

void solve2(Tower& a, Tower& b, Tower& c) {
   
}

int main() {
  Tower x = {4, 3, 2, 1};
  Tower a = x;
  Tower b = {}, c = {};
  solve(a, b, c);
  assert(b == x);
}
