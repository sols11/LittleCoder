#include <iostream>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <vector>

using namespace std;

class Solution{
public:
    // https://leetcode-cn.com/problems/reverse-integer/
    int 整数倒置(int x)    {
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
    bool 回文数(int x)    {
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
    int 罗马数字转整数(string s) {
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
    int romanToInt(string s) {
        unordered_map<string, int> m = {{"I", 1}, {"IV", 3}, {"IX", 8}, {"V", 5}, {"X", 10}, {"XL", 30}, {"XC", 80}, {"L", 50}, {"C", 100}, {"CD", 300}, {"CM", 800}, {"D", 500}, {"M", 1000}};
        int r = m[s.substr(0, 1)];
        for(int i=1; i<s.size(); ++i){
            string two = s.substr(i-1, 2);
            string one = s.substr(i, 1);
            r += m[two] ? m[two] : m[one];
        }
        return r;
    }

    // https://leetcode-cn.com/problems/add-binary/
    string 二进制求和(string a, string b) {
        string ret;
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        const size_t n = a.size() > b.size() ? a.size() : b.size();
        int carry = 0;
        for (size_t i = 0; i < n; ++i)
        {
            int ai = i < a.size() ? a[i] - '0' : 0; // 每次判断处理溢出
            int bi = i < b.size() ? b[i] - '0' : 0; // 更经典的办法是把短的算完再算长的
            int val = (ai + bi + carry) % 2;
            carry = (ai + bi + carry) / 2;
            ret.push_back(val+'0');
        }
        if (carry == 1) // 检查最高位
            ret.push_back('1');
        reverse(ret.begin(), ret.end());
        return ret;
    }
    /* ez，即使不用转整数/双指针法，3次reverse+while逐位计算也可
    不愿用reverse的话可以insert往前面插入 ret.insert(ret.begin(), '1') */
    char* addBinary(char* a, char* b) {
        int i = strlen(a);
        int j = strlen(b);
        
        int len = i > j? i: j;
        char* res = (char*)malloc(sizeof(char) * (len + 2));
        res[++len] = 0;
        
        char carry = '0';
        char pa, pb;
        while(len > 1 || carry == '1') {
            pa = i > 0? a[--i]: '0';
            pb = j > 0? b[--j]: '0';
            res[--len] = pa ^ pb ^ carry; // 当前位
            carry = (pa & carry) | (pb & carry) | (pa & pb); //进位
        }
        return res + len;
    }
    // 附一个C语言的双指针+位运算法，不需要reverse，其实更好

    // https://leetcode-cn.com/problems/sqrtx/
    int 实现sqrt(int x) {
        if (x == 1)
            return 1;
        // 二分搜索
        long long l = 0;
        long long r = x;
        long long m;
        long long sum;
        // 精确到int
        while (l+1 < r)
        {
            m = l + (r-l) / 2;
            sum = m * m;
            if (sum < x)
                l = m;
            else if (sum > x)
                r = m;
            else
                return m;
        }
        return l;
    }
    /* 对于一个非负数n，它的平方根不会大于（n/2+1），最容易想到的非暴力算法就是二分 */

    /* 袖珍计算器法：用到一个指数对数计算公式 根号x=e^(0.5*logx)
    from math import e, log
    def mySqrt(self, x):  # python
        if x < 2:            return x
        # 用了log计算，所以复杂度也是O(logn)? 
        left = int(e**(0.5 * log(x))) # e和log相对，0.5指数即根号
        right = left + 1
        return left if right * right > x else right
    */

    /* 牛顿迭代法：公式 Xk+1 = 0.5*(Xk+X/Xk)，性能比二分更好
    def mySqrt(self, x):
        if x < 2:
            return x
        
        x0 = x
        x1 = (x0 + x / x0) / 2
        while abs(x0 - x1) >= 1:  # 渐进到误差小于1时结束迭代
            x0 = x1
            x1 = (x0 + x / x0) / 2        
   
        return int(x1)
    */

    // https://leetcode-cn.com/problems/excel-sheet-column-title/
    string Excel表列名称(int n) {
        string ret;
        while (n>0)
        {
            int divisor = (n-1) / 26;
            int remainder = (n-1) % 26;
            n = divisor;
            char c = 'A' + remainder;
            ret.insert(ret.begin(), c);
        }
        return ret;
    }
    /* 水题，类似进制换算，26进1，但需要注意进位从1开始 没有0，因此需要n-1 */
    
    // https://leetcode-cn.com/problems/excel-sheet-column-title/
    int Excel表列序号(string s) {
        int ret=0;
        for(auto c : s){
            ret = ret * 26 + (c - 'A' + 1);
        }
        return ret;
    }
    /* 水题，26进制转10进制，比上一题还水 */

    // https://leetcode-cn.com/problems/factorial-trailing-zeroes/
    int 阶乘后的零(int n) {
        long long ret=0;
        while (n)
        {
            n /= 5;
            ret += n;
        }
        return ret;
    }
    /* 阶乘尾数零是一道经典题，因为尾数0必然由因子5产生（因子2远比5多），因此要算出所有因子5的数量
    25/125 这些都是会产生多个因子5的，所以循环算出。复杂度O(log5 n) */

    // https://leetcode-cn.com/problems/happy-number/
    int 平方和(int n)
    {
        int sum=0;
        while (n>0)
        {
            sum += pow(n % 10, 2);
            n /= 10;
        }
        return sum;
    }

    bool 快乐数(int n)
    {
        if (n <= 0)
    		return false;
        set<int> hash;
        while (n != 1)
        {
            n = 平方和(n);
            if(hash.find(n) != hash.end())
                return false;
            hash.insert(n);
        }
        return true;
    }
    /* 快乐数就是 无限循环得不到1的数，暴力+set记录 即可，O(logn)
    但也可以用快慢指针法，这题本质是检测链表是否有环。官方题解很精彩，解析了原理 */

    // https://leetcode-cn.com/problems/count-primes/
    bool isPrime(int n)
    {
        for (int i=2; i*i<=n; ++i)
            if (n % i==0)
                return false;
        return true;
    }
    // 判断素数只需要判断[2, sqrt(n)]范围内即可，因为后面的因数和前面的因数是同样的，只是顺序反过来
    int 计数质数(int n)
    {
        int count = 0;
        // 初始默认所有数为质数
        vector<bool> signs(n, true);
        for (int i = 2; i < n; i++) 
        {
            if (signs[i]) 
            {
                count++;
                for (int j = 2*i; j < n; j += i) // 排除i的倍数
                    signs[j] = false;
            }
        }
        return count;
    }
    /* 这题看题解的，用排除法（埃拉托色尼筛选法），逐步构建素数表并计数即可 */

    // https://leetcode-cn.com/problems/power-of-two/
    bool 是不是2的幂(int n)
    {
        if (n<=0)
            return false;
        while (n>1)
        {
            if (n % 2 != 0)
                return false;
            n /= 2;
        }
        return true;
    }
};

// Test Case
int main()
{
    Solution *s = new Solution();
    cout << s->romanToInt("XVI") << endl;
    return 0;
}
