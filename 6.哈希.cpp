#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

// https://leetcode-cn.com/problems/two-sum/
vector<int> twoSum(vector<int>& nums, int target) {
	unordered_map<int, int> hash;
	vector<int> ret;
    for (int i=0; i<nums.size(); ++i)
    {
        int findNum = target - nums[i];
        if (hash.find(findNum) != hash.end())
        {
            ret.push_back(hash[findNum]);
            ret.push_back(i);
            return ret;
        }
		hash[nums[i]] = i;  // 一边find前者一边加入hash
    }
    return ret;
}
/* 简单的hash题，查找hash[target-nums[i]]即可 */