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