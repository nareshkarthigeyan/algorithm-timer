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
            output << fixed << setprecision(9) << time / 1000000000 << "s";
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

class Tournament {
    int matchesPlayed = 1;
    int rounds;
    vector<Algorithm*> algos;
    vector<vector<pair<int, int>>> matchUps;

    public:
    Tournament() {
        algos.push_back(new SelectionSort());
        algos.push_back(new BubbleSort());
        algos.push_back(new MergeSort());
        algos.push_back(new InsertionSort());

        rounds = algos.size() - 1;
       // matchUps.resize(rounds / 2, vector<pair<int, int>>(rounds));
    }

    void calculateMatchUps(){
        int n = algos.size();
        vector<int> row;
        vector<int> col;
        for(int i = 0; i < n; i++){
            row.push_back(i + 1);
            col.push_back(i + 1);
        };
        int index = 0;
        // for(int round = 0; round < n - 1; round++){
        //     vector<pair<int,int>> thisRound;
        //     for(int i = 0; i < n / 2; i++){
        //         index = (index + i) % (n - 1);
        //         if (row[index] == row[n - 1 -index]) continue;
        //         int first = row[index];
        //         int second = row[n - 1 - index];
        //         thisRound.push_back({first, second});
        //     }
        //     matchUps.push_back(thisRound);
        // }

        for(int i = 0; i < row.size(); i++){
            vector<pair<int, int>> thisRound;
            for(int j = 0; j < col.size(); j++){
                if(i == j) continue;
                thisRound.push_back({row[i], col[j]});
            }
            matchUps.push_back(thisRound);
        }

        for(int round  = 0; round < matchUps.size(); round++){
            cout << "ROUND " << round << endl;
            for(int i = 0; i < n - 1; i++){
                cout << matchUps[round][i].first << " vs  " << matchUps[round][i].second << endl;
            }
        }
    }

    void playMatch(Algorithm *team1, Algorithm *team2, vector<int> a){
        team1->sort(a);
        team2->sort(a);

        team1->matches++;
        team2->matches++;
        
        cout << "MATCH " << matchesPlayed++ << ":\n" << team1->name << "\tvs\t" << team2->name << endl;
        cout << team1->timeAsString(4) << "\t\t" << team2->timeAsString(4) << endl;

        if(team1->currentTime < team2->currentTime){
            cout << "WINNER: " << team1->name << endl;
            team1->points += 3;
            team1->wins++;
            team2->losses++;
        } else if (team2->currentTime < team1->currentTime){
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
    void playTournament(vector<int> arr){
        for (auto a: algos){
            for(auto b: algos){
                if(a->id == b->id) continue;
                playMatch(a, b, arr);
            }
            pointsTable();
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
//    random_device rd;
//    uniform_int_distribution d(1, 100);

//    vector<int> a;
//    const int MAX_SIZE = 10000;
//    for(int i  = 0; i < MAX_SIZE; i++){
//         int num = d(rd);
//         a.push_back(num);
//    }

    Tournament tourney;
    tourney.calculateMatchUps();
//     tourney.playTournament(a);
}