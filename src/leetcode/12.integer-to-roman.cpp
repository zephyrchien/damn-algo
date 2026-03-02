/*
 * @lc app=leetcode id=12 lang=cpp
 *
 * [12] Integer to Roman
 */

#include <string>
#include <string_view>
#include <unordered_map>

using namespace std;

// @lc code=start
class Solution {
public:
    inline const static pair<int, string_view> tbl[] = {
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"},
        {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
        {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}
    };
    string intToRoman(int num) {
        string out;
        for(const auto [n, str]: tbl) {
            if(num < n) continue;
            int c = num / n;
            for(int i = 0; i < c; i++) {
                out.append(str);
            }
            num -= c * n;
        }
        return out;
    }
};
// @lc code=end

