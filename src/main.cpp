#include <iostream>
#include <chrono>
#include <iomanip>
#include <random>   
#include <ranges>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;
using namespace std::chrono;


class Algorithm {
    public:
        string name;
        int id;
        int position;
        int tries;
        int points;
        int matches;
        int wins;
        int losses;
        int ties;
        long double fastestTime;
        long double slowestTime;
        long double totalTime;
        long double currentTime;

        vector<int> played;

        Algorithm(string n, int i){
            name = n;
            id = i;
            position = 0;
            tries = 0;
            fastestTime = 10000000000;
            slowestTime = 0;
            currentTime = 0;
            totalTime = 0;
            points = 0;
        }

        string timeAsString(int i){
            long double time;
            switch (i)
            {
            case 1:
                time = fastestTime;
                break;
            case 2:
                time = slowestTime;
                break;
            case 3:
                time = totalTime;
                break;
            default:
                time = currentTime;
                break;
            }
            ostringstream output;
            output << fixed << setprecision(9) << time / 1000000000 << "s";
            return output.str();
        }

        virtual void sort(vector<int> a){};

        void display(){
            cout << "Played Against:\t";
            for(int i: played){
                cout << i  << " ";
            }
        }
};

class SelectionSort : public Algorithm {
    public:
    SelectionSort() : Algorithm("Selection Sort", 1){};

    void sort(vector<int> a){

        auto start = high_resolution_clock::now();

        int n = a.size();
        for(int i = 0; i < n - 1; i++){
            int min = i;
            for(int j = i + 1; j < n; j++){
                if(a[j] < a[min]){
                    min = j;
                }
            }
            if(min != i){
                int temp = a[i];
                a[i] = a[min];
                a[min] = temp;
            }
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime) fastestTime = totalTime;
        if(slowestTime < totalTime) slowestTime = totalTime;
        tries++;
    }

};

class BubbleSort : public Algorithm {
    public:
    BubbleSort() : Algorithm("Bubble Sort", 2){};

    void sort(vector<int> a){
        auto start = high_resolution_clock::now();

        int n = a.size();
        bool swapped = false;
        for(int i = 0; i < n - 1; i++){
            swapped = false;
            for(int j = 0; j < n - i - 1; j++){
                if(a[j] > a[j + 1]){
                    int temp = a[j];
                    a[j] = a[j + 1];
                    a[j + 1] = temp;
                    swapped = true;
                }
            }
            if (!swapped) break;
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }

};
class MergeSort : public Algorithm {

    void merge(vector<int>& arr, int left, int mid, int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        // Create temp vectors
        vector<int> L(n1), R(n2);

        // Copy data to temp vectors L[] and R[]
        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0;
        int k = left;

        // Merge the temp vectors back 
        // into arr[left..right]
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        // Copy the remaining elements of L[], 
        // if there are any
        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        // Copy the remaining elements of R[], 
        // if there are any
        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    // begin is for left index and end is right index
    // of the sub-array of arr to be sorted
    void mergeSort(vector<int>& arr, int left, int right)
    {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }

    public:
    MergeSort() : Algorithm("Merge Sort", 3){};

    void sort(vector<int> a){
        auto start = high_resolution_clock::now();

        mergeSort(a, 0, a.size() - 1);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime) fastestTime = totalTime;
        if(slowestTime < totalTime) slowestTime = totalTime;
        tries++;
    }

};

class InsertionSort : public Algorithm {
    public:
    InsertionSort() : Algorithm("Insertion Sort", 4){};

    void sort(vector<int> arr){
        auto start = high_resolution_clock::now();

        int n = arr.size();
        for (int i = 1; i < n; ++i) {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }

};
class OddEvenSort : public Algorithm {
    public:
    OddEvenSort() : Algorithm("Odd Even Sort", 5){};

    void sort(vector<int> arr){
        auto start = high_resolution_clock::now();

        int n = arr.size();
        bool isSorted = false; // Initially array is unsorted
    
        while (!isSorted)
        {
            isSorted = true;
        
            // Perform Bubble sort on odd indexed element
            for (int i=1; i<=n-2; i=i+2)
            {
                if (arr[i] > arr[i+1])
                {
                    swap(arr[i], arr[i+1]);
                    isSorted = false;
                }
            }
    
            // Perform Bubble sort on even indexed element
            for (int i=0; i<=n-2; i=i+2)
            {
                if (arr[i] > arr[i+1])
                {
                    swap(arr[i], arr[i+1]);
                    isSorted = false;
                }
            }
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }

};

class CocktailSort : public Algorithm {
    public:
    CocktailSort() : Algorithm("Cocktail Sort", 6){};

    void sort(vector<int> a){
        auto startT = high_resolution_clock::now();

        int n = a.size();
        bool swapped = true;
        int start = 0;
        int end = n - 1;
    
        while (swapped) {
            // reset the swapped flag on entering
            // the loop, because it might be true from
            // a previous iteration.
            swapped = false;
    
            // loop from left to right same as
            // the bubble sort
            for (int i = start; i < end; ++i) {
                if (a[i] > a[i + 1]) {
                    swap(a[i], a[i + 1]);
                    swapped = true;
                }
            }
    
            // if nothing moved, then array is sorted.
            if (!swapped)
                break;
    
            // otherwise, reset the swapped flag so that it
            // can be used in the next stage
            swapped = false;
    
            // move the end point back by one, because
            // item at the end is in its rightful spot
            --end;
    
            // from right to left, doing the
            // same comparison as in the previous stage
            for (int i = end - 1; i >= start; --i) {
                if (a[i] > a[i + 1]) {
                    swap(a[i], a[i + 1]);
                    swapped = true;
                }
            }
    
            // increase the starting point, because
            // the last stage would have moved the next
            // smallest number to its rightful spot.
            ++start;
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - startT);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }

};

class QuickSort : public Algorithm {
    private:
    int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = (low - 1);
        
