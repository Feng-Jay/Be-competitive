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

该题的贪心思路很直观: 在所有备选的区间中，右区间最小的那个一定是让区间数最大的区间中的一个。然后该问题的规模就从n变成n - 1, 以此类推, 当对数组根据右区间大小进行排序后，每次都选择右区间最小且与前一个区间不重叠的即可解决该问题。

我在写这道题的时候遇到了一个有意思的点：当sort中定义的比较函数定义成为类成员时效率很低，排在5%, 但如果写成匿名的函数，效率可以到95%。

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

这道题相比贪心，感觉更像一个简单的模拟题。可以将n个空格分为三类：

1. [左临界, 花]，那么可以用来种花的空格有 n - 1个，可以种 (n - 1 + 1)/2 朵花

2. [花, 花]，那么可以用来种花的空格有 n -2个，可以种 (n - 2 + 1 )/2 朵花

3. [花, 右临界]，那么可以用来种花的空格有 n - 1个，可以种 (n - 1 + 1)/2 朵花

特殊情况，如果花坛没有花，那么所有len个空格都可以用来种花，可以种 (len + 1)/2 朵花


## [452. 用最少数量的箭引爆气球](https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/description/)

```C++
class Solution {
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int len = points.size();
        if (len == 1) return 1;
        sort(points.begin(), points.end(), [](const vector<int>&a, const vector<int>&b){
            return a[1] < b[1];
        });
        int right = points[0][1];
        int res = 1;
        for(int i = 1; i < len; ++i){
            if (points[i][0] <= right){
                continue;
            }else{
                res += 1;
                right = points[i][1];
            }
        }
        return res;
    }
};
```

这道题的贪心思路也很简单: 尽量一支箭射穿尽可能多的气球。因此，对气球的右端点进行排序，由于尽可能射的多，所以极限是当前气球的右端点。如果下一个气球和当前气球有重叠，那么不需要额外射箭。如果没有重叠，那么当前箭射出，该气球为剩下的第一个气球。

## [763. 划分字母区间](https://leetcode.cn/problems/partition-labels/description/)

```C++
class Solution {
public:
    vector<int> partitionLabels(string s) {
        int endIndexes[26];
        int len = s.size();
        for(int i = 0; i < len; ++i){
            endIndexes[s[i] - 'a'] = i;
        }
        int start = 0;
        int end = 0;
        vector<int> res;
        for(int i = 0; i < len; ++i){
            end = max(end, endIndexes[s[i] - 'a']);
            if (i == end){
                res.push_back(end - start + 1);
                start = end + 1;
            }
        }
        return res;
    }
};
```

这道题的难点是如何想到将字符串处理得到每个字母的开始和结束下标这样的特征。这提示我们可以对数据进行一些特征抽取后应用算法。

一旦得到每个char的结束下标，那么即可开始遍历，每遇到一个char，那么当前字符串结束下标都不会小于该char的end下标。 即 end = max(end, endIndexes[c])

一旦发现当前index等于当前字符串的end，那么即可将当前子串分离出来，记录长度为 endIndex - beginIndex + 1. 下一个字符串的开始下标为endIndex + 1


## [122. 买卖股票的最佳时机 II](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/description/)

```C++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len = prices.size();
        if (len == 1) return 0;
        int res = 0;
        for (int i = 0; i < len - 1; ++i){
            if(prices[i] < prices[i + 1]){
               res += prices[i + 1] - prices[i]; 
            }
        }
        return res;
    }
};
```

由于可以当天买卖，且每天都可以进行买卖，那么贪心策略就是：只要明天价格比今天高，那就今天买入，明天卖出。等到明天后依旧执行该策略，如果下一天价格更高，那就今天卖出后再买入，下一天卖掉，以此类推。


## [406.根据身高重建队列](https://leetcode.cn/problems/queue-reconstruction-by-height/description/)

这道题有两种思路，分别是从低到高和从高到低考虑排序:

1. 由低到高

根据题意我们可以知道，当身高相同时，ki值更高的人会排在ki较低的人的后面，因此可以视作ki更高的人身高其实略低一个delta。这步在实现的时候有一个trick，即可以将hi作为第一个key升序排序，ki作为第二个key降序排序。

