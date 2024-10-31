#include <iostream>
#include <chrono>
#include <iomanip>
#include <random>   
#include <ranges>
#include <algorithm>

using namespace std;
using namespace std::chrono;


class Algorithm {
    public:
        string name;
        int id;
        int position;
        int tries;
        double fastestTime;
        double slowestTime;
        double averageTime;
        double currentTime;

        Algorithm(string n, int i){
            name = n;
            id = i;
            position = 0;
            tries = 0;
            fastestTime = 10000000;
            slowestTime = 0;
            currentTime = 0;
            averageTime = 0;
        }

        virtual void sort(vector<int> a){};

        void display(){
            cout << "Name: " << name
            << endl << "Id: " << id
            << endl << "Position: " << position
            << endl << "Time: " << fixed << setprecision(9) << currentTime / 1000000000 << "s" << endl;
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
        if(fastestTime > totalTime) fastestTime = totalTime;
        if(slowestTime < totalTime) slowestTime = totalTime;
        tries++;
    }

};



int main(void){
   cout << "start" << endl;
   random_device rd;
   uniform_int_distribution d(1, 100);

   vector<int> a;
   const int MAX_SIZE = 10000;
   for(int i  = 0; i < MAX_SIZE; i++){
        int num = d(rd);
        a.push_back(num);
   }


    SelectionSort ss;
    ss.sort(a);
    ss.display();


    BubbleSort bs;
    bs.sort(a);
    bs.display();
}