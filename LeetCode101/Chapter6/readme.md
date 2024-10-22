# 搜索

第六章了已经，前面有些章节的内容都忘记了，等动态规划那章前复习一下，然后开始dp！

## [695. 岛屿的最大面积](https://leetcode.cn/problems/max-area-of-island/description/)

这道题应该算挺经典的搜索题目，思路很简单: 遍历矩阵所有节点，如果`是岛屿&&没被遍历过`，从该节点上下左右进行扩张，用栈来存当前岛屿的待搜索节点，同样用`岛屿&&没被遍历过`条件进行过滤。另外要注意数组访问的合法性，别越界:

```C++
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int number_of_rows = grid.size();
        int number_of_columns = grid[0].size();
        int ret = 0;
        vector<vector<int>> visited(number_of_rows, vector<int>(number_of_columns, 0));
        for(int i = 0; i < number_of_rows; ++i){
            for(int j = 0; j < number_of_columns; ++j){
                int current_size = 0;
                if (grid[i][j] == 1 && visited[i][j] == 0){
                    stack<pair<int, int>> nodes = {};
                    nodes.push({i, j});
                    while(!nodes.empty()){
                        int current_row = nodes.top().first;
                        int current_col = nodes.top().second;
                        nodes.pop();
                        if (visited[current_row][current_col] == 1) continue;
                        visited[current_row][current_col] = 1;
                        current_size++;
                        int row_minus_1 = current_row - 1;
                        int row_plus_1 = current_row + 1;
                        int col_minus_1 = current_col - 1;
                        int col_plus_1 = current_col + 1;
                        if(col_minus_1 >= 0 && grid[current_row][col_minus_1] == 1 && visited[current_row][col_minus_1] == 0){
                            nodes.push({current_row, col_minus_1});
                        }
                        if(col_plus_1 < number_of_columns && grid[current_row][col_plus_1] == 1 && visited[current_row][col_plus_1] == 0){
                            nodes.push({current_row, col_plus_1});
                        }
                        if(row_minus_1 >= 0 && grid[row_minus_1][current_col] == 1 && visited[row_minus_1][current_col] == 0){
                            nodes.push({row_minus_1, current_col});
                        }
                        if(row_plus_1 < number_of_rows && grid[row_plus_1][current_col] == 1 && visited[row_plus_1][current_col] == 0){
                            nodes.push({row_plus_1, current_col});
                        }
                    }
                    // cout << current_size << endl;
                    // cout << i << ";" << j <<endl;
                    ret = max(ret, current_size);
                }
            }
        }
        return ret;
    }
};
```

## [547. 省份数量](https://leetcode.cn/problems/number-of-provinces/description/)

这道题也是类似的做法，相比上一题只能从上下左右进行扩张，这道题的节点可能有更多`邻居`，即对其他n-1个节点都要check是否相邻。如果相邻且没被访问过，那么就把该节点放入stack，同样对他剩下的n-1个节点重复上述过程:

```C++
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        std::vector<int> visited(n, 0);
        int ret = 0;
        for (int i = 0; i < n; ++i) {
            if (visited[i] == 1)
                continue;
            std::stack<int> tmp_stack;
            tmp_stack.push(i);
            while (!tmp_stack.empty()) {
                int province = tmp_stack.top();
                tmp_stack.pop();
                visited[province] = 1;
                for (int j = 0; j < n; ++j) {
                    if (visited[j] == 0 && isConnected[province][j] == 1) {
                        tmp_stack.push(j);
                    }
                }
            }
            ret++;
        }
        return ret;
    }
};
```

## [417. 太平洋大西洋水流问题](https://leetcode.cn/problems/pacific-atlantic-water-flow/description/)

