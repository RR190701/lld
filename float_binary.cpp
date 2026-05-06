class Solution {

    bool isEqual(vector<int>& buckets, double target, int loss) {

        // remove water from the over fikled buckets with calculating loss
        double netWater = 0;

        for (auto x : buckets) {
            if (x > target)
                netWater += ((x - target) * (100.0 - loss)) / 100.0;
            else
                netWater -= target - x;
        }

        return netWater >= 0;
    }

public:
    double equalizeWater(vector<int>& buckets, int loss) {

    int ans = 0;
        // lower bond question

        int maxV = *max_element(buckets.begin(), buckets.end());

        double l = 0, r = maxV;

        while (1e-6 < r - l) {

            double mid = l + (r -l)/2;

            if (isEqual(buckets, mid,loss))
            
                l = mid; //no int addition that leads to a huge error because it misses the 
            else
                r = mid;
        }

        return l;
    }
};