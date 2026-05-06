
//example of a lower case question but the condition of truth should lie on right side

class Solution {
public:
    int findMin(vector<int>& nums) {

        // lower bound
        int l = 0, r = nums.size()- 1; //because it can never be a value equal to nums size
        while (l < r) {
            int mid = (l + r) >> 1;
            if (nums[mid] > nums[r]) {
                // ans should lie on right side
                l = mid + 1;
            } else {
                r = mid;
            }
        }

        return nums[l];

    }
};