接下来就是缩小问题的求解空间：对排完序的数组，第一个没有被排序的人永远是所有人中身高最低的(相同身高考虑delta)，那么这个人的位置一定是固定的，即他前面有ki个空位用于比他更高的人(也就是剩下人中的ki个，因为都比他高)，位置是第ki+1个空位。当最低的人位置确定后，问题空间即可缩小，剩下的n-1个人中仍有一个最低的人，重复上述过程直到所有人都有位置。

```C++
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        int len = people.size();
        if (len == 1) return people;
        sort(people.begin(), people.end(), [](const vector<int>& a, const vector<int>& b){
            return a[0] == b[0] ? a[1] > b[1] : a[0] < b[0];
        });
        vector<vector<int>> res(len);
        for(int i = 0; i < len; ++i){
            int spaces = people[i][1] + 1;
            for(int j = 0; j < len; ++j){
                if(res[j].empty()){
                    spaces--;
                    if(spaces == 0){
                        res[j] = people[i];
                        break;
                    }
                }
            }
        }
        return res;
    }
};
```

2. 由高到低

我们仍然可以采用第一种思路的假设：当hi相同时，ki越大可以视为身高越低。不过此时我们需要对hi进行逆序排序，hi进行顺序排序来保证身高更"高"的人排在数组前面。当身高最高的人站好后，后面来的人身高一定比他低，如果这个人的ki > 0，那么在数组的第ki位置插入这个人即可(此时排序一定会让hi更高，ki更低的人往前排，所以该插入一定是合法的, 即数组中至少已经有了ki个人); 如果ki==0，将其插在数组刚开始即可。对数组中每个人都采用上述策略，即可恢复序列。


```C++
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // 其实个身高组里面是有序的，组间顺序需要恢复
        int len = people.size();
        if (len == 1) return people;
        sort(people.begin(), people.end(), [](const vector<int> & a, const vector<int> & b){
            return a[0] == b[0] ? a[1] < b[1] : a[0] > b[0];
        });
        // for(int i =0; i < len; ++i) cout<<people[i][0] << " " << people[i][1];
        vector<vector<int>> res;
        res.push_back(people[0]);
        for(int i = 1; i < len; ++i){
            int len2 = res.size();
            int counter = 0;
            int j = 0;
            for(; j < len2; ++j){
                if(res[j][0] >= people[i][0]){
                    counter ++;
                }
                if(counter > people[i][1]){
                    res.insert(res.begin() + j, people[i]);
                    break;
                }
                if(counter == people[i][1]){
                    res.insert(res.begin() + j + 1, people[i]);
                    break;
                }
            }
            if (j == len2){
                res.push_back(people[i]);
            }
            
        }
        return res;
    }
```
我的这版实现其实不太优雅，可以看到后面3个if判断是没有什么必要的

```C++
if(counter > people[i][1]){
    // 这个if单独处理 people[i][1] == 0的情况，因此 j == 0
    res.insert(res.begin() + j, people[i]);
    break;
}
if(counter == people[i][1]){
    // 这个insert其实可以简化为 res.insert(res.begin() + people[i][1] + 1, people[i]), +1是因为我手动将第一个人加进去了。
    res.insert(res.begin() + j + 1, people[i]);
    break;
}
if (j == len2){
    // 如果ki还没达到，那就插入最后，其实没必要，因为在之前的分析中可得到插入的位置是一定存在的，也可以用insert表示: res.insert(res.begin() + j, people[i]);
    res.push_back(people[i]);
}
```

看了官方题解的答案是这样:

```C++
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        int len = people.size();
        if (len == 1) return people;
        sort(people.begin(), people.end(), [](const vector<int> & a, const vector<int> & b){
            return a[0] == b[0] ? a[1] < b[1] : a[0] > b[0];
        });
        vector<vector<int>> res;
        //官方题解
        for (const vector<int> & person: people){
            res.insert(res.begin() + person[1], person);
        }
        return res;
    }
}
```

比我的优雅多了..., 记住一个用法 `vector:insert(vec.begin()+i,a), 在第i+1个元素前插入a`

Okay! 第一章的贪心算法就到这里了，其实总结一下核心思想就是，通过选择数据中最具代表性的一个数据一步步减小问题空间，进而解决问题，有点dp的意思。