# 二分查找

## [69. x 的平方根](https://leetcode.cn/problems/sqrtx/description/)

这道题是一个加强对二分查找模板理解的题目，我的解法是这样的:

```C++
class Solution {
public:
    int mySqrt(int x) {
        if (x == 1 || x == 0) return x;
        int left = 1;
        int right = x;
        long middle = 0;
        while(left <= right){
            middle = (right - left) / 2 + left;
            if (middle * middle == x) return middle;
            if (middle * middle < x){
                left = middle + 1;
            }
            if (middle * middle > x){
                right = middle - 1;
            }
        }
        return left - 1;
        
    }
};
```

至于对于二分查找的边界条件可以这样判断，当出循环时，一定是 left > right, 原因无非两种: 1. middle * middle < x, left = middle + 1 > right, 所以此前的left就应该是平方根的值，ans = left - 1;

2. middle * middle > x, right = middle - 1, 说明此前left == right == middle, 且(left - 1) * (left - 1) 一定是小于x的，因为left一定是由一个middle*middle < x 的middle + 1得来的，因此ans = left - 1

可以通过对跳出循环的条件来对二分查找的各个部分进行检查！