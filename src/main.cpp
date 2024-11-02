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
            output << time / 1000000000 << "s";
            return output.str();
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

class Tournament {
    int matchesPlayed = 0;
    vector<Algorithm*> algos;

    public:
    Tournament() {
        algos.push_back(new SelectionSort());
        algos.push_back(new BubbleSort());
        algos.push_back(new MergeSort());
    }

    void playMatch(Algorithm *team1, Algorithm *team2, vector<int> a){
        team1->sort(a);
        team2->sort(a);

        team1->matches++;
        team2->matches++;

        if(team1->currentTime < team2->currentTime){
            team1->points += 3;
            team1->wins++;
            team2->losses++;
        } else if (team2->currentTime < team1->currentTime){
            team2->points += 3;
            team2->wins++;
            team1->losses++;
        } else {
            team1->points++;
            team2->points++;
            team1->ties++;
            team2->ties++;
        }
    }
    void playTournament(vector<int> arr){
        for (auto a: algos){
            for(auto b: algos){
                if(a->id == b->id) continue;
                playMatch(a, b, arr);
            }
        }
    }

    void pointsTable(){
        vector<Algorithm*> sortedAlg = algos;

        sort(sortedAlg.begin(), sortedAlg.end(), [](Algorithm* a, Algorithm*  b){
            if(a->points == b->points)
                return a->fastestTime < b->fastestTime;
            return a->points > b->points;
        });

        cout << "Pos\tAlgorithm\tMatches\tWins\tLosses\tTies\tFastestTime\tSlowestTime\tPoints" << endl;
        int pos = 1;
        for(auto a: sortedAlg){
            a->position = pos;
            pos++;
            cout << a->position << "\t" << a->name << "\t" << a->matches << "\t" << a->wins << "\t" << a->losses << "\t" << a->ties << "\t" << a->timeAsString(1) << "\t" << a->timeAsString(2) << "\t" << a->points << endl; 
        }
    }
};

int main(void){
   random_device rd;
   uniform_int_distribution d(1, 100);

   vector<int> a;
   const int MAX_SIZE = 10000;
   for(int i  = 0; i < MAX_SIZE; i++){
        int num = d(rd);
        a.push_back(num);
   }

    Tournament tourney;
    tourney.playTournament(a);
    tourney.pointsTable();
}