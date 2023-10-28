#include <string>

class Solution {
public:
    int findTheLongestBalancedSubstring(std::string s) {
        int  counter     = 0;
        int  tmp_counter = 0;
        int  zeros = 0, ones = 0;
        bool flag = false;
        for (std::string::iterator i = s.begin(); i != s.end(); ++i) {
            if (*i == '0' && !flag) {
                tmp_counter++;
                zeros++;
            }
            else if (*i == '1' && !flag) {
                tmp_counter++;
                flag = !flag;
                ones++;
            }
            else if (*i == '1' && flag) {
                tmp_counter++;
                ones++;
            }
            else if (flag && *i == '0') {
                if (ones != zeros) {
                    tmp_counter = ones > zeros ? 2 * zeros : tmp_counter;
                    tmp_counter = zeros > ones ? 2 * ones : tmp_counter;
                }
                counter     = std::max(counter, tmp_counter);
                tmp_counter = 1;
                zeros       = 1;
                ones        = 0;
                flag        = false;
                if (counter >= (s.end() - i)) {
                    break;
                }
            }
        }
        if (ones != zeros) {
            tmp_counter = ones > zeros ? 2 * zeros : tmp_counter;
            tmp_counter = zeros > ones ? 2 * ones : tmp_counter;
        }
        counter = std::max(counter, tmp_counter);
        return counter;
    }
};
