#include <iostream>
#include <math.h>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution{
public:
    // https://leetcode-cn.com/problems/reverse-integer/
    int reverse(int x)    {
        long long ret = 0;
        while (x != 0)
        {
            // 简单的/%计算，能处理负数
            ret = ret * 10 + x % 10;
            x /= 10;
            // 反转溢出返回0
            if (ret < INT_MIN || ret > INT_MAX)
                return 0;
        }
        return (int)ret;
    }
    /* 注意点两个：1.要用long long存，2.要检查32位范围 */

    // https://leetcode-cn.com/problems/palindrome-number/
    bool isPalindrome(int x)    {
        long long res = 0;
        int num = x;
        while (x > 0)
        {
            res = res * 10 + x % 10;
            x /= 10;
        }
        return res == num;
    }
    /* 这题其实是整数反转的变种，需要将数字反转后与原数比较，但因为负数不符合条件
    因此不应参与反转
    还有一种做法是首尾对比，负数直接排除 */

    // https://leetcode-cn.com/problems/roman-to-integer/
    int romanToInt(string s) {
        int sum = 0;
        int pre = convert(s[0]);
        for (int i=1; i<s.length(); ++i)
        {
            int cur = convert(s[i]);
            if (pre < cur)
                sum -= pre;
            else
                sum += pre;
            pre = cur;
        }
        sum += pre;
        return sum;
    }
    /* easyway是用switch，每次操作都基于前一个值，看其是否比后值大来决定+- */
    int convert(char c)
    {
        switch(c)
        {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
            default : return 0;
        }
    }
    /* hardway是基于convert做手脚，查找两个字符，计算两个字符代表的值，这也是符合规则的 */
    int romanToInt2(string s) {
        unordered_map<string, int> m = {{"I", 1}, {"IV", 3}, {"IX", 8}, {"V", 5}, {"X", 10}, {"XL", 30}, {"XC", 80}, {"L", 50}, {"C", 100}, {"CD", 300}, {"CM", 800}, {"D", 500}, {"M", 1000}};
        int r = m[s.substr(0, 1)];
        for(int i=1; i<s.size(); ++i){
            string two = s.substr(i-1, 2);
            string one = s.substr(i, 1);
            r += m[two] ? m[two] : m[one];
        }
        return r;
    }
};

// Test Case
int main()
{
    Solution *s = new Solution();
    cout << s->romanToInt("XVI") << endl;
    return 0;
}
