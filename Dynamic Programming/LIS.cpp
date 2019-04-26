/*Longest Increasing Subsequence*/
#include <bits/stdc++.h>
using namespace std;

int lengthOfLIS(vector<int>& nums) {
        int size = nums.size();
        if(size == 0) return 0;
        vector<int> lis(size, 1);
        for(int i=1; i<size; i++){
            for(int j=0; j<i; j++){
                if(nums[j]<nums[i] && lis[i] < lis[j]+1){
                    lis[i] = lis[j]+1;
                }
            }
        }
        return *max_element(lis.begin(), lis.end());
}
