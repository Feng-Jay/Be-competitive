# 贪心算法

## [455.分发饼干](https://leetcode.cn/problems/assign-cookies/description/)

```C++
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int child_ptr = 0;
        int res = 0;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] >= g[child_ptr]){
                child_ptr += 1;
                res += 1;
            }
            if(child_ptr == g.size()) break;
        }
        return res;
    }
};
```
经典的贪心算法题目, 将饼干和胃口排序后，按大小将饼干给孩子，背后的思想是这样的:

1. 若饼干可以分给孩子，那么一定是最优分配，当前饼干是所有可用饼干中最小的。

2. 若饼干不能分配给当前孩子，那么一定也分配不给后面的孩子(已经排序)，将该饼干“丢掉”

## [135.分发糖果](https://leetcode.cn/problems/candy/description/)

```C++
class Solution {
public:
    int candy(vector<int>& ratings) {
        int len = ratings.size();
        vector<int> candies(len, 1);
        // 保证对于i [1, len), i 和 i - 1保证题设关系
        for (int i = 1; i < len; ++i){
            if(ratings[i] > ratings[i - 1]){
                candies[i] = candies[i - 1] + 1;
            }
        }
        // 保证对于i [0, len-1), i 和 i + 1保证题设关系
        for (int i = len-2; i >= 0; --i){
            if(ratings[i] > ratings[i + 1] && candies[i] <= candies[i + 1]){
                candies[i] = candies[i + 1] + 1;
            }
        }
        // for (int i = 0; i < len; ++i) cout << candies[i] << " ";
        return accumulate(candies.begin(), candies.end(), 0);
    }
};
```

可以将`相邻两个孩子评分更高的孩子获得更多糖果`分解成两部分, 对于孩子i:

1. 如果 ratings[i] > ratings[i-1] 要满足: candies[i] > candies[i-1]

2. 如果 ratings[i] > ratings[i+1] 要满足: candies[i] > candies[i+1]

首先从左至右遍历ratings数组可以确保满足条件1. 再从右向左遍历ratings数组可以确保满足条件2.

问题是在满足2的时候条件1会被破坏吗:

条件1被破坏 <==> 条件1首先成立, 第二次遍历后不成立 <==> ratings[i] > ratings[i-1], candies[i] <= candies[i-1]

由于candies数组只会增加不会减少，那么是candies[i-1]增大，但已经有ratings[i-1] < ratings[i], 所以在第二次遍历时不会将candies[i-1]提升，因此此时两个条件都满足。


## [435.无重叠区间](https://leetcode.cn/problems/non-overlapping-intervals/description/)

```C++
class Solution {
public:
    static bool compare(vector<int> a, vector<int> b){
        // enda < endb
        // if (a[1] != b[1]){
           return a[1] < b[1]; 
        // }
    }
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        int len = intervals.size();
        sort(intervals.begin(), intervals.end(), [](const auto&a, const auto&b){
            return a[1] < b[1]; 
        });
        int end = intervals[0][1];
        int res = 0;
        for(int i = 1; i < len; ++i){
            if(end > intervals[i][0]){
                res += 1;
            }else{
                end = intervals[i][1];
            }
        }
        return res;
    }
};
```

## [605.种花问题](https://leetcode.cn/problems/can-place-flowers/description/)

```C++
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        //总共可以分为三种类型的花坛
        //左边界到花: 如果有n个空格，可以种n/2朵花
        //花到右边界: 如果有n个空格，可以种n/2 朵花 
        //在两个花之间: 如果有n个空格，可以种n/2朵花
        int len = flowerbed.size();
        int prev = -1;
        int res = 0;
        for (int i = 0; i < len; ++i){
            if (flowerbed[i] == 1){
                if(prev < 0){
                    res += i/2;
                }else{
                    res += (i - prev - 2) / 2;
                }
                prev = i;
            }
        }
        //特殊情况，全空
        if (prev < 0){
            res += (len + 1)/ 2;
        }else{
            res += (len - prev - 1) / 2;
        }
        return res >= n;
    }
};
```
