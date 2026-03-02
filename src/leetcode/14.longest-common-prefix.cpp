/*
 * @lc app=leetcode id=14 lang=cpp
 *
 * [14] Longest Common Prefix
 */

#include <string>
#include <vector>

using namespace std;

// @lc code=start
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string out;
        for(auto i = 0; i < numeric_limits<size_t>::max(); i++) {
            int ch = -1;
            for(const auto& s: strs) {
                if(s.size() <= i) { ch = -1; break; }
                if(ch == -1) { ch = s[i]; continue; }
                if(s[i] != ch) { ch = -1; break; }
            }
            if(ch == -1) break;
            out.push_back(char(ch));
        }
        return out;
    }
};
// @lc code=end

