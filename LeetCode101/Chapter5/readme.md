# 排序算法

在写leetcode之前，先回顾一下已有的排序算法，这里按所需的时间复杂度进行分类:

## O(n^2) 

### 冒泡排序

该排序方式非常形象，即一轮遍历中，最大(小)的那个值会一步步地向数组尾(头)移动，非常像冒泡. 下面给出一个算法示例(在本章目录下的dummy.cpp给出了检测所有提到算法正确性的示例程序)

```C++
void bubble_sort(std::vector<int>& arr){
    int len = arr.size();
    for(int i = 0; i < len - 1; ++i){
        for (int j = 0; j < len - i - 1; ++j){
            if(arr[j] > arr[j + 1]){
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}
```

如上述过程，每次循环中，j都会从数组头开始执行如下逻辑: `如果一个数组元素大于他的后继，那就交换他们`，这样，最大的数组元素一定会在这次循环中被放在数组尾部。然后排序问题的规模从0到n-1的长度为n的数组降低到了从0到n-2的长度为n-1的数组。这也是内层循环的条件为 `j < len - i - 1`的原因。外部循环只需要执行len - 1次即可，因为此时已经找到了len - 1个最值，剩下的那个一定是最小值。

可以从算法看出，该算法遍历了n * n 次数组，因此算法的时间复杂度为 O(n^2).

但上述算法有点无脑，即外部循环一定会遍历 len - 1 次，但有些时候数据的特殊性会使得外部循环还没执行完数组就已经有序了，例如数组 `arr[7] = {1,2,3,4,9,8,6}`, 因此我们可以对冒泡算法进行一个小小的优化，即当一次循环没有执行swap时，此时整个数组已经有序了:

```C++
void opt_bubble_sort(std::vector<int>& arr){
    int len = arr.size();
    for(int i = 0; i < len - 1; ++i){
        bool swapped = false;
        for (int j = 0; j < len - i - 1; ++j){
            if(arr[j] > arr[j + 1]){
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
```

额外讨论一下, bubble_sort是稳定算法吗？(即两个元素值相同时，排序后二者的相对位置不会改变)，答案是yes，因为只有在arr[j] > arr[j + 1]时才会进行交换。

## 选择排序

如名称所示，该排序方法为每次选择一个当前数组中最小(大)的元素，然后插入数组头(尾)。

```C++
void selection_sort(std::vector<int>& arr){
    int len = arr.size();
    for(int i = 0; i < len - 1; ++i){
        int minIndex = i;
        for (int j = i + 1; j < len; ++j){
            if(arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}
```
该算法逻辑和冒泡排序类似，但不同的是选择排序通过用一个中间变量将最值记录下来，减少了程序中数据交换的次数. 还有一个不同就是选择排序不是稳定的，例如这个数组 `arr[3] = {2, 2, 1}`, 选择排序会在第一轮循环将第一个`2`与`1`进行交换，从而改变两个`2`的相对位置。

既然我们每次记录下来了minIndex，我们是否可以同时记录下maxIndex呢？该算法称为二元选择排序:

```C++
void selection_sort2(std::vector<int>& arr){
    int len = arr.size();
    for(int i = 0; i < len / 2; ++i){
        int minIndex = i;
        int maxIndex = i;
        for (int j = i + 1; j < len - i; ++j){
            if(arr[j] < arr[minIndex]){
                minIndex = j;
            }
            if(arr[j] > arr[maxIndex]){
                maxIndex = j;
            }
        }
        if (minIndex == maxIndex) break;
        std::swap(arr[minIndex], arr[i]);
        if (maxIndex == i) maxIndex = minIndex;
        std::swap(arr[maxIndex], arr[len - 1 - i]);
    }
}
```
外层的循环只需要循环 len / 2次即可: 若长度为偶数，那么所有的元素都会被挑为min/max值；若长度为奇数，那么除了剩下的一个元素，剩下的元素都已经排好序，因此整个数组也是有序的。

## 插入排序

插入排序类似打牌，维护一个有序的部分数组，然后对每个新来的元素，找到应该插入的位置:

```C++
void insertion_sort(std::vector<int>& arr){
    int len = arr.size();
    for(int i = 1; i < len; ++i){
        int j = i - 1;
        int current = arr[i];
        while(j >= 0 && current < arr[j]){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = current;
    }
    printToShell(arr);
}
```

在代码中，将第一个元素视为初始有序的数组，如果current数组元素比arr[j]小，那么就移动arr[j]。当跳出循环时有两种情况: 1. j == -1, 说明current比所有数组内容都小，因此arr[0]应该被置为current；2. current >= arr[j], 此时current应该插入在arr[j + 1]的位置。二者插入位置都为j + 1.

同样我们分析其稳定性，由于判断条件是current < arr[j]时才会进行交换，因此当值相同时不会将原数组元素移动，因此是稳定的。