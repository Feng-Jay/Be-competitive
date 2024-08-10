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


## [142. 环形链表 II](https://leetcode.cn/problems/linked-list-cycle-ii/description/)

这道题很直观的解法就是一直遍历该链表，并记录下来每次遍历的节点，第一个重复的节点就是环的开头:

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_set<ListNode*> res;
        while(head != nullptr){
            if(res.count(head)){
                return head;
            }
            res.insert(head);
            head = head->next;
        }
        return nullptr;
    }
};
```

但看题解还有另一种快慢指针的方法，该方法用了叫做Floyd判环法的算法，[link](https://blog.csdn.net/weixin_45609535/article/details/125708493)有详细的解释:

总结一下就是，slow指针每次走一步，fast每次走两步。设环外长度为a, 环长为L。

如果有环，那么slow和fast一定会相遇: 设此时相遇时已经在环的b长度处，还有L-b = c长度就又到环的起点。且当这次相遇时，slow一定不会在环中走过一圈: 假设最差情况，slow刚到环起点，fast到环起点下一个点，此问题就变成了fast追slow，最多花费L-1时间就可以追到, 可得所需要追到的距离为 L - b。所以当相遇时有下列等式: 

```text
DisSlow = a + (L - b)
DisFast = a + L * N + (L - b)
DisFast = 2 * DistSlow
```

可以得到: (L - b) + a= L * N; 且由前述可得此时交点位于 L - b, 所以再走a步就可以走完这圈，因此将一个指针放在head走，一个放在环中走，相遇时的点即为环起点。

```C++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;
        do{
            if(fast == nullptr || fast->next == nullptr) return nullptr;
            fast = fast->next->next;
            slow = slow->next;
        } while(fast != slow);
        fast = head;
        while(fast != slow){
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};
```

## [76. 最小覆盖子串](https://leetcode.cn/problems/minimum-window-substring/description/)

```C++
class Solution {
public:
    string minWindow(string s, string t) {
        map<char, int> token_amount;
        set<char> token_in;
        for(int i = 0; i < t.size(); ++i){
            if (token_amount.contains(t[i])){
                token_amount[t[i]] += 1;
            }else{
                token_amount[t[i]] = 1;
            }
            token_in.insert(t[i]);
        }

        int l =0, r;
        int counter = 0;
        int min_size = s.size() + 1;
        int min_l = 0;
        for(r = 0; r < s.size(); ++r){
            if(token_in.contains(s[r])){
                if(--token_amount[s[r]] >= 0){
                    counter += 1;
                }
                while(counter == t.size()){
                    if (r - l + 1 < min_size){
                        min_l = l;
                        min_size = r - l + 1;
                    }
                    if (token_in.contains(s[l]) && ++token_amount[s[l]] > 0){
                        counter--;
                    }
                    l++;
                }
            }
        }
        return min_size > s.size() ? "" : s.substr(min_l, min_size);
    }
};
```

这道题要用滑动窗口写，其实写的思路很明确，一个指针一直向前移动直到满足要求，然后左指针开始尝试减小长度。就是实现的部分需要花点心思。


## [633. 平方数之和](https://leetcode.cn/problems/sum-of-square-numbers/description/)

```C++
class Solution {
public:
    bool judgeSquareSum(int c) {
        int upper_bound = sqrt(c) + 1;
        long long l = 0, r = upper_bound;
        while(l <= r){
            long long tmp = l * l + r * r;
            if (tmp == c){
                return true;
            }else if(tmp < c){
                l += 1;
            }else if(tmp > c){
                r -=1;
            }
        }
        return false;
    }
};
```

这道题的思路很简单，就是需要用sqrt算一个上界出来，中间需要注意溢出问题，记得使用long/long long. 然后就是双指针搜索，算平方和根据与c的大小关系遍历。

## [680. 验证回文串 II](https://leetcode.cn/problems/valid-palindrome-ii/description/)

感觉这道题比上一题还要麻烦点，即删除掉一个字符后，只有剩下的字符串是回文的时候才能满足题意。此时删字符的方式有两种，左边和右边，当时在想怎么判断该删哪个，但其实可以都算出来，只要有一个满足回文即可：

```C++
class Solution {
public:
    bool isPalindrome(string s, int l, int r){
        while(l < r){
            if (s[l] != s[r]) return false;
            l++;
            r--;
        }
        return true;
    }

    bool validPalindrome(string s) {
        int len = s.size();
        int i = 0, j = len - 1;
        int counter = 0;
        while(i < j){
            if(s[i] != s[j]){
                return isPalindrome(s, i + 1, j) || isPalindrome(s, i, j - 1);
            }
            i++;
            j--;
        }
        return true;
    }
};
```

## [524. 通过删除字母匹配到字典里最长单词](https://leetcode.cn/problems/longest-word-in-dictionary-through-deleting/description/)

```C++
class Solution {
public:
    string findLongestWord(string s, vector<string>& dictionary) {
        sort(dictionary.begin(), dictionary.end(), [](string a, string b){
            return a.size() == b.size() ? a < b : a.size() > b.size();
        });
        // for(auto s: dictionary) cout << s <<"#";
        int len_s = s.size();
        string res = "";
        for(auto elem: dictionary){
            int elem_ptr = 0;
            int s_ptr = 0;
            int len = elem.size();
            while(elem_ptr < len && s_ptr < len_s){
                if(s[s_ptr] == elem[elem_ptr]) elem_ptr++;
                s_ptr++;
            }
            if(elem_ptr == len){
                res = elem;
                return res;
            }
        }
        return res;
    }
};
```

这道题的思路其实很简单，就是一个指针指向dictionary的元素，另一个指向字符串s，对dict每个元素进行判断即可。但有点trick的点就是题目中提到的要求长度最长，且字典序最小。这点可以借助排序，以长度倒排序，字典序升序排，遇到的第一个满足要求的element就是想要的那个。

但其实我们也看到这个算法其实效率很低，s每次都要遍历，其实可以记下s中每个元素的出现位置来对算法进行优化，这里就先不写了，等dp那章再写。


## [340. 至多包含 K 个不同字符的最长子串](https://leetcode.cn/problems/longest-substring-with-at-most-k-distinct-characters/description/)

```C++
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int len = s.size();
        if (len == 1) return min(k, len);
        if (k == 0) return 0;
        int i = 0;
        int j = 0;
        int current_tokens = 0;
        map<char, int> record;
        int res = -1;
        while(i < len && j < len){
            if(record.contains(s[j]) && record[s[j]] > 0){
                record[s[j]] += 1;
                j++;
            }else if(!record.contains(s[j]) || record[s[j]] == 0){
                while(current_tokens >= k){
                    record[s[i]] -= 1;
                    if(record[s[i]] == 0) current_tokens -= 1;
                    i++;
                }
                record[s[j]] = 1;
                current_tokens += 1;
                j++;
            }
            res = max(res, j - i);
        }
        return res;
    }
};
```

这道题可以用滑动窗口的方式解，窗口的长度没有明确限制，根据k动态调整，真正的限制是窗口内的不同字符数量最多为k个。因此可以用一个map来保存窗口内各个字符的个数，遍历整个字符串，如果当前窗口没满，就加不同字符；如果已经满了，遇到不同字符后需要将左端点移动直到字符数减少1. 每次都记录下当前窗口长度最后取最大值即可。