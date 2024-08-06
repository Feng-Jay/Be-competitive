# 双指针

## [167. 两数之和 II - 输入有序数组](https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/description/)


今天竟然写了道超越100%的时间效率算法，记录一下。

这道题思路很简单，由于数组本身已经有序，那么可以用双指针的方式来遍历该数组，但使用双指针的方式也有不同。

我刚开始是设计了一个同向的双指针

```C++
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int i=0, j = 1;
        int sum = 0;
        int len = numbers.size();
        while(i < len - 1){
            sum = numbers[i] + numbers[j];
            if (sum == target){
                return vector<int>{i+1, j+1};
            }else if(sum < target){
                int tmp = numbers[j++];
                while(j < len && numbers[j] == tmp)
                    j++;
            }
            if (sum > target || j >= len){
                int tmp = numbers[i++];
                while(i < len -1 && numbers[i] == tmp)
                    i++;
                j = i + 1;
            }
        }
        return vector<int>{0,0};
    }
};
```

i和j都往前走，不过j快一步但这个算法在没有优化的时候在一些case上会超时。于是我加了两个while循环来排除掉那些重复数字的情况，即如果指针移动后仍指向和计算sum时同样的数字，那么继续移动指针。

但这个方法其实不是最优的，因为j在向前遍历时其实已经知道了一些数字的值，所以x其实可以略过一些值。但这个逻辑比较复杂，与之思路类似的方式是，设计两个反方向指针：

```C++
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int len = numbers.size();
        int i = 0, j = len - 1;
        int sum = 0;
        while(i < j){
            sum = numbers[i] + numbers[j];
            if (sum == target) return vector<int>{i + 1, j + 1};
            else if(sum < target){
                int tmp = numbers[i++];
                while(numbers[i] == tmp) i++;
            }
            else if(sum > target) {
                int tmp = numbers[j--];
                while(numbers[j] == tmp) j--;
            }
        }
        return {-1, -1};
    }
};
```

由于已经有序了，那么ij分别位于头和尾，如果此时sum < target, 那么i一定向前移动；如果sum > target, j一定向后移动。这样最终可以得到结果。另外我也加上了对重复数字的优化，这样这个solution可以做到时间效率上击败100%的solutions。

## [88. 合并两个有序数组](https://leetcode.cn/problems/merge-sorted-array/description/)

这道题如果不关心空间复杂度的话其实很简单，直接开辟一个m + n 大小的新数组然后普通的归并排序即可；这里介绍一个空间复杂度为O(1)的方法:

```C++
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int ptr1 = m - 1;
        int ptr2 = n - 1;
        int res_ptr = m + n - 1;
        while(ptr1 >= 0 && ptr2 >= 0 ){
            if (nums1[ptr1] >= nums2[ptr2]){
                nums1[res_ptr] = nums1[ptr1];
                ptr1--;
            }else{
                nums1[res_ptr] = nums2[ptr2];
                ptr2--;
            }
            res_ptr--;
        }
        while(ptr1 >= 0){
            nums1[res_ptr] = nums1[ptr1];
            ptr1--;
            res_ptr--;
        }
        while(ptr2 >= 0){
            nums1[res_ptr] = nums2[ptr2];
            ptr2--;
            res_ptr--;
        }
        // return nums1;
    }
};
```

整体框架和归并排序还是一样的，不同点在于是从大的数值开始排序，这样nums1中的数字如果需要排在数组尾部的话虽然占用了一个空间，但又将原本占据的那个空间释放出来了，所以该空间一定是够nums1和nums2使用的。