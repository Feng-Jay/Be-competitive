#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

void printToShell(std::vector<int>& arr){
    std::cout << "sorted: ";
    for(int num: arr){
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void bubble_sort(std::vector<int>& arr){
    int len = arr.size();
    for(int i = 0; i < len - 1; ++i){
        for (int j = 0; j < len - i - 1; ++j){
            if(arr[j] > arr[j + 1]){
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
    printToShell(arr);
}

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
    printToShell(arr);
}

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
    printToShell(arr);
}

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
    printToShell(arr);
}

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

void shell_sort(std::vector<int>& arr){
    int len = arr.size();
    for(int gap = len/2; gap > 0; gap /= 2){
        for(int currentIndex = gap; currentIndex < len; ++ currentIndex){
            int currentNumber = arr[currentIndex];
            int prevIndex = currentIndex - gap;
            while(prevIndex >= 0 && currentNumber < arr[prevIndex]){
                arr[prevIndex + gap] = arr[prevIndex];
                prevIndex -= gap;
            }
            arr[prevIndex + gap] = currentNumber;
        }
    }
    printToShell(arr);
}

void max_heap(std::vector<int>& arr, int i, int size){
    int leftIndex = 2 * i + 1;
    int rightIndex = leftIndex + 1;
    int largestIndex = i;
    if (leftIndex < size && arr[leftIndex] > arr[largestIndex]){
        largestIndex = leftIndex;
    }
    if(rightIndex < size && arr[rightIndex] > arr[largestIndex]){
        largestIndex = rightIndex;
    }
    if(largestIndex != i){
        std::swap(arr[i], arr[largestIndex]);
        max_heap(arr, largestIndex, size);
    }
}

void build_heap(std::vector<int>& arr){
    int len = arr.size();
    for(int i = len / 2 - 1; i >= 0; --i){
        max_heap(arr, i, len);
    }
}

void heap_sort(std::vector<int>& arr){
    build_heap(arr);
    int len = arr.size();
    for(int i = len - 1; i > 0; --i){
        std::swap(arr[0], arr[i]);
        max_heap(arr, 0, i);
    }
    printToShell(arr);
}


int partition(std::vector<int>& arr, int begin, int end){
    int pivot = arr[begin];
    int l = begin + 1;
    int r = end;
    while(l < r){
        while(l < r && arr[l] < pivot) l++;
        while(l < r && arr[r] > pivot) r--;
        if (l != r){
            std::swap(arr[l], arr[r]);
            r--;
        }
    }
    if(l == r && arr[r] > pivot) r--;
    if(r != begin) std::swap(arr[begin], arr[r]);
    return r;
}

void quick_sort(std::vector<int>& arr, int begin, int end){
    int middle = partition(arr, begin, end);
    if (middle != begin && middle != begin + 1)
        quick_sort(arr, begin, middle - 1);
    if (middle != end && middle != end - 1)
        quick_sort(arr, middle + 1, end);
}

void quick_sort(std::vector<int>& arr){
    quick_sort(arr, 0, arr.size() - 1);
    printToShell(arr);
}


void merge(std::vector<int>& arr, int begin, int end, std::vector<int>& result){
    int end1 = (begin + end) / 2;
    int begin2 = end1 + 1;
    int begin1 = begin;
    int end2 = end;
    int index1 = begin1;
    int index2 = begin2;
    while(index1 <= end1 && index2 <= end2){
        if(arr[index1] <= arr[index2]){
            result[index1 + index2 - begin2] = arr[index1];
            index1++;
        }else{
            result[index1 + index2 - begin2] = arr[index2];
            index2++;
        }
    }
    while (index1 <= end1) {
        result[index1 + index2 - begin2] = arr[index1];
        index1++;
    }
    while (index2 <= end2) {
        result[index1 + index2 - begin2] = arr[index2];
        index2++;
    }
    while(begin <= end){
        arr[begin] = result[begin];
        begin++;
    }
}

void merge_sort(std::vector<int>& arr, int begin, int end, std::vector<int>& result){
    if (begin == end) return;
    int middle = (begin + end) / 2;
    merge_sort(arr, begin, middle, result);
    merge_sort(arr, middle + 1, end, result);
    merge(arr, begin, end, result);
}

void merge_sort(std::vector<int>& arr){
    std::vector<int> result(arr.size(), 0);
    merge_sort(arr, 0, arr.size() - 1, result);
    printToShell(arr);
}


void count_sort(std::vector<int>& arr){
    if(arr.size() < 2) return;
    int len = arr.size();
    int min = arr[0];
    int max = arr[0];
    for(int elem: arr){
        if(elem < min) min = elem;
        if(elem > max) max = elem;
    }
    int counting_len = max - min + 1;
    std::vector<int> counting(counting_len, 0);
    for(int elem: arr){
        counting[elem - min]++;
    }
    int prevCount = 0;
    for(int i = 0; i < counting_len; ++i){
        int tmp = counting[i];
        counting[i] = prevCount;
        prevCount += tmp;
    }
    std::vector<int> result(len, 0);
    for(int elem: arr){
        result[counting[elem - min]] = elem;
        counting[elem - min]++;
    }
    for(int i = 0; i < len; ++i){
        arr[i] = result[i];
    }
    printToShell(arr);
}

void count_sort_reverse(std::vector<int>& arr){
    if(arr.size() < 2) return;
    int len = arr.size();
    int min = arr[0];
    int max = arr[0];
    for(int elem: arr){
        if(elem < min) min = elem;
        if(elem > max) max = elem;
    }
    int counting_len = max - min + 1;
    std::vector<int> counting(counting_len, 0);
    for(int elem: arr){
        counting[elem - min]++;
    }
    int prevCount = 0;
    for(int i = 0; i < counting_len; ++i){
        int tmp = counting[i];
        counting[i] += prevCount - 1;
        prevCount += tmp;
    }
    std::vector<int> result(len, 0);
    for(int i = len - 1; i >= 0; --i){
        result[counting[arr[i] - min]] = arr[i];
        counting[arr[i] - min]--;
    }
    for(int i = 0; i < len; ++i){
        arr[i] = result[i];
    }
    printToShell(arr);
}


void radix_sort(std::vector<int>& arr){
    if (arr.size() < 2) return;
    int len = arr.size();
    int max_elem = 0;
    for(int elem: arr){
        if (std::abs(elem) > max_elem){
            max_elem = std::abs(elem);
        }
    }
    int max_digits_length = 0;
    while(max_elem != 0){
        max_elem /= 10;
        max_digits_length++;
    }
    std::vector<int> counting(19, 0); // [-9, 9]
    std::vector<int> result(len, 0);
    int dev = 1;
    for(int i = 0; i < max_digits_length; ++i){
        for(int elem: arr){
            int radix = elem / dev % 10 + 9;
            counting[radix]++; 
        }
        for(int j = 1; j < counting.size(); ++j){
            counting[j] += counting[j - 1];
        }
        for(int j = len - 1; j >= 0; --j){
            int radix = arr[j] / dev % 10 + 9;
            result[--counting[radix]] = arr[j];
        }
        arr.assign(result.begin(), result.end());
        std::fill(counting.begin(), counting.end(), 0);
        dev *= 10;
    }
    printToShell(arr);
}


void bucket_sort_helper_insert_sort(int* arr, int size){
    for(int i = 1; i < size; ++i){
        int j = i - 1;
        int current = arr[i];
        while(j >=0 && current < arr[j]){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = current;
    }
}


void bucket_sort_arr(std::vector<int>& arr){
    int len = arr.size();
    if (len < 2) return;
    // prepare buckets
    int min_elem, max_elem;
    min_elem = max_elem = arr[0];
    for(int elem: arr){
        min_elem = elem < min_elem ? elem : min_elem;
        max_elem = elem > max_elem ? elem : max_elem;   
    }
    int range = max_elem - min_elem;
    int NUMBER_OF_BUCKETS = 10;
    int gap = range * 1.0 / (NUMBER_OF_BUCKETS - 1);
    int** buckets = new int*[NUMBER_OF_BUCKETS];
    for (int i = 0; i < NUMBER_OF_BUCKETS; ++i) {
        buckets[i] = new int[len]();  // Initialize all to 0
    }
    int* bucketLengths = new int[NUMBER_OF_BUCKETS]();
    
    // for(int i =0; i< NUMBER_OF_BUCKETS; ++i){
    //     std::cout<<bucketLengths[i] <<";";
    // }

    // put elems into buckets
    for(int elem: arr){
        int bucketIndex = (int) ((elem - min_elem) / gap);
        buckets[bucketIndex][bucketLengths[bucketIndex]] = elem;
        bucketLengths[bucketIndex]++;
    }

    // sort each buckets
    int index = 0;
    for(int i = 0; i < NUMBER_OF_BUCKETS; ++i){
        if (bucketLengths[i] <= 0) continue;
        bucket_sort_helper_insert_sort(buckets[i], bucketLengths[i]);
        std::copy(buckets[i], buckets[i] + bucketLengths[i], arr.begin() + index);
        index += bucketLengths[i];
    }
    printToShell(arr);
}



int main(){
    int n = 10;
    std::vector<int> testArr;
    std::random_device rd;   // Obtain a random number from hardware
    std::mt19937 gen(rd());  // Seed the generator
    std::uniform_int_distribution<> distr(1, 100); // Define the range

    // Generate random numbers and store them in the vector
    for (int i = 0; i < n; ++i) {
        testArr.push_back(distr(gen));
    }
    std::cout << "unordered: ";
    for(int num: testArr){
        std::cout << num << " ";
    }
    std::cout << std::endl;
    // bubble_sort(testArr);
    // opt_bubble_sort(testArr);
    // selection_sort(testArr);
    // selection_sort2(testArr);
    // insertion_sort(testArr);
    // shell_sort(testArr);
    // heap_sort(testArr);
    // quick_sort(testArr);
    // merge_sort(testArr);
    // count_sort_reverse(testArr);
    // radix_sort(testArr);
    bucket_sort_arr(testArr);
}