        for(int j = low; j <= high - 1; j++) {
            if(arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        return (i + 1);
    }
    
    void quickSort(vector<int>& arr, int low, int high) {
        if(low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
    
    public:
    QuickSort() : Algorithm("Quick Sort", 7){};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        quickSort(arr, 0, arr.size() - 1);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class HeapSort : public Algorithm {
    private:
    void heapify(vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if(left < n && arr[left] > arr[largest])
            largest = left;
            
        if(right < n && arr[right] > arr[largest])
            largest = right;
            
        if(largest != i) {
            // Manual swap without using built-in function
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
            heapify(arr, n, largest);
        }
    }
    
    public:
    HeapSort() : Algorithm("Heap Sort", 8){};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        int n = arr.size();
        
        // Build heap
        for(int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);
            
        // Extract elements from heap one by one
        for(int i = n - 1; i > 0; i--) {
            // Manual swap without using built-in function
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            heapify(arr, i, 0);
        }
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class RadixLSDSort : public Algorithm {
private:
    // Helper function to find maximum element
    int getMax(const vector<int>& arr) {
        if (arr.empty()) return 0;
        int mx = arr[0];
        for (int i = 1; i < arr.size(); i++)
            mx = max(mx, arr[i]);
        return mx;
    }

    // Helper function to handle negative numbers
    int handleNegativeNumbers(vector<int>& arr) {
        // Find minimum value
        int minVal = *min_element(arr.begin(), arr.end());
        
        // If there are negative numbers, shift all numbers to positive
        if (minVal < 0) {
            for (int& num : arr) {
                num -= minVal; // Make all numbers non-negative
            }
        }
        return minVal;
    }

public:
    RadixLSDSort() : Algorithm("Radix LSD Sort", 9) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        if (arr.empty() || arr.size() == 1) {
            return; // Already sorted
        }

        // Handle negative numbers
        int shift = handleNegativeNumbers(arr);
        
        int n = arr.size();
        int max = getMax(arr);
        vector<int> output(n);
        
        // Do counting sort for every digit
        for (int exp = 1; max/exp > 0; exp *= 10) {
            vector<int> count(10, 0);
            
            // Store count of occurrences
            for (int i = 0; i < n; i++)
                count[(arr[i]/exp) % 10]++;
            
            // Change count[i] so that count[i] contains actual
            // position of this digit in output[]
            for (int i = 1; i < 10; i++)
                count[i] += count[i-1];
            
            // Build the output array
            for (int i = n-1; i >= 0; i--) {
                output[count[(arr[i]/exp) % 10] - 1] = arr[i];
                count[(arr[i]/exp) % 10]--;
            }
            
            // Copy output array to arr[], so that arr[] now
            // contains sorted numbers according to current digit
            for (int i = 0; i < n; i++)
                arr[i] = output[i];
        }

        // Shift back if we handled negative numbers
        if (shift < 0) {
            for (int& num : arr) {
                num += shift;
            }
        }
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class RadixMSDSort : public Algorithm {
private:
    void msdRadixSort(vector<int>& arr, int left, int right, int exp) {
        if (left >= right || exp == 0) return;
        
        vector<int> output(right - left + 1);
        vector<int> count(10, 0);
        
        // Count frequencies
        for (int i = left; i <= right; i++)
            count[(arr[i] / exp) % 10]++;
            
        // Calculate positions
        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];
            
        // Build output array
        for (int i = right; i >= left; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        
        // Copy back to original array
        for (int i = 0; i < right - left + 1; i++)
            arr[left + i] = output[i];
            
        // Recursively sort each bucket
        int pos = left;
        for (int i = 0; i < 10; i++) {
            int newPos = left + (i == 0 ? 0 : count[i - 1]);
            int bucketSize = (i == 0 ? count[0] : count[i] - count[i - 1]);
            if (bucketSize > 1)
                msdRadixSort(arr, newPos, newPos + bucketSize - 1, exp / 10);
        }
    }

public:
    RadixMSDSort() : Algorithm("Radix MSD Sort", 10){};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        int max = arr[0];
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] > max) max = arr[i];
        }
        int exp = 1;
        while (max / exp > 0) exp *= 10;
        msdRadixSort(arr, 0, arr.size() - 1, exp / 10);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class CountingSort : public Algorithm {
public:
    CountingSort() : Algorithm("Counting Sort", 11){};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        int max = arr[0];
        int min = arr[0];
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] > max) max = arr[i];
            if (arr[i] < min) min = arr[i];
        }
        int range = max - min + 1;
        
        vector<int> count(range), output(arr.size());
        
        // Store count of each element
        for (int i = 0; i < arr.size(); i++)
            count[arr[i] - min]++;
            
        // Change count[i] to contain actual position
        for (int i = 1; i < count.size(); i++)
            count[i] += count[i - 1];
            
        // Build output array
        for (int i = arr.size() - 1; i >= 0; i--) {
            output[count[arr[i] - min] - 1] = arr[i];
            count[arr[i] - min]--;
        }
        
        // Copy output array to arr
        for (int i = 0; i < arr.size(); i++)
            arr[i] = output[i];
            
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class TimSort : public Algorithm {
private:
    static const int RUN = 32;  // minimum size for a run

    void insertionSort(vector<int>& arr, int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            int temp = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > temp) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = temp;
        }
    }

    void merge(vector<int>& arr, int l, int m, int r) {
        int len1 = m - l + 1, len2 = r - m;
        vector<int> left(len1), right(len2);

        for (int i = 0; i < len1; i++)
            left[i] = arr[l + i];
        for (int i = 0; i < len2; i++)
            right[i] = arr[m + 1 + i];

        int i = 0, j = 0, k = l;

        while (i < len1 && j < len2) {
            if (left[i] <= right[j]) {
                arr[k] = left[i];
                i++;
            }
            else {
                arr[k] = right[j];
                j++;
            }
            k++;
        }

        while (i < len1) {
            arr[k] = left[i];
            k++;
            i++;
        }

        while (j < len2) {
            arr[k] = right[j];
            k++;
            j++;
        }
    }

    void timSort(vector<int>& arr) {
        int n = arr.size();

        // Sort individual subarrays of size RUN using insertion sort
        for (int i = 0; i < n; i += RUN)
            insertionSort(arr, i, min((i + RUN - 1), (n - 1)));

        // Start merging from size RUN. It will merge
        // to form size 2*RUN, then 4*RUN, and so on
        for (int size = RUN; size < n; size = 2 * size) {
            for (int left = 0; left < n; left += 2 * size) {
                int mid = left + size - 1;
                int right_end = min((left + 2 * size - 1), (n - 1));

                if (mid < right_end)
                    merge(arr, left, mid, right_end);
            }
        }
    }

public:
    TimSort() : Algorithm("Tim Sort", 12) {};

    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();

