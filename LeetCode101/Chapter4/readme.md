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


## [154. 寻找旋转排序数组中的最小值 II](https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array-ii/description/)

```C++
class Solution {
public:
    int findMin(vector<int>& nums) {
        int len = nums.size();
        if (len == 1) return nums[0];
        int l = 0;
        int r = len - 1;
        int middle = 0;
        int res = 500000;
        while(l <= r){
            middle = (r - l) / 2 + l;
            res = min(res, nums[middle]);
            if(nums[middle] == nums[l] && nums[middle] == nums[r]){
                r--;
                l++;
            }else if(nums[middle] < nums[l]){
                //l ~ middle有旋转
                r = middle - 1;
            }else if(nums[middle] >= nums[l]){
                // l~middle 无旋转
                if(nums[middle] <= nums[r]){
                    // l~r无旋转
                    r = middle - 1;
                }else{
                    l = middle + 1;
                }
            }
        }
        return res;
    }
};
```
这道题其实就是上一道题的另一个版本，n次旋转就是在位置n进行一次旋转。具体的思路也是通过判断middle和l大小来判断是否存在旋转来变化l和r的值。

## [540. 有序数组中的单一元素](https://leetcode.cn/problems/single-element-in-a-sorted-array/description/)


```C++
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int len = nums.size();
        if (len == 1) return nums[0];
        int l = 0;
        int r = len - 1;
        int middle = 0;
        while(l <= r){
            middle = (r - l) / 2 + l;
            if (l == r) return nums[l];
            if (middle % 2 == 0){
                if (nums[middle + 1] == nums[middle]) l = middle + 2;
                else r = middle;
            }
            if (middle % 2 == 1){
                if (nums[middle -1] == nums[middle]) l = middle + 1;
                else r = middle;
            }
        }
        return -1;
    }
};
```

假设单一位置下标为x，那么x左侧，若有偶数下标y，一定有 nums[y] == nums[y+1]; 在x右侧，若有奇数下标y，一定有nums[y-1] == nums[y]. 可以根据判断middle是否满足这两个条件，如果满足则当前middle一定在x左侧，调整l的大小。否则说明middle在右侧，调整r的大小即可。


## [4. 寻找两个正序数组的中位数](https://leetcode.cn/problems/median-of-two-sorted-arrays/description/)

这道题有点难，我之前的搜索条件一直是ptr1, ptr2之前的数字之和为中位数前应该有的数字数量，但发现这个假设其实局限在了偶数长度中位数必须存在在nums1和nums2中各一个，后面看到了题解，发现可以通过求前k个数来找到中位数，先放题解:

```C++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size();
        int len2 = nums2.size();
        int left = (len1 + len2 + 1) / 2;
        int right = (len1 + len2 + 2) / 2;
        // solution#1
        // return (getKth(nums1, 0, len1 - 1, nums2, 0, len2 - 1, left) +getKth(nums1, 0, len1 - 1, nums2, 0, len2 - 1, right)) * 1.0 / 2;
        
        // solution#2
        if ((len1 + len2) % 2 == 1) return getKth(nums1, nums2, (len1 + len2 + 1) / 2);
        else return (getKth(nums1, nums2, (len1 + len2)/2 ) + getKth(nums1, nums2, (len1 + len2)/2 + 1)) * 1.0 / 2;
    }
    int getKth(vector<int>& nums1, int start1, int end1, vector<int>& nums2, int start2, int end2, int k){
        int len1 = end1 - start1 + 1;
        int len2 = end2 - start2 + 1;
        if (len1 > len2) return getKth(nums2, start2, end2, nums1, start1, end1, k);

        if (len1 == 0) return nums2[start2 + k - 1];
        if (k == 1) return min(nums1[start1], nums2[start2]);

        int idx_i = start1 + min(len1, k/2) - 1;
        int idx_j = start2 + min(len2, k/2) - 1;

        if(nums1[idx_i] >= nums2[idx_j]){
            return getKth(nums1, start1, end1, nums2, idx_j + 1, end2, k - (idx_j - start2 + 1));
        }else{
            return getKth(nums1, idx_i + 1, end1, nums2, start2, end2, k - (idx_i - start1 + 1));
        }
    }

    int getKth(vector<int>& nums1, vector<int>& nums2, int k){
        int len1 = nums1.size();
        int len2 = nums2.size();
        int index1 = 0, index2 = 0;
        while(true){
            if (index1 == len1) return nums2[index2 + k - 1];
            if (index2 == len2) return nums1[index1 + k - 1];
            if (k == 1) return min(nums1[index1], nums2[index2]);

            int newIndex1 = min(len1 - 1, index1 + k / 2 - 1);
            int newIndex2 = min(len2 - 1, index2 + k / 2 - 1);

            if (nums1[newIndex1] > nums2[newIndex2]){
                k -= newIndex2 - index2 + 1;
                index2 = newIndex2 + 1;
            }else{
                k -= newIndex1 - index1 + 1;
                index1 = newIndex1 + 1;
            }
        }
    }
    
};
```

第二个solution更好懂，我就按第二个代码捋一下思路: 每次循环都看数组从index1/2开始的第k/2 - 1个数字的值，其中较小的那个值及之前的一定不是第k小的数字, 然后调整k值和对应下标，直到nums1走到尽头，那么直接nums2取index2 + k -1即可。另一种情况也一样的操作。如果k==1，那么就说明要找当前子数组最小的数，就返回nums1[index1]和nums2[index2]中最小的那个即可。solution1其实是solution2的递归版本.