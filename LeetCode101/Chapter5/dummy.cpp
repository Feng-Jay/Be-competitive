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
    shell_sort(testArr);
}