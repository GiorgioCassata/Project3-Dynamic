#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Sums a vector, a, from indices b to c
int sumVector(vector<int> a, int b, int c) {
    int total = 0;

    for (int i = b; i < c; ++i) {
        total += a.at(i);
    }

    return total;
}


int main() {
    vector<int> x, s;

    int numDays, lastReboot, temp;

    ifstream file;
    ofstream fout;

    // open input file in which the first entry is n = number of days
    file.open("input.txt");
    file >> numDays;

    // initialize variables that depend on numDays
    vector<vector<int>> processes (numDays);
    vector<int> sum(numDays);
    vector<int> decision(numDays);

    // read in and store into vectors, the x and s series  of numbers
    for (int i = 0; i < numDays; ++i) {
        file >> temp;
        x.push_back(temp);
    }
    for (int i = 0; i < numDays; ++i) {
        file >> temp;
        s.push_back(temp);
    }
    file.close();

    // Calculate possible processes for each day
    for (int i = 0; i < numDays; ++i) {
        for (int j = 0; j < numDays; ++j) {
            if (j >= i) {
        	       processes.at(i).push_back(min(x[j], s[j-i]));
    		      sum.at(i) += processes[i][j];
            } else {
                processes.at(i).push_back(0);
            }
        }
    }

    lastReboot = numDays-1;
    //for every day, decide wheter or not to reboot the day before or not.
    for(int j = numDays-1; j>0; j--){
    	if (sumVector(processes.at(j), 0, lastReboot) < sumVector(processes.at(j-1), 0, lastReboot)){ 	//where sum(*a,b,c) returns the sum of elements from index b to c in array a.
    		decision[j-1] = 0;
    	} else {
    		decision[j-1] = 1;
            lastReboot = j-1;
        }
    }

    // Build array of data processes for best day
    vector<int> output;
    int row = 0;
    for (int i = 0; i < numDays; ++i) {
        if(decision.at(i) == 0) {
            output.push_back(processes.at(row).at(i));
        } else {
            output.push_back(0);
            row = i+1;
        }
    }
    fout.open("output.txt");

    // Sum total data processed and output results to console and output file
    int outSum = 0;
    for (int i = 0; i < numDays; ++i) {
        outSum += output.at(i);
    }
    cout << outSum << endl;
    fout << outSum << endl;
    for (int i = 0; i < numDays; ++i) {
        cout << output.at(i) << ' ';
        fout << output.at(i) << ' ';
    }
    cout << endl;
    fout.close();

    return 0;
}