这道题是个有点反逻辑的搜索问题，如果从`陆地`出发进行搜索，那么不仅需要记住搜索到海洋的整个stackrace，而且搜索空间也很爆炸。因此可以采用反逻辑的方法: 即让海水漫灌陆地。陆地的四条边的地方肯定是临海的，那我们从这四条边出发对内进行搜索，如果遇到相邻且海拔高于当前点的，他也能流到海里。由于题目中还将海分为了两类，我们可以将左和上两条边搜索得到的点认为可以到达海1，从右和下边搜索得到的点可以到达海2，然后对其取交集即可:


```C++
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = heights.size();
        int n = heights[0].size();
        std::vector<std::vector<int>> can1(m, vector<int>(n, 0));
        std::vector<std::vector<int>> can2(m, vector<int>(n, 0));

        std::vector<vector<int>> ret;

        for(int i = 0; i < m; ++i){
            search(heights, can1, i, 0);
            search(heights, can2, i, n - 1);
        }
        for(int i = 0; i < n; ++i){
            search(heights, can1, 0, i);
            search(heights, can2, m - 1, i);
        }

        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if (can1[i][j] == 1 && can1[i][j] == can2[i][j]){
                    ret.push_back({i, j});
                }
            }
        }
        return ret;
    }

    void search(std::vector<std::vector<int>>& map, std::vector<std::vector<int>>& can, int begin_x, int begin_y){
        // cout << begin_x << ";" <<begin_y <<endl;
        // cout << can.size() << ";" << can[0].size() <<endl;
        if(can[begin_x][begin_y] == 1){
            return;
        }
        can[begin_x][begin_y] = 1;
        std::vector<int> move_horizon = {-1, 1, 0, 0};
        std::vector<int> move_vertical = {0, 0, -1, 1};
        int current_x, current_y;
        for(int i = 0; i < 4; ++i){
            current_x = begin_x + move_vertical[i];
            current_y = begin_y + move_horizon[i];
            if(current_x >=0 && current_x < map.size()
              && current_y >=0 && current_y < map[0].size()
              && map[begin_x][begin_y] <= map[current_x][current_y]){
                search(map, can, current_x, current_y);
              }
        }
    }
};
```


## [46. 全排列](https://leetcode.cn/problems/permutations/description/)

这道题使用的是回溯法，回溯法和之前用的dfs差不多，但就像算法名字一样，回溯后需要保证状态回复原来的状态。例如这道题，全排列可以视为i位置的元素和(i, n)的元素分别swap, 然后i+1, i+2,..., n - 1 分别进行上述过程，在进入递归时，需要把当前数组的引用(当前状态)传进去；当前递归结束后，需要把数组的恢复之前的样子，然后继续循环递归:

```C++
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        int len = nums.size();
        vector<vector<int>> ret;
        search(nums, ret, 0);
        return ret;
    }
    void search(vector<int>& nums, vector<vector<int>>& ret, int current_index){
        if(current_index == nums.size() - 1)
            ret.push_back(nums);
        for(int i = current_index; i < nums.size(); ++i){
            std::swap(nums[current_index], nums[i]);
            search(nums, ret, current_index + 1);
            std::swap(nums[current_index], nums[i]);
        }
    }
};
```

## [77. 组合](https://leetcode.cn/problems/combinations/description/)

组合和排列差不多，只是元素间顺序没有要求。在这道题中，我们需要返回一个由长度为k的vector组成的vector，对于每个vector，我们可以对元素i分别赋 [1, n]的值，假设为m，然后对i+1 分别赋[m+1, n]的值，递归直到为第k位赋值:

```C++
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> ret;
        vector<int> all_numbers;
        for(int i = 1; i <= n; ++i) all_numbers.push_back(i);
        vector<int> tmp(k, 0);
        search(ret, all_numbers, tmp, 0, 0, k);
        return ret;
    }

    void search(vector<vector<int>>& ret, vector<int>& nums, vector<int>& current_nums, int current_index, int pos, int k){
        if (current_index == k) {ret.push_back(current_nums); return;}
        for(int i = pos; i < nums.size(); ++i){
            current_nums[current_index] = nums[i];
            search(ret, nums, current_nums, current_index + 1, i + 1, k);
        }
    }
};
```