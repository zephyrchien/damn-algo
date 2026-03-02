/*
 * @lc app=leetcode id=13 lang=cpp
 *
 * [13] Roman to Integer
 */
#include <string>
#include <array>
#include <unordered_map>
#include <iostream>

using namespace std;
// @lc code=start
class Solution {
public:
    inline static unordered_map<int, int> tbl = {
        {'I', 1}, {'V', 5}, {'X', 10},
        {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}
    };
    int romanToInt(string s) {
        const int len = std::size(s); 
        int idx = 0, out = 0;
        while(idx < len) {
            int cur = tbl[s[idx]];
            if(idx+1 < len) {
                int next = tbl[s[idx+1]];
                if(next > cur) {
                    out += (next - cur);
                    idx += 2;
                    continue;
                }
            }
            out += cur; idx++;
        }
        return out;
    }
};
// @lc code=end