        timSort(arr);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class ShellSort : public Algorithm {
public:
    ShellSort() : Algorithm("Shell Sort", 13) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        int n = arr.size();
        
        // Start with a big gap, then reduce the gap
        for (int gap = n/2; gap > 0; gap /= 2) {
            // Do a gapped insertion sort
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                    arr[j] = arr[j - gap];
                
                arr[j] = temp;
            }
        }
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class CombSort : public Algorithm {
private:
    int getNextGap(int gap) {
        gap = (gap * 10) / 13;
        return (gap < 1) ? 1 : gap;
    }
    
public:
    CombSort() : Algorithm("Comb Sort", 14) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        int n = arr.size();
        int gap = n;
        bool swapped = true;
        
        while (gap != 1 || swapped) {
            gap = getNextGap(gap);
            swapped = false;
            
            for (int i = 0; i < n - gap; i++) {
                if (arr[i] > arr[i + gap]) {
                    int temp = arr[i];
                    arr[i] = arr[i + gap];
                    arr[i + gap] = temp;
                    swapped = true;
                }
            }
        }
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class CycleSort : public Algorithm {
public:
    CycleSort() : Algorithm("Cycle Sort", 15) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        int n = arr.size();
        for (int cycle_start = 0; cycle_start < n - 1; cycle_start++) {
            int item = arr[cycle_start];
            int pos = cycle_start;
            
            for (int i = cycle_start + 1; i < n; i++)
                if (arr[i] < item)
                    pos++;
            
            if (pos == cycle_start)
                continue;
            
            while (item == arr[pos])
                pos++;
            int temp = item;
            item = arr[pos];
            arr[pos] = temp;
            
            while (pos != cycle_start) {
                pos = cycle_start;
                for (int i = cycle_start + 1; i < n; i++)
                    if (arr[i] < item)
                        pos++;
                
                while (item == arr[pos])
                    pos++;
                
                temp = item;
                item = arr[pos]; 
                arr[pos] = temp;
            }
        }
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class PancakeSort : public Algorithm {
private:
    void flip(vector<int>& arr, int i) {
        int start = 0;
        while (start < i) {
            int temp = arr[start];
            arr[start] = arr[i];
            arr[i] = temp;
            start++;
            i--;
        }
    }
    
    int findMax(vector<int>& arr, int n) {
        int maxIdx = 0;
        for (int i = 1; i < n; ++i)
            if (arr[i] > arr[maxIdx])
                maxIdx = i;
        return maxIdx;
    }
    
public:
    PancakeSort() : Algorithm("Pancake Sort", 16) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        int n = arr.size();
        for (int curr_size = n; curr_size > 1; --curr_size) {
            int maxIdx = findMax(arr, curr_size);
            
            if (maxIdx != curr_size - 1) {
                if (maxIdx != 0) {
                    flip(arr, maxIdx);
                }
                flip(arr, curr_size - 1);
            }
        }
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class BitonicSort : public Algorithm {
private:
    void compAndSwap(vector<int>& arr, int i, int j, bool dir) {
        if (dir == (arr[i] > arr[j])) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    void bitonicMerge(vector<int>& arr, int low, int cnt, bool dir) {
        if (cnt > 1) {
            int k = cnt / 2;
            for (int i = low; i < low + k; i++)
                compAndSwap(arr, i, i + k, dir);
            bitonicMerge(arr, low, k, dir);
            bitonicMerge(arr, low + k, k, dir);
        }
    }
    
    void bitonicSort(vector<int>& arr, int low, int cnt, bool dir) {
        if (cnt > 1) {
            int k = cnt / 2;
            bitonicSort(arr, low, k, true);
            bitonicSort(arr, low + k, k, false);
            bitonicMerge(arr, low, cnt, dir);
        }
    }
    
public:
    BitonicSort() : Algorithm("Bitonic Sort", 17) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        bitonicSort(arr, 0, arr.size(), true);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class GnomeSort : public Algorithm {
public:
    GnomeSort() : Algorithm("Gnome Sort", 18) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        int n = arr.size();
        int index = 0;
        
        while (index < n) {
            if (index == 0)
                index++;
            if (arr[index] >= arr[index - 1])
                index++;
            else {
                // Manual swap without using built-in function
                int temp = arr[index];
                arr[index] = arr[index - 1];
                arr[index - 1] = temp;
                index--;
            }
        }
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class StrandSort : public Algorithm {
private:
    // Add this custom merge function
    vector<int> mergeVectors(const vector<int>& left, const vector<int>& right) {
        vector<int> result;
        size_t i = 0, j = 0;
        
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                result.push_back(left[i]);
                i++;
            } else {
                result.push_back(right[j]);
                j++;
            }
        }
        
        // Add remaining elements
        while (i < left.size()) {
            result.push_back(left[i]);
            i++;
        }
        
        while (j < right.size()) {
            result.push_back(right[j]);
            j++;
        }
        
        return result;
    }

public:
    StrandSort() : Algorithm("Strand Sort", 21) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        vector<int> result;
        
        while (!arr.empty()) {
            vector<int> sublist;
            sublist.push_back(arr[0]);
            arr.erase(arr.begin());
            
            for (auto it = arr.begin(); it != arr.end();) {
                if (*it >= sublist.back()) {
                    sublist.push_back(*it);
                    it = arr.erase(it);
                } else {
                    ++it;
                }
            }
            
            // Use our custom merge function instead
            result = mergeVectors(result, sublist);
        }
        
        arr = result;
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class TagSort : public Algorithm {
private:
    // Add custom merge function
    vector<int> mergeVectors(const vector<int>& left, const vector<int>& right) {
        vector<int> result;
        size_t i = 0, j = 0;
        
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                result.push_back(left[i]);
                i++;
            } else {
                result.push_back(right[j]);
                j++;
            }
        }
        
        // Add remaining elements
        while (i < left.size()) {
            result.push_back(left[i]);
            i++;
        }
        
        while (j < right.size()) {
            result.push_back(right[j]);
            j++;
        }
        
        return result;
    }

public:
    TagSort() : Algorithm("Tag Sort", 20) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        int n = arr.size();
        vector<pair<int, int>> tagged(n);
        
        // Tag elements with their indices
        for(int i = 0; i < n; i++) {
            tagged[i] = {arr[i], i};
        }
        // Sort based on values using bubble sort
        for(int i = 0; i < n - 1; i++) {
            for(int j = 0; j < n - i - 1; j++) {
                if(tagged[j].first > tagged[j + 1].first) {
                    auto temp = tagged[j];
                    tagged[j] = tagged[j + 1];
                    tagged[j + 1] = temp;
                }
            }
        }
        // Create auxiliary array and copy elements
        vector<bool> visited(n, false);
        
        // Process all cycles
        for(int i = 0; i < n; i++) {
            if(visited[i] || tagged[i].second == i)
                continue;
                
            int cycle_size = 0;
            int j = i;
            
            while(!visited[j]) {
                visited[j] = true;
                j = tagged[j].second;
                cycle_size++;
            }
            
            // If cycle size is greater than 1
            if(cycle_size > 0) {
                int temp = arr[i];
                j = tagged[i].second;
                
                while(j != i) {
                    int next_temp = arr[j];
                    arr[j] = temp;
                    temp = next_temp;
                    j = tagged[j].second;
                }
                arr[i] = temp;
            }
        }
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};


class BucketSort : public Algorithm {
public:
    BucketSort() : Algorithm("Bucket Sort", 22) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        int n = arr.size();
        int max_val = arr[0];
        int min_val = arr[0];
        
        for(int i = 1; i < n; i++) {
            if(arr[i] > max_val) max_val = arr[i];
            if(arr[i] < min_val) min_val = arr[i];
        }
        
        // Number of buckets
        int bucket_range = (max_val - min_val) / n + 1;
        vector<vector<int>> buckets(n);
        
        // Put array elements in different buckets
        for (int i = 0; i < n; i++) {
            int bucket_index = (arr[i] - min_val) / bucket_range;
            // Manually add element to bucket
            buckets[bucket_index].push_back(arr[i]);
        }
        
        // Sort individual buckets using insertion sort
        for (auto& bucket : buckets) {
            // Insertion sort implementation
            for (int i = 1; i < bucket.size(); i++) {
                int key = bucket[i];
                int j = i - 1;
                while (j >= 0 && bucket[j] > key) {
                    bucket[j + 1] = bucket[j];
                    j--;
                }
                bucket[j + 1] = key;
            }
        }
        
        // Concatenate all buckets into arr[]
        int index = 0;
        for (const auto& bucket : buckets) {
            for (int val : bucket) {
                arr[index++] = val;
            }
        }
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class IntroSort : public Algorithm {
private:
    void insertionSort(vector<int>& arr, int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            int key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
    
    int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] <= pivot) {
                i++;
                // Manual swap
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        // Manual swap
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        return i + 1;
    }
    
    void heapify(vector<int>& arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && arr[left] > arr[largest])
            largest = left;
        if (right < n && arr[right] > arr[largest])
            largest = right;
            
        if (largest != i) {
            // Manual swap
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
            heapify(arr, n, largest);
        }
    }
    
    void heapSort(vector<int>& arr, int low, int high) {
        int n = high - low + 1;
        
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);
            
        for (int i = n - 1; i > 0; i--) {
            // Manual swap
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            heapify(arr, i, 0);
        }
    }
    
    void introSortUtil(vector<int>& arr, int low, int high, int depthLimit) {
        int size = high - low + 1;
        
        if (size < 16) {
            insertionSort(arr, low, high);
            return;
        }
        
        if (depthLimit == 0) {
            heapSort(arr, low, high);
            return;
        }
        
        int pivot = partition(arr, low, high);
        introSortUtil(arr, low, pivot - 1, depthLimit - 1);
        introSortUtil(arr, pivot + 1, high, depthLimit - 1);
    }

public:
    IntroSort() : Algorithm("Intro Sort", 24) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        int depthLimit = 2 * log2(arr.size());
        introSortUtil(arr, 0, arr.size() - 1, depthLimit);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class IterativeMergeSort : public Algorithm {
private:
    void merge(vector<int>& arr, int l, int m, int r) {
        int i, j, k;
        int n1 = m - l + 1;
        int n2 = r - m;
        
        vector<int> L(n1), R(n2);
        
        for(i = 0; i < n1; i++)
            L[i] = arr[l + i];
        for(j = 0; j < n2; j++)
            R[j] = arr[m + 1 + j];
            
        i = 0;
        j = 0;
        k = l;
        
        while(i < n1 && j < n2) {
            if(L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        
        while(i < n1) {
            arr[k] = L[i];
            k++;
            i++;
        }
        
        while(j < n2) {
            arr[k] = R[j];
            k++;
            j++;
        }
    }
    
public:
    IterativeMergeSort() : Algorithm("Iterative Merge Sort", 28) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        int n = arr.size();
        for(int curr_size = 1; curr_size <= n-1; curr_size = 2*curr_size) {
            for(int left_start = 0; left_start < n-1; left_start += 2*curr_size) {
                int mid;
                if(left_start + curr_size - 1 < n-1) {
                    mid = left_start + curr_size - 1;
                } else {
                    mid = n-1;
                }
                
                int right_end;
                if(left_start + 2*curr_size - 1 < n-1) {
                    right_end = left_start + 2*curr_size - 1;
                } else {
                    right_end = n-1;
                }
                
                merge(arr, left_start, mid, right_end);
            }
        }
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class PatienceSort : public Algorithm {
private:
    struct Pile {
        int* cards;
        int size;
        int capacity;
        
        Pile() {
            capacity = 10;
            cards = new int[capacity];
            size = 0;
        }
        
        ~Pile() {
            delete[] cards;
        }
        
        int top() const { 
            return cards[size - 1]; 
        }
        
        void push(int x) {
            if (size == capacity) {
                int newCapacity = capacity * 2;
                int* newCards = new int[newCapacity];
                for (int i = 0; i < size; i++) {
                    newCards[i] = cards[i];
                }
                delete[] cards;
                cards = newCards;
                capacity = newCapacity;
            }
            cards[size++] = x;
        }
        
        int pop() {
            int x = cards[--size];
            return x;
        }
        
        bool empty() const { 
            return size == 0; 
        }
    };
    
public:
    PatienceSort() : Algorithm("Patience Sort", 32) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        Pile* piles = new Pile[arr.size()];
        int numPiles = 0;
        
        // Create piles
        for(int i = 0; i < arr.size(); i++) {
            int x = arr[i];
            bool placed = false;
            for(int j = 0; j < numPiles; j++) {
                if(piles[j].top() >= x) {
                    piles[j].push(x);
                    placed = true;
                    break;
                }
            }
            if(!placed) {
                piles[numPiles].push(x);
                numPiles++;
            }
        }
        
        // Manual min heap implementation
        int* heap = new int[numPiles * 2];
        int* pileIndices = new int[numPiles];
        int heapSize = 0;
        
        // Initialize heap with top cards
        for(int i = 0; i < numPiles; i++) {
            if(!piles[i].empty()) {
                heap[heapSize] = piles[i].top();
                pileIndices[heapSize] = i;
                int curr = heapSize;
                while(curr > 0) {
                    int parent = (curr - 1) / 2;
                    if(heap[curr] < heap[parent]) {
                        // Swap heap elements
                        int temp = heap[curr];
                        heap[curr] = heap[parent]; 
                        heap[parent] = temp;
                        // Swap pile indices
                        temp = pileIndices[curr];
                        pileIndices[curr] = pileIndices[parent];
                        pileIndices[parent] = temp;
                        curr = parent;
                    } else {
                        break;
                    }
                }
                heapSize++;
            }
        }
        
        // Merge into final sorted array
        int index = 0;
        while(heapSize > 0) {
            arr[index++] = heap[0];
            int pileIdx = pileIndices[0];
            piles[pileIdx].pop();
            
            if(!piles[pileIdx].empty()) {
                heap[0] = piles[pileIdx].top();
            } else {
                heap[0] = heap[heapSize - 1];
                pileIndices[0] = pileIndices[heapSize - 1];
                heapSize--;
            }
            
            // Heapify down
            int curr = 0;
            while(true) {
                int smallest = curr;
                int left = 2 * curr + 1;
                int right = 2 * curr + 2;
                
                if(left < heapSize && heap[left] < heap[smallest])
                    smallest = left;
                if(right < heapSize && heap[right] < heap[smallest]) 
                    smallest = right;
                
                if(smallest != curr) {
                    // Swap heap elements
                    int temp = heap[curr];
                    heap[curr] = heap[smallest];
                    heap[smallest] = temp;
                    // Swap pile indices  
                    temp = pileIndices[curr];
                    pileIndices[curr] = pileIndices[smallest];
                    pileIndices[smallest] = temp;
                    curr = smallest;
                } else {
                    break;
                }
            }
        }
        
        delete[] heap;
        delete[] pileIndices;
        delete[] piles;
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class TournamentSort : public Algorithm {
private:
    struct Node {
        int value;
        int index;
        Node *left, *right;
        Node(int v = INT_MAX, int i = -1) : value(v), index(i), left(nullptr), right(nullptr) {}
    };
    
    Node* buildTree(vector<int>& arr, int left, int right) {
        if (left > right) return new Node();
        if (left == right) return new Node(arr[left], left);
        
        int mid = (left + right) / 2;
        Node* node = new Node();
        node->left = buildTree(arr, left, mid);
        node->right = buildTree(arr, mid + 1, right);
        
        if (node->left->value < node->right->value) {
            node->value = node->left->value;
            node->index = node->left->index;
        } else {
            node->value = node->right->value;
            node->index = node->right->index;
        }
        return node;
    }
    
    void updateTree(Node* node, int index) {
        node->value = INT_MAX;
        node->index = -1;
        
        if (node->left) {
            if (node->left->value < node->right->value) {
                node->value = node->left->value;
                node->index = node->left->index;
            } else {
                node->value = node->right->value;
                node->index = node->right->index;
            }
        }
    }
    
    void cleanupTree(Node* node) {
        if (node) {
            cleanupTree(node->left);
            cleanupTree(node->right);
            delete node;
        }
    }

public:
    TournamentSort() : Algorithm("Tournament Sort", 34) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        int n = arr.size();
        vector<int> result(n);
        Node* root = buildTree(arr, 0, n-1);
        
        for (int i = 0; i < n; i++) {
            result[i] = root->value;
            arr[root->index] = INT_MAX;
            updateTree(root, root->index);
        }
        
        arr = result;
        cleanupTree(root);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class TreeSort : public Algorithm {
private:
    struct Node {
        int data;
        Node *left, *right;
        Node(int val) : data(val), left(nullptr), right(nullptr) {}
    };
    
    void insert(Node*& root, int key) {
        if(!root) {
            root = new Node(key);
            return;
        }
        if(key < root->data)
            insert(root->left, key);
        else
            insert(root->right, key);
    }
    
    void inorder(Node* root, vector<int>& arr, int& index) {
        if(!root) return;
        inorder(root->left, arr, index);
        arr[index++] = root->data;
        inorder(root->right, arr, index);
    }
    
    void cleanup(Node* root) {
        if(!root) return;
        cleanup(root->left);
        cleanup(root->right);
        delete root;
    }

public:
    TreeSort() : Algorithm("Tree Sort", 36) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        Node* root = nullptr;
        for(int x : arr)
            insert(root, x);
            
        int index = 0;
        inorder(root, arr, index);
        
        cleanup(root);
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class LibrarySort : public Algorithm {
public:
    LibrarySort() : Algorithm("Library Sort", 31) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        int n = arr.size();
        vector<int> sorted;
        sorted.push_back(arr[0]);
        
        for(int i = 1; i < n; i++) {
            auto pos = lower_bound(sorted.begin(), sorted.end(), arr[i]);
            sorted.insert(pos, arr[i]);
        }
        
        arr = sorted;
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class SmoothSort : public Algorithm {
private:
    void heapify(vector<int>& arr, int start, int end) {
        int root = start;
        while(root * 2 + 1 <= end) {
            int child = root * 2 + 1;
            if(child + 1 <= end && arr[child] < arr[child + 1])
                child++;
            if(arr[root] < arr[child]) {
                int temp = arr[root];
                arr[root] = arr[child];
                arr[child] = temp;
                root = child;
            } else
                return;
        }
    }

public:
    SmoothSort() : Algorithm("Smooth Sort", 33) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        int n = arr.size();
        for(int i = (n - 2) / 2; i >= 0; i--)
            heapify(arr, i, n - 1);
            
        for(int i = n - 1; i > 0; i--) {
            // Manual swap
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            heapify(arr, 0, i - 1);
        }
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class FlashSort : public Algorithm {
public:
    FlashSort() : Algorithm("Flash Sort", 35) {};
    
    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        
        int n = arr.size();
        if(n <= 1) return;
        
        int min = arr[0], max = arr[0];
        for(int i = 1; i < n; i++) {
            if(arr[i] < min) min = arr[i];
            if(arr[i] > max) max = arr[i];
        }
        
        if(max == min) return;
        
        int m = 0.43 * n;
        vector<int> l(m);
        
        for(int i = 0; i < n; i++) {
            int k = ((m - 1) * (arr[i] - min)) / (max - min);
            l[k]++;
        }
        
        for(int i = 1; i < m; i++)
            l[i] += l[i - 1];
            
        // Permutation
        int hold = arr[0];
        int flash;
        int j = 0;
        int k = m - 1;
        int t = 0;
        
        while(t < n - 1) {
            while(j > l[k] - 1) {
                j++;
                k = ((m - 1) * (arr[j] - min)) / (max - min);
            }
            flash = arr[j];
            while(j != l[k]) {
                k = ((m - 1) * (flash - min)) / (max - min);
                hold = arr[l[k] - 1];
                arr[l[k] - 1] = flash;
                flash = hold;
                l[k]--;
                t++;
            }
        }
        
        // Insertion sort for remaining elements
        for(int i = 1; i < n; i++) {
            hold = arr[i];
            j = i - 1;
            while(j >= 0 && arr[j] > hold) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = hold;
        }
        
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if(fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if(slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class InPlaceMergeSort : public Algorithm {
private:
    void merge(vector<int>& arr, int left, int mid, int right) {
        int start2 = mid + 1;
        if (arr[mid] <= arr[start2]) return;

        while (left <= mid && start2 <= right) {
            if (arr[left] <= arr[start2]) {
                left++;
            } else {
                int value = arr[start2];
                int index = start2;

                while (index != left) {
                    arr[index] = arr[index - 1];
                    index--;
                }
                arr[left] = value;

                left++;
                mid++;
                start2++;
            }
        }
    }

    void mergeSort(vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

public:
    InPlaceMergeSort() : Algorithm("In-Place Merge Sort", 35) {};

    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        mergeSort(arr, 0, arr.size() - 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if (fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if (slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};


class QuadSort : public Algorithm {
private:
    void insertionSort(vector<int>& arr, int left, int right) {
        for (int i = left + 1; i <= right; ++i) {
            int key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    void merge(vector<int>& arr, int left, int mid, int right) {
        vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right) {
            if (arr[i] <= arr[j]) {
                temp[k++] = arr[i++];
            } else {
                temp[k++] = arr[j++];
            }
        }

        while (i <= mid) temp[k++] = arr[i++];
        while (j <= right) temp[k++] = arr[j++];

        for (i = left, k = 0; i <= right; ++i, ++k) {
            arr[i] = temp[k];
        }
    }

    void quadSort(vector<int>& arr, int left, int right) {
        if (right - left <= 16) {  // Use insertion sort for small subarrays
            insertionSort(arr, left, right);
            return;
        }

        int mid = left + (right - left) / 2;
        quadSort(arr, left, mid);
        quadSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }

public:
    QuadSort() : Algorithm("Quad Sort", 36) {};

    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        quadSort(arr, 0, arr.size() - 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if (fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if (slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class WeakHeapSort : public Algorithm {
private:
    vector<bool> bits;
    int weakParent(int i) {
        while (i & 1) i >>= 1;
        return i >> 1;
    }

    void join(vector<int>& arr, int i) {
        int j = weakParent(i);
        if (arr[j] < arr[i]) {
            // Manual swap
            int temp = arr[j];
            arr[j] = arr[i]; 
            arr[i] = temp;
            bits[i] = !bits[i];
        }
    }

    void buildWeakHeap(vector<int>& arr) {
        int n = arr.size();
        bits.resize(n, false);
        for (int i = 1; i < n; ++i) {
            join(arr, i);
        }
    }

public:
    WeakHeapSort() : Algorithm("Weak Heap Sort", 37) {};

    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        buildWeakHeap(arr);
        for (int i = arr.size() - 1; i > 0; --i) {
            // Manual swap
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            
            int j = 1;
            while (j < i) {
                int k = 2 * j + bits[j];
                if (k >= i) break;
                if (arr[j] < arr[k]) {
                    // Manual swap
                    int temp = arr[j];
                    arr[j] = arr[k];
                    arr[k] = temp;
                }
                j = k;
            }
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if (fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if (slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class AmericanFlagSort : public Algorithm {
private:
    void flagSort(vector<int>& arr, int left, int right, int byte) {
        if (right - left <= 1 || byte < 0) return;

        vector<int> count(256, 0);
        vector<int> offset(256, 0);

        for (int i = left; i < right; ++i) {
            unsigned char digit = (arr[i] >> (byte * 8)) & 0xFF;
            count[digit]++;
        }

        offset[0] = left;
        for (int i = 1; i < 256; ++i) {
            offset[i] = offset[i - 1] + count[i - 1];
        }

        vector<int> temp(right - left);
        for (int i = left; i < right; ++i) {
            unsigned char digit = (arr[i] >> (byte * 8)) & 0xFF;
            temp[offset[digit]++ - left] = arr[i];
        }

        for (int i = left; i < right; ++i) {
            arr[i] = temp[i - left];
        }

        for (int i = 0; i < 256; ++i) {
            int subLeft = (i == 0) ? left : offset[i - 1];
            int subRight = offset[i];
            if (subLeft < subRight) {
                flagSort(arr, subLeft, subRight, byte - 1);
            }
        }
    }

public:
    AmericanFlagSort() : Algorithm("American Flag Sort", 38) {};

    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        flagSort(arr, 0, arr.size(), sizeof(int) - 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if (fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if (slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};


class ThreeWayMergeSort : public Algorithm {
private:
    void merge(vector<int>& arr, int left, int mid1, int mid2, int right) {
        vector<int> temp(right - left + 1);
        int i = left, j = mid1 + 1, k = mid2 + 1, l = 0;

        while (i <= mid1 && j <= mid2 && k <= right) {
            if (arr[i] < arr[j]) {
                if (arr[i] < arr[k]) temp[l++] = arr[i++];
                else temp[l++] = arr[k++];
            } else {
                if (arr[j] < arr[k]) temp[l++] = arr[j++];
                else temp[l++] = arr[k++];
            }
        }

        while (i <= mid1 && j <= mid2) temp[l++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];
        while (j <= mid2 && k <= right) temp[l++] = (arr[j] < arr[k]) ? arr[j++] : arr[k++];
        while (i <= mid1 && k <= right) temp[l++] = (arr[i] < arr[k]) ? arr[i++] : arr[k++];
        while (i <= mid1) temp[l++] = arr[i++];
        while (j <= mid2) temp[l++] = arr[j++];
        while (k <= right) temp[l++] = arr[k++];

        for (i = left, l = 0; i <= right; i++, l++) arr[i] = temp[l];
    }

    void threeWayMergeSort(vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid1 = left + (right - left) / 3;
            int mid2 = left + 2 * (right - left) / 3;

            threeWayMergeSort(arr, left, mid1);
            threeWayMergeSort(arr, mid1 + 1, mid2);
            threeWayMergeSort(arr, mid2 + 1, right);

            merge(arr, left, mid1, mid2, right);
        }
    }

public:
    ThreeWayMergeSort() : Algorithm("Three Way Merge Sort", 27) {};

    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        threeWayMergeSort(arr, 0, arr.size() - 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if (fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if (slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class PigeonholeSort : public Algorithm {
public:
    PigeonholeSort() : Algorithm("Pigeonhole Sort", 29) {};

    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();
        if (arr.size() == 0) return;

        int min = arr[0];
        int max = arr[0];
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] < min) min = arr[i];
            if (arr[i] > max) max = arr[i];
        }
        int range = max - min + 1;

        vector<int> holes;
        for (int i = 0; i < range; i++) {
            holes.push_back(0);
        }

        for (int i = 0; i < arr.size(); i++) {
            holes[arr[i] - min]++;
        }

        int index = 0;
        for (int i = 0; i < range; i++) {
            while (holes[i] > 0) {
                arr[index] = i + min;
                index++;
                holes[i]--;
            }
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if (fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if (slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class ShakerSort : public Algorithm {
public:
    ShakerSort() : Algorithm("Shaker Sort", 31) {};

    void sort(vector<int> arr) {
        auto startT = high_resolution_clock::now();

        bool swapped = true;
        int start = 0;
        int end = arr.size() - 1;
        while (swapped) {
            swapped = false;
            for (int i = start; i < end; ++i) {
                if (arr[i] > arr[i + 1]) {
                    // Manual swap
                    int temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                    swapped = true;
                }
            }
            if (!swapped) break;
            swapped = false;
            --end;
            for (int i = end - 1; i >= start; --i) {
                if (arr[i] > arr[i + 1]) {
                    // Manual swap
                    int temp = arr[i];
                    arr[i] = arr[i + 1];
                    arr[i + 1] = temp;
                    swapped = true;
                }
            }
            ++start;
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - startT);
        double totalTime = duration.count();
        currentTime = totalTime;
        if (fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if (slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class DoubleSelectionSort : public Algorithm {
public:
    DoubleSelectionSort() : Algorithm("Double Selection Sort", 32) {};

    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();

        int n = arr.size();
        for (int i = 0; i < n / 2; ++i) {
            int minIndex = i;
            int maxIndex = i;
            for (int j = i + 1; j < n - i; ++j) {
                if (arr[j] < arr[minIndex]) minIndex = j;
                if (arr[j] > arr[maxIndex]) maxIndex = j;
            }
            // Manual swap for min element
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
            
            if (maxIndex == i) maxIndex = minIndex;
            
            // Manual swap for max element
            temp = arr[n - i - 1];
            arr[n - i - 1] = arr[maxIndex]; 
            arr[maxIndex] = temp;
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if (fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if (slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class BinaryInsertionSort : public Algorithm {
public:
    BinaryInsertionSort() : Algorithm("Binary Insertion Sort", 33) {};

    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();

        for (int i = 1; i < arr.size(); ++i) {
            int key = arr[i];
            int left = 0;
            int right = i;
            while (left < right) {
                int mid = left + (right - left) / 2;
                if (arr[mid] <= key) left = mid + 1;
                else right = mid;
            }
            for (int j = i; j > left; --j) arr[j] = arr[j - 1];
            arr[left] = key;
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if (fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if (slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};

class GravitySort : public Algorithm {
public:
    GravitySort() : Algorithm("Gravity Sort", 34) {};

    void sort(vector<int> arr) {
        auto start = high_resolution_clock::now();

        if (arr.empty()) return;

        int max = *max_element(arr.begin(), arr.end());
        vector<vector<int>> beads(max, vector<int>(arr.size(), 0));

        for (int i = 0; i < arr.size(); ++i) {
            for (int j = 0; j < arr[i]; ++j) {
                beads[j][i] = 1;
            }
        }

        for (int j = 0; j < max; ++j) {
            int sum = 0;
            for (int i = 0; i < arr.size(); ++i) {
                sum += beads[j][i];
                beads[j][i] = 0;
            }
            for (int i = arr.size() - sum; i < arr.size(); ++i) {
                beads[j][i] = 1;
            }
        }

        for (int i = 0; i < arr.size(); ++i) {
            int j;
            for (j = 0; j < max && beads[j][i]; ++j);
            arr[i] = j;
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        double totalTime = duration.count();
        currentTime = totalTime;
        if (fastestTime > totalTime || fastestTime == 0) fastestTime = totalTime;
        if (slowestTime < totalTime || slowestTime == 0) slowestTime = totalTime;
        tries++;
    }
};




class Tournament {
    int matchesPlayed = 1;
    vector<Algorithm*> algorithms;
    vector<pair<Algorithm*, Algorithm*>> matchUps;

public:
    Tournament() {
        // Initialize algorithms
        algorithms.push_back(new SelectionSort());
        algorithms.push_back(new BubbleSort());
        algorithms.push_back(new MergeSort());
        algorithms.push_back(new InsertionSort());
        algorithms.push_back(new OddEvenSort());
        algorithms.push_back(new CocktailSort());
        algorithms.push_back(new QuickSort());
        algorithms.push_back(new HeapSort());
        algorithms.push_back(new RadixLSDSort());
        algorithms.push_back(new RadixMSDSort());
        algorithms.push_back(new CountingSort());
        algorithms.push_back(new TimSort());
        algorithms.push_back(new ShellSort());
        algorithms.push_back(new CombSort());
        algorithms.push_back(new CycleSort());
        algorithms.push_back(new PancakeSort());
        algorithms.push_back(new BitonicSort());
        algorithms.push_back(new GnomeSort());
        algorithms.push_back(new StrandSort());
        algorithms.push_back(new TagSort());
        algorithms.push_back(new LibrarySort());
        algorithms.push_back(new PatienceSort());
        algorithms.push_back(new SmoothSort());
        algorithms.push_back(new TournamentSort());
        algorithms.push_back(new FlashSort());
        algorithms.push_back(new TreeSort());
        algorithms.push_back(new ThreeWayMergeSort());
        algorithms.push_back(new BucketSort());
        algorithms.push_back(new PigeonholeSort());
        algorithms.push_back(new IntroSort());
        algorithms.push_back(new ShakerSort());
        algorithms.push_back(new DoubleSelectionSort());
        algorithms.push_back(new BinaryInsertionSort());
        algorithms.push_back(new GravitySort());
        algorithms.push_back(new InPlaceMergeSort());
        algorithms.push_back(new QuadSort());
        algorithms.push_back(new WeakHeapSort());
        algorithms.push_back(new AmericanFlagSort());

        // Initialize matchUps for round-robin
        calculateMatchUps();
    }

    void calculateMatchUps() {
        int n = algorithms.size();
        if (n % 2 == 1) {
            algorithms.push_back(nullptr); // Add a dummy team if odd number of teams
            n++;
        }

        for (int round = 0; round < n - 1; ++round) {
            for (int i = 0; i < n / 2; ++i) {
                Algorithm* team1 = algorithms[i];
                Algorithm* team2 = algorithms[n - 1 - i];

                if (team1 && team2) {
                    matchUps.push_back({team1, team2});
                }
            }
            // Rotate the array, keeping the first element fixed
            rotate(algorithms.begin() + 1, algorithms.end() - 1, algorithms.end());
        }
    }

    void playMatch(Algorithm* team1, Algorithm* team2, vector<int> a) {
        team1->sort(a);
        team2->sort(a);

        team1->matches++;
        team2->matches++;

        cout << "MATCH " << matchesPlayed++ << ":\n" << team1->name << "\tvs\t" << team2->name << endl;
        cout << team1->timeAsString(4) << "\t\t" << team2->timeAsString(4) << endl;

        if (team1->currentTime < team2->currentTime) {
            cout << "WINNER: " << team1->name << endl;
            team1->points += 3;
            team1->wins++;
            team2->losses++;
        } else if (team2->currentTime < team1->currentTime) {
            cout << "WINNER: " << team2->name << endl;
            team2->points += 3;
            team2->wins++;
            team1->losses++;
        } else {
            cout << "MATCH TIED" << endl;
            team1->points++;
            team2->points++;
            team1->ties++;
            team2->ties++;
        }
        cout << endl;
    }

    void playTournament(vector<int> arr) {
        pointsTable();
        for (const auto& match : matchUps) {
            playMatch(match.first, match.second, arr);
            pointsTable();
        }
    }

    void pointsTable() {
        vector<Algorithm*> sortedAlg = algorithms;
        sortedAlg.erase(remove(sortedAlg.begin(), sortedAlg.end(), nullptr), sortedAlg.end());

        sort(sortedAlg.begin(), sortedAlg.end(), [](Algorithm* a, Algorithm* b) {
            if (a->points == b->points)
                return a->fastestTime < b->fastestTime;
            return a->points > b->points;
        });

        // Print header with divider - increased Algorithm width from 18 to 25
        cout << "\n╔═════╦═════════════════════════════╦═════════╦══════╦════════╦══════╦═══════════════╦═══════════════╦═══════════════╦════════╗\n";
        cout << "║ " << left << setw(3) << "Pos" 
             << " ║ " << setw(25) << "Algorithm"
             << " ║ " << setw(7) << "Matches"
             << " ║ " << setw(4) << "Wins"
             << " ║ " << setw(6) << "Losses"
             << " ║ " << setw(4) << "Ties"
             << " ║ " << setw(13) << "FastestTime"
             << " ║ " << setw(13) << "SlowestTime"
             << " ║ " << setw(13) << "CurrentTime"
             << " ║ " << setw(6) << "Points" << "   ║\n";
        cout << "╠═════╬═════════════════════════════╬═════════╬══════╬════════╬══════╬═══════════════╬═══════════════╬═══════════════╬════════╣\n";

        int pos = 1;
        for (auto a : sortedAlg) {
            a->position = pos++;
            cout << "║ " << left << setw(3) << a->position 
                 << " ║ " << setw(25) << a->name  // increased from 18 to 25
                 << " ║ " << setw(7) << a->matches
                 << " ║ " << setw(4) << a->wins
                 << " ║ " << setw(6) << a->losses
                 << " ║ " << setw(4) << a->ties
                 << " ║ " << setw(13) << a->timeAsString(1)
                 << " ║ " << setw(13) << a->timeAsString(2)
                 << " ║ " << setw(13) << a->timeAsString(4)
                 << " ║ " << setw(6) << a->points << "   ║\n";
        }
        
        cout << "╚═════╩═════════════════════════════╩═════════╩══════╩════════╩══════╩═══════════════╩═══════════════╩═══════════════╩════════╝\n\n";
    }
};

int main(void){
   random_device rd;
   uniform_int_distribution d(1, 100);

    auto start = high_resolution_clock::now();

   vector<int> a;
   const int MAX_SIZE = 50000;
   for(int i  = 0; i < MAX_SIZE; i++){
        int num = d(rd);
        a.push_back(num);
   }

   cout << "Starting Tournament: " << endl;

    Tournament tourney;
    tourney.playTournament(a);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto time = duration.count();
    cout << "Time taken for program execution: " << time / 1000 << "s\n";
}
