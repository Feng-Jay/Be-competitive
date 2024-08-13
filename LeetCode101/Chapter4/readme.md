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


## [34. 在排序数组中查找元素的第一个和最后一个位置](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/description/)


```C++
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int len = nums.size();
        if (len == 0) return {-1, -1};

        int begin_idx = -1;
        int end_idx = -1;
        // search for the lower bound
        int l = 0, r = len - 1;
        int middle = 0;
        while(l <= r){
           middle =  (r - l) / 2 + l;
           if(nums[middle] >= target){
            r = middle - 1;
           }
           else{
            l = middle + 1;
           }
        }
        begin_idx = l;
        if (begin_idx == len || nums[begin_idx] != target) return {-1, -1};
        // find upper bound
        middle = 0;
        l = 0; r = len - 1;
        while(l <= r){
           middle =  (r - l) / 2 + l;
           if(nums[middle] <= target){
            l = middle + 1;
           }
           else{
            r = middle - 1;
           }
        }
        end_idx = l - 1;
        return {begin_idx, end_idx};
    }
};
```
这道题可以看做是通过二分查找来判断数字所在的上界和下界，上界和下界影响着二分算法中的逻辑实现:

求下界时:
```C++
if (nums[middle] >= target) r = middle - 1;
else l = middle + 1;
```

求上界时:

```C++
if(nums[middle] <= target) l = middle + 1;
else r = middle -1;
```
可以看到求下界时r的值是尽量小的，即使 nums[middle] == target 也会下降；求上界时l的值尽可能大，即nums[middle] == target时l也会尝试上升。

我们可以根据二分结束的状态来对begin_idx和end_idx进行赋值:

下界结束时一定是 l > r, 由于 l == r时如果nums[middle] == target, r --导致该条件，则l就应该是target的位置。然后加以判断，如果l不是target或者l已经到达了数组长，那么就不存在该target。

上界结束时也是 l > r, 由于 l == r时如果nums[middle] == target, l += 1导致该条件，则l-1(或者r)就应该是target位置。


## [33. 搜索旋转排序数组](https://leetcode.cn/problems/search-in-rotated-sorted-array/description/)

```C++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int len = nums.size();
        int l = 0;
        int r = len - 1;
        int middle = 0;
        while(l <= r){
            middle = (r - l) / 2 + l;
            if (nums[middle] == target) return middle;
            if (nums[middle] >= nums[0]){
                // 0~middle 无旋转
                if(nums[middle] > target && nums[0] > target){
                    l = middle + 1;
                }else if(nums[middle] > target && nums[0] <= target){
                    r = middle - 1;
                }else if(nums[middle] < target){
                    l = middle + 1;
                }
            }
            if (nums[middle] < nums[0]){
                // 0~middle有旋转
                if(nums[middle] > target){
                    r = middle - 1;
                }else if(nums[middle] < target && nums[0] <= target){
                    r = middle - 1;
                }else if(nums[middle] < target && nums[0] > target){
                    l = middle + 1;
                }
            }
        }
        return -1;
    }
};
```
这道题是更复杂的二分算法，需要判断数组哪一部分是有序和无序的，整体逻辑比较简单


## [81. 搜索旋转排序数组 II](https://leetcode.cn/problems/search-in-rotated-sorted-array-ii/description/)

这道题虽然只是在数组中可能存在一些重复元素，但写起来感觉比上一道感觉难了很多，有很多corner case要考虑

```C++
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int len = nums.size();
        if (len == 1) return nums[0] == target;
        int l = 0;
        int r = len - 1;
        int middle = 0;
        while(l <= r){
            middle = (r - l) / 2 + l;
            if (nums[middle] == target) return true;
            if (nums[middle] == nums[l] && nums[middle] == nums[r]){
                l++;
                r--;
            }
            else if (nums[middle] >= nums[l]){
                // l~middle 无旋转
                if(nums[middle] > target && nums[l] > target){
                    l = middle + 1;
                }else if(nums[middle] > target && nums[l] <= target){
                    r = middle - 1;
                }else if(nums[middle] < target){
                    l = middle + 1;
                }
            }
            else if (nums[middle] < nums[l]){
                // l~middle有旋转
                if(nums[middle] > target){
                    r = middle - 1;
                }else if(nums[middle] < target && nums[l] <= target){
                    r = middle - 1;
                }else if(nums[middle] < target && nums[l] > target){
                    l = middle + 1;
                }
            }
        }
        return false;
    }
};
```

如果存在 nums[l] == nums[middle] == nums[r], 那么我们在不遍历数组的情况下是无法判断有序性的，因此此时只能去l++;r--来约束空间。

当上述条件不满足时，即三者不等时，如果有nums[l] <= nums[middle], 那么就说明l ~ middle 有序的；如果有 nums[l] > nums[middle], 那么就说明他们之间有翻转，具体的二分赋值依旧按之前的逻辑就好了。