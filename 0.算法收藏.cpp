#include <iostream>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <vector>

using namespace std;

class Solution {
public:
    /* 收藏一些我喜欢的算法，未必会是常用算法 */
    int BinarySearch(vector<int>& nums, int target) {
        int l=0, r=nums.size()-1;
        while (l <= r) { 
            int m = l + (r - l) / 2; 
    
            if (nums[m] < target) 
                l = m+1; 
            else if (nums[m] > target) 
                r = m-1; 
            else
                return m; 
        } 
        return l; 
    }
};