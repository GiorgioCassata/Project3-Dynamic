#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int sum(vector<int> a, int b, int c) {
    int total = 0;
    for (int i = b; i < c; ++i) {
        total += a.at(i);
    }

    return total;
}

int main() {
    vector<vector<int>> list;
    vector<int> x, s;

    int numDays;
    int greatestIndex;
    int temp;

    bool trigger;
    ifstream file;
    ofstream fout;

    // open input file in which the first entry is n = number of days
    file.open("input.txt");
    file >> numDays;

    // initialize variables that depend on numDays
        //vector<vector<int>> processes (numDays);


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
    /*
    // calculate all possible processes possible just one time and store into matrix
    for (int i = 0; i < numDays; ++i) {
        for (int j = 0; j < numDays; ++j) {
            if (s.at(j) > x.at(i)) {
                processes.at(i).push_back(x.at(i));
            } else {
                processes.at(i).push_back(s.at(j));
            }
            if (j >= i) {
                break;
            }
        }
    }
    */

    vector<vector<int>> processes (numDays);
    vector<int> sum(numDays);
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

    vector<int> decision(numDays);
    int lastReboot = numDays-1;
    int total1, total2;

    //for every day, decide wheter or not to reboot the day before or not.
    for(int j = numDays-1; j>0; j--){
        total1 = 0;
        for (int i = 0; i < lastReboot; ++i) {
            total1 += processes.at(j).at(i);
        }
        total2 = 0;
        for (int i = 0; i < lastReboot; ++i) {
            total2 += processes.at(j-1).at(i);
        }
    	if (total1 < total2){ 	//where sum(*a,b,c) returns the sum of elements from index b to c in array a.
    		decision[j-1] = 0;
    	} else {
    		decision[j-1] = 1;
            lastReboot = j-1;
        }
    }

    /*
    // print out processes matrix
    for (int i = 0; i < numDays; ++i) {
        for (int j = 0; j < numDays; ++j) {
            cout << processes[i][j] << ", ";
        }
        cout << sum.at(i) << " " << decision.at(i);
        cout << endl;
    }
    */

    vector<int> output;
    int row = 0;
    for (int i = 0; i < numDays; ++i) {
        if(decision.at(i) == 0) {
            //cout << processes.at(row).at(i) << ' ';
            output.push_back(processes.at(row).at(i));
        } else {
            //cout << 0 << ' ';
            output.push_back(0);
            row = i+1;
        }
    }
    //cout << endl;
    fout.open("output.txt");
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
