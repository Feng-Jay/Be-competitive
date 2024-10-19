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
