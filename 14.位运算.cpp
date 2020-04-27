#include <iostream>
#include <math.h>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    // https://www.lintcode.com/zh-cn/problem/a-b-problem/
    int aplusb(int a, int b)
    {
        while (b != 0)
        {
            int tmpa = a ^ b;        // 得到最后一位的结果。异或相当于相加但没考虑进位
            int tmpb = (a & b) << 1; // 得到A+B进位的结果并左移到上一位
            a = tmpa;                // 替换ab继续循环直到b=0即没有进位
            b = tmpb;
        }
        return a; // a已经是和值了
    }
    /* a+b位运算实现，需要异或（不进位值）和与（进位值）运算
    加法原理（如101+111）:不进位,进位分开算,循环直到不需进位 */
};