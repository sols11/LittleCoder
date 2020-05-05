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
            int cBit = a ^ b;        // 得到最后一位的结果。异或相当于相加但没考虑进位
            int pBit = (a & b) << 1; // 得到A+B进位的结果并左移到上一位
            a = cBit;                // 替换ab继续循环直到b=0即没有进位
            b = pBit;
        }
        return a; // a已经是和值了
    }
    /* a+b位运算实现，需要异或（不进位值）和与（进位值）运算分开计算，每次处理最终位
    示例:101+111, cBit=010 pBit=1110 得0进位1, cBit=1100 pBit=100 得0进位1...
    下次得1进位1，最后得1进位0，和值a=1100 */

    